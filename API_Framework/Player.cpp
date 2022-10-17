#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"
#include "Seller.h"
#include "Mouse.h"
#include "Inven.h"
#include "Status.h"
#include "ObjMgr.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "MathMgr.h"
#include "UIMgr.h"
#include "Skill.h"
#include "MyEvent.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
	:m_bSkill(false),m_bAtt(false), m_tMainSkill(nullptr)
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/cast.bmp", L"cast");
	m_eGroup = GROUPID::GAMEOBJECT;
	m_tInfo.fX = 1150.f;
	m_tInfo.fY = 1100.f;
	m_tInfo.iCX = 42;
	m_tInfo.iCY = 76;
	m_tBeforePos = m_tInfo;
	m_tPInfo.iMoveSpeed = 3;
	m_fAngle = 0.f;
	m_tPInfo.iStr = 10;
	m_tPInfo.iDex = 10;
	m_tPInfo.iLife = 10;
	m_tPInfo.iEnergy = 10;
	m_tPInfo.iMaxHp = 200;
	m_tPInfo.iHp = m_tPInfo.iMaxHp;
	m_tPInfo.iMaxMp = 200;
	m_tPInfo.iMp = m_tPInfo.iMaxMp;
	m_tPInfo.iMaxStamina = 200;
	m_tPInfo.iStamina = m_tPInfo.iMaxStamina;
	m_tPInfo.iMaxExp = 100;
	m_tPInfo.iBeforeExp = 0;
	m_tPInfo.iExp = 0;
	m_tPInfo.iLevel = 1;
	m_tPInfo.iAttSpeed = 3;
	m_tPInfo.iSkillUp = 0;
	m_tPInfo.iGold = 10000;
	m_tPInfo.iRemainStat = 1;
	m_iRemainSkill = 1;
	m_iHpRestore = 0;
	m_bHpRestore = false;
	m_iMpRestore = 0;
	m_bMpRestore = false;

	m_bRun = false;
	m_bMove = true;
	m_bMap = false;
	m_bOffset = true;
	m_eState = STATE::IDLE;
}

int CPlayer::Update()
{
	if (!m_bDead)
	{
		if (m_tPInfo.iExp >= m_tPInfo.iMaxExp)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
			CSoundMgr::Get_Instance()->PlaySound(L"prare.wav", CSoundMgr::PLAYER);
			m_tPInfo.iBeforeExp = m_tPInfo.iMaxExp;
			m_tPInfo.iMaxExp += (m_tPInfo.iLevel + 1) * 100;
			m_tPInfo.iLevel += 1;
			m_tPInfo.iRemainStat += 1;
			m_iRemainSkill += 1;
		}
		if (CKeyMgr::Get_Instance()->Key_Down('M'))
			m_bMap = !m_bMap;
		if (CKeyMgr::Get_Instance()->Key_Down(VK_ADD))
			m_bOffset = !m_bOffset;
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) && m_bMove && m_eState != STATE::CASTING && m_eState != STATE::ATTACK)
		{
			GetCursorPos(&m_tMPoint);
			ScreenToClient(g_hWnd, &m_tMPoint);
			m_tMPoint.x -= LONG(CScrollMgr::Get_Instance()->Get_Scroll_X());
			m_tMPoint.y -= LONG(CScrollMgr::Get_Instance()->Get_Scroll_Y());
			m_fAngle = MathMgr::Get_Angle(float(m_tMPoint.x), float(m_tMPoint.y), m_tInfo.fX, m_tInfo.fY);
		}
		Attack();
		m_tBeforePos = m_tInfo;
		Skill();
		Move();
		if (m_bHpRestore)
		{
			m_iHpRestore -= 1;
			m_tPInfo.iHp += 1;
			if (m_tPInfo.iMaxHp < m_tPInfo.iHp)
				m_tPInfo.iHp = m_tPInfo.iMaxHp;
			if (0 == m_iHpRestore)
			{
				m_bHpRestore = false;
				CUIMgr::Get_Instance()->Get_HpBal().front()->Set_Open(false);
			}
		}
		if (m_bMpRestore)
		{
			m_iMpRestore -= 1;
			m_tPInfo.iMp += 1;
			if (m_tPInfo.iMaxMp < m_tPInfo.iMp)
				m_tPInfo.iMp = m_tPInfo.iMaxMp;
			if (0 == m_iMpRestore)
			{
				m_bMpRestore = false;
				CUIMgr::Get_Instance()->Get_MpBal().front()->Set_Open(false);
			}
		}
		if (CKeyMgr::Get_Instance()->Key_Down('Q'))
			m_tPInfo.iHp -= 100;
		if (CKeyMgr::Get_Instance()->Key_Pressing('W'))
			m_tPInfo.iExp += 100;
		if (CKeyMgr::Get_Instance()->Key_Down('R'))
		{
			m_bRun = !m_bRun;
			static_cast<CStatus*>(CUIMgr::Get_Instance()->Get_Statu().front())->Set_Run(m_bRun);
			if (STATE::RUN == m_eState)
				m_eState = STATE::WALK;
			else if (STATE::WALK == m_eState)
				m_eState = STATE::RUN;
		}
		//딜레이 후 발사
		if (m_bSkill && m_fTime > m_fSkill)
		{
			m_tMainSkill->Skill(m_tInfo.fX, m_tInfo.fY, m_fAngle, m_tMainSkill->iLevel + m_tPInfo.iSkillUp);
			m_bSkill = false;
		}
		if (m_bAtt && m_fTime > m_fAtt)
		{
			CObj* pObj = CAbstractFactory<CBullet>::Create(m_tInfo.fX + 10 * cosf(m_fAngle), m_tInfo.fY + 10 * sinf(m_fAngle) - 38, m_fAngle, m_tPInfo.iStr);
			pObj->Set_FrameKey(L"");
			CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
			m_bAtt = false;
		}
		m_tPInfo.iStamina += 1;
		if (m_tPInfo.iMaxStamina < m_tPInfo.iStamina)
			m_tPInfo.iStamina = m_tPInfo.iMaxStamina;
		OffSet();
		m_fTime += 0.1f;
	}
		return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	if (0 >= m_tPInfo.iHp)
	{
		if (!m_bDead)
		{
			m_eState = STATE::DEAD;
			m_iLife = -1;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
			CSoundMgr::Get_Instance()->PlaySound(L"pdeath3.wav", CSoundMgr::PLAYER);
		}
		m_iLife += 1;
		if (46 < m_iLife)
			m_iLife = 46;
		m_tPInfo.iHp = 0;
		m_bDead = true;
	}
	m_bMove = true;
}

void CPlayer::Render(HDC _DC)
{
	Update_Rect();

	Ani(_DC);
	Map(_DC);

	//TCHAR		szBuff[32] = L"";
	//wsprintf(szBuff, L"PX: %d", int(m_tInfo.fX));
	//TextOut(_DC, 0, 0, szBuff, lstrlen(szBuff));
	//
	//wsprintf(szBuff, L"PY: %d", int(m_tInfo.fY));
	//TextOut(_DC, 100, 0, szBuff, lstrlen(szBuff));

	//wsprintf(szBuff, L"MX: %d", m_tMPoint.x);
	//TextOut(_DC, 1200, 0, szBuff, lstrlen(szBuff));

	//wsprintf(szBuff, L"MY: %d", m_tMPoint.y);
	//TextOut(_DC, 1300, 0, szBuff, lstrlen(szBuff));
}

void CPlayer::Release()
{
}

void CPlayer::Move()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) && m_bMove && m_eState != STATE::CASTING && m_eState != STATE::ATTACK && m_eState != STATE::HITTED)
	{
		if (m_bRun)
			m_eState = STATE::RUN;
		else
			m_eState = STATE::WALK;
	}
	if (STATE::RUN == m_eState)
	{
		float fTemp = MathMgr::Get_Distance(float(m_tMPoint.x), float(m_tMPoint.y), m_tInfo.fX, m_tInfo.fY);

		m_tInfo.fX += m_tPInfo.iMoveSpeed*cosf(m_fAngle)*2;
		m_tInfo.fY += m_tPInfo.iMoveSpeed*sinf(m_fAngle);
		if (3 > fTemp)
		{
			m_tInfo.fX = float(m_tMPoint.x);
			m_tInfo.fY = float(m_tMPoint.y);
			static_cast<CInven*>(CUIMgr::Get_Instance()->Get_Inven().front())->PickItem();
			static_cast<CInven*>(CUIMgr::Get_Instance()->Get_Inven().front())->Shop();
			static_cast<CMyEvent*>(CUIMgr::Get_Instance()->Get_Event().front())->Event();
			m_eState = STATE::IDLE;
		}
		m_tPInfo.iStamina -= 2;
		if (0 > m_tPInfo.iStamina)
		{
			m_eState = STATE::WALK;
			m_bRun = false;
			static_cast<CStatus*>(CUIMgr::Get_Instance()->Get_Statu().front())->Set_Run(m_bRun);
		}
	}
	if (STATE::WALK == m_eState)
	{
		m_tBeforePos = m_tInfo;
		float fTemp = MathMgr::Get_Distance(float(m_tMPoint.x), float(m_tMPoint.y), m_tInfo.fX, m_tInfo.fY);

		m_tInfo.fX += m_tPInfo.iMoveSpeed*cosf(m_fAngle);
		m_tInfo.fY += m_tPInfo.iMoveSpeed*sinf(m_fAngle) *0.5;
		if (3 > fTemp)
		{
			m_tInfo.fX = float(m_tMPoint.x);
			m_tInfo.fY = float(m_tMPoint.y);
			static_cast<CInven*>(CUIMgr::Get_Instance()->Get_Inven().front())->PickItem();
			static_cast<CInven*>(CUIMgr::Get_Instance()->Get_Inven().front())->Shop();
			static_cast<CMyEvent*>(CUIMgr::Get_Instance()->Get_Event().front())->Event();
			m_eState = STATE::IDLE;
		}
	}
}

void CPlayer::Skill()
{
	if (m_tMainSkill && CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON) && m_bMove && m_eState != STATE::CASTING && m_eState != STATE::ATTACK)
	{
		if (m_tMainSkill->iUseMp > m_tPInfo.iMp)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
			CSoundMgr::Get_Instance()->PlaySound(L"pAcain.wav", CSoundMgr::UI);
			return;
		}

		GetCursorPos(&m_tMPoint);
		ScreenToClient(g_hWnd, &m_tMPoint);

		m_tMPoint.x -= LONG(CScrollMgr::Get_Instance()->Get_Scroll_X());
		m_tMPoint.y -= LONG(CScrollMgr::Get_Instance()->Get_Scroll_Y());

		m_fAngle = MathMgr::Get_Angle(float(m_tMPoint.x), float(m_tMPoint.y), m_tInfo.fX, m_tInfo.fY - m_tInfo.iCY / 2);

		m_fSkill = m_fTime + 10 / m_tPInfo.iAttSpeed;
		m_bSkill = true;

		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CASTING);
		CSoundMgr::Get_Instance()->PlaySound(L"scoldcast.wav", CSoundMgr::CASTING);

		m_fCastingTime = m_fTime;
		m_tPInfo.iMp -= m_tMainSkill->iUseMp;
		m_eState = STATE::CASTING;
	}
}

void CPlayer::Attack()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) && m_eState != STATE::CASTING && m_eState != STATE::ATTACK)
	{
		for (auto& pMonster : CObjMgr::Get_Instance()->Get_Obj(OBJID::MONSTER))
		{
			if (PtInRect(&pMonster->Get_Rect(), m_tMPoint))
			{
				if (100 > MathMgr::Get_Distance(pMonster->Get_Info().fX, pMonster->Get_Info().fY, m_tInfo.fX,m_tInfo.fY))
				{
					m_bAtt = true;
					m_fAttTime = m_fTime;
					m_eState = STATE::ATTACK;
					m_fAtt = m_fTime + 10 / m_tPInfo.iAttSpeed;
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
					CSoundMgr::Get_Instance()->PlaySound(L"pone hand swing.wav", CSoundMgr::PLAYER);
					return;
				}
			}
		}
	}
}

void CPlayer::Ani(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Rectangle(_DC, m_tRect.left + iScrollX, m_tRect.top + iScrollY, m_tRect.right + iScrollX, m_tRect.bottom + iScrollY);

	HDC hMemDC = nullptr;

	float fTemp = m_fAngle - 7*PI / 16;
	if (0 > fTemp)
		fTemp += 2 * PI;
	int i = int(8 * fTemp / PI);

	switch (m_eState)
	{
	case STATE::IDLE:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Idle");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, 42, 73
			, hMemDC
			, 42 * (int(m_fTime) % 16), 73*i
			, 42, 73
			, RGB(170, 170, 170));
		break;
	case STATE::RUN:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Run");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX-10, m_tRect.top + iScrollY
			, 61, 76
			, hMemDC
			, 61 * (int(m_fTime*m_tPInfo.iMoveSpeed*0.8) % 8), 76*i
			, 61, 76
			, RGB(170, 170, 170));
		break;
	case STATE::WALK:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Attackwalk");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX-10, m_tRect.top + iScrollY
			, 60, 76
			, hMemDC
			, 60 * (int(m_fTime * m_tPInfo.iMoveSpeed*0.8) % 8), 76 * i
			, 60, 76
			, RGB(170, 170, 170));
		break;
	case STATE::ATTACK: // 85, 105
		if ((m_fTime - m_fAttTime) > 20/ m_tPInfo.iAttSpeed)
		{
			m_eState = STATE::ATTACKIDLE;
			Ani(_DC);
		}
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Attack");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX-37, m_tRect.top + iScrollY-13
			, 120, 92
			, hMemDC
			, 120 * int((m_fTime - m_fAttTime)*m_tPInfo.iAttSpeed), 92 * i
			, 120, 92
			, RGB(170, 170, 170));
		break;
	case STATE::CASTING:
		if ((m_fTime - m_fCastingTime) > 14 / m_tPInfo.iAttSpeed)
		{
			m_eState = STATE::ATTACKIDLE;
			Ani(_DC);
		}
		m_iOption = int((m_fTime - m_fCastingTime)*m_tPInfo.iAttSpeed);
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Casting");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX - 26, m_tRect.top + iScrollY - 18
			, 97, 92
			, hMemDC
			, 97 * m_iOption, 92 * i
			, 97, 92
			, RGB(170, 170, 170));
		//캐스팅
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"cast");
		GdiTransparentBlt(_DC
			, m_tRect.left - 14 + iScrollX, m_tRect.top - 40 + iScrollY
			, 70, 123
			, hMemDC
			, 70* m_iOption, 0
			, 70, 123
			, RGB(0, 0, 0));
		break;
	case STATE::ATTACKIDLE: // 80, 82
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"AttackIdle");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX - 10, m_tRect.top + iScrollY+2
			, 66, 72
			, hMemDC
			, 66 * (int(m_fTime) % 8), 72 * i
			, 66, 72
			, RGB(170, 170, 170));
		break;
	case STATE::HITTED:
		if ((m_fTime - m_fHittedTime) > 0.7f)
		{
			m_eState = STATE::ATTACKIDLE;
			Ani(_DC);
		}
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GetHit");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX - 10, m_tRect.top + iScrollY + 2
			, 66, 73
			, hMemDC
			, 66 * int((m_fTime - m_fHittedTime)*10), 73 * i
			, 66, 73
			, RGB(170, 170, 170));
		break;
	case STATE::DEAD:
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"PlayerDie");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX - 10, m_tRect.top + iScrollY + 2
			, 92, 88
			, hMemDC
			, 92 * (m_iLife>>1),0
			, 92, 88
			, RGB(0, 0, 0));
		break;
	default:
		break;
	}
}

void CPlayer::Map(HDC _DC)
{
	if (m_bMap)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Minimap");
		GdiTransparentBlt(_DC
			, 950, 50
			, 400, 200
			, hMemDC
			, 0, 0
			, 400, 200
			, RGB(0, 0, 0));
		Ellipse(_DC, int(947 + m_tInfo.fX*0.0743), int(47 + m_tInfo.fY*0.0743), int(953 + m_tInfo.fX*0.0743), int(53 + m_tInfo.fY*0.0743));

		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON) &&
			!m_bOffset)
		{
			GetCursorPos(&m_tMPoint);
			ScreenToClient(g_hWnd, &m_tMPoint);

			if (950 < m_tMPoint.x && 1350 >  m_tMPoint.x &&
				50 <  m_tMPoint.y && 250 >  m_tMPoint.y)
			{
				CScrollMgr::Get_Instance()->Set_Scroll_X(WINCX / 2 - (m_tMPoint.x - 950) / 0.0743f);
				CScrollMgr::Get_Instance()->Set_Scroll_Y(WINCY / 2 - (m_tMPoint.y - 50) / 0.0743f);
			}

		}
	}
}

float CPlayer::Get_HpRestoreRate()
{
	float fTemp = float(m_tPInfo.iMaxHp - m_tPInfo.iHp - m_iHpRestore) / m_tPInfo.iMaxHp;
	if (0 > fTemp)
		fTemp = 0.f;
	return fTemp;
}

float CPlayer::Get_MpRestoreRate()
{
	float fTemp = float(m_tPInfo.iMaxMp - m_tPInfo.iMp - m_iMpRestore) / m_tPInfo.iMaxMp;
	if (0 > fTemp)
		fTemp = 0.f;
	return fTemp;
}

void CPlayer::Set_Hitted()
{
	m_eState = STATE::HITTED;
	m_bSkill = false; m_bAtt = false;
	m_fHittedTime = m_fTime;
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
	switch (int(m_fTime*10)%4)
	{
	case 0:
		CSoundMgr::Get_Instance()->PlaySound(L"psoft1.wav", CSoundMgr::PLAYER);
		break;
	case 1:
		CSoundMgr::Get_Instance()->PlaySound(L"psoft2.wav", CSoundMgr::PLAYER);
		break;
	case 2:
		CSoundMgr::Get_Instance()->PlaySound(L"psoft3.wav", CSoundMgr::PLAYER);
		break;
	case 3:
		CSoundMgr::Get_Instance()->PlaySound(L"psoft4.wav", CSoundMgr::PLAYER);
		break;
	default:
		break;
	}
}

void CPlayer::OffSet()
{
	if (m_bOffset)
	{
		int iOffsetX = (WINCX >> 1);
		if (CUIMgr::Get_Instance()->Get_Inven().front()->Get_Open())
			iOffsetX = (WINCX >> 2);
		else if (CUIMgr::Get_Instance()->Get_Skill().front()->Get_Open())
			iOffsetX = (WINCX >> 2);
		else if(CUIMgr::Get_Instance()->Get_Statu().front()->Get_Open())
			iOffsetX = 3*(WINCX >> 2);
		else if(static_cast<CInven*>(CUIMgr::Get_Instance()->Get_Inven().front())->Get_Shop())
			iOffsetX = 3 * (WINCX >> 2);

		int iOffsetY = (WINCY >> 1);
		//int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();

		CScrollMgr::Get_Instance()->Set_Scroll_X(iOffsetX - m_tBeforePos.fX);
		CScrollMgr::Get_Instance()->Set_Scroll_Y(iOffsetY - m_tBeforePos.fY);
	}
	else
	{
		POINT tTemp = {};
		GetCursorPos(&tTemp);
		ScreenToClient(g_hWnd, &tTemp);
		LONG fX = tTemp.x;
		LONG fY = tTemp.y;
		if(20 > fX)
			CScrollMgr::Get_Instance()->Set_Scroll_XP(10);
		else if (1380 < fX)
			CScrollMgr::Get_Instance()->Set_Scroll_XP(-10);
		if (20 > fY)
			CScrollMgr::Get_Instance()->Set_Scroll_YP(10);
		else if (780 < fY)
			CScrollMgr::Get_Instance()->Set_Scroll_YP(-10);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
	{
		int iOffsetX = (WINCX >> 1);
		int iOffsetY = (WINCY >> 1);
		int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();

		CScrollMgr::Get_Instance()->Set_Scroll_X(iOffsetX - m_tInfo.fX);
		CScrollMgr::Get_Instance()->Set_Scroll_Y(iOffsetY - m_tInfo.fY);
	}

	CScrollMgr::Get_Instance()->Set_Boundary();
}

void CPlayer::HpPotion_Use(int _iHp)
{
	m_iHpRestore += _iHp; 
	m_bHpRestore = true; 
	CUIMgr::Get_Instance()->Get_HpBal().front()->Set_Open(true);
}

void CPlayer::MpPotion_Use(int _iMp)
{
	m_iMpRestore += _iMp;
	m_bMpRestore = true; 
	CUIMgr::Get_Instance()->Get_MpBal().front()->Set_Open(true);
}
