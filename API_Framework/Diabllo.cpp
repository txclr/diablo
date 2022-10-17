#include "stdafx.h"
#include "Diabllo.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "DiaLightning.h"
#include "Fire.h"
#include "Invisible.h"
#include "DiaDead.h"
#include "ObjMgr.h"
#include "MathMgr.h"
#include "SoundMgr.h"

CDiabllo::CDiabllo()
{
	m_tInfo.fX = 1615.f;
	m_tInfo.fY = 820.f;
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
	CSoundMgr::Get_Instance()->PlaySound(L"DiabloInit.wav", CSoundMgr::UI);
}


CDiabllo::~CDiabllo()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
	CSoundMgr::Get_Instance()->PlaySound(L"Diadeath.wav", CSoundMgr::UI);
	CObj* pObj = CAbstractFactory<CDiaDead>::Create(m_tInfo.fX+10, m_tInfo.fY-30, m_fAngle, true);
	CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
}

void CDiabllo::Initialize()
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_bEffect = false;
	m_bEffect1 = true;
	m_bAtt = false;
	m_pFrameKey = L"DiaNatural";
	m_fSpeed = 5.f;
	m_fActionSpeed = 2;
	m_fAngle = 0.f;
	m_fBeamTime = 0;
	m_eState = STATE::IDLE;
	m_iMaxLife = 5000;
	m_iLife = m_iMaxLife;
	m_eGroup = GROUPID::GAMEOBJECT;
}

int CDiabllo::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_bEffect)
	{
		m_bEffect1 = true;
		m_fEffectTime = m_fTime + 10;
		//이속감소
		m_fActionSpeed = 1;
		m_bEffect = false;
	}
	if (m_bEffect1)
	{
		if (m_fTime > m_fEffectTime)
		{
			m_bEffect1 = false;
			//이속증가
			m_fActionSpeed = 2;
		}
	}
	if (m_eState != STATE::ATTACK && m_eState != STATE::CASTING && m_eState != STATE::RUN)
	{
		if (!m_pPlayer->Get_Dead())
		{
			m_fAngle = MathMgr::Get_Angle(m_pPlayer->Get_Info().fX, m_pPlayer->Get_Info().fY, m_tInfo.fX, m_tInfo.fY);
			float fTemp = MathMgr::Get_Distance(this, m_pPlayer);
			if (700 < fTemp)
			{
				m_fRunTime = m_fTime;
				m_eState = STATE::RUN;
				m_bRun = true;
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
				CSoundMgr::Get_Instance()->PlaySound(L"Dattack4.wav", CSoundMgr::MONSTER);
			}
			else
			{
				switch (rand()%4)
				{
				case 0:
					m_fRunTime = m_fTime;
					m_eState = STATE::RUN;
					m_bRun = true;
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
					CSoundMgr::Get_Instance()->PlaySound(L"Dattack4.wav", CSoundMgr::MONSTER);
					break;
				case 1:
					m_fCastTime = m_fTime;
					m_eState = STATE::CASTING;
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
					CSoundMgr::Get_Instance()->PlaySound(L"Dlazer.wav", CSoundMgr::MONSTER);
					break;
				case 2:
					m_fCastTime = m_fTime;
					m_eState = STATE::CASTING;
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
					CSoundMgr::Get_Instance()->PlaySound(L"Dlazer.wav", CSoundMgr::MONSTER);
					break;
				case 3:
					m_bAtt = true;
					m_fAttTime = m_fTime;
					m_eState = STATE::ATTACK;
					m_fAtt = m_fTime + 10 / m_fActionSpeed;
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MONSTER);
					CSoundMgr::Get_Instance()->PlaySound(L"Dcastfire.wav", CSoundMgr::MONSTER);
					break;
				}
			}
		}
		else
		{
			m_iLife = m_iMaxLife;
			CSoundMgr::Get_Instance()->PlaySound(L"Dlaugh1.wav", CSoundMgr::MONSTER);
		}
	}

	if (m_bAtt && m_fTime > m_fAtt)
	{
		for (int i = 0; i < 16; ++i)
		{
			CObj* pObj = CAbstractFactory<CFire>::Create(m_tInfo.fX, m_tInfo.fY, i*PI*0.125f, 1);
			CObjMgr::Get_Instance()->Add_Object(OBJID::MBULLET, pObj);
		}
		m_bAtt = false;
	}

	m_fTime += 0.1f;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CDiabllo::Late_Update()
{
	if (m_iLife < 0)
		m_bDead = true;
}

void CDiabllo::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();
	//Rectangle(_DC, m_tRect.left + iScrollX, m_tRect.top+ iScrollY, m_tRect.right + iScrollX, m_tRect.bottom+ iScrollY);

	HDC hMemDC;

	float fTemp = m_fAngle - 3 * PI / 8;
	if (0 > fTemp)
		fTemp += 2 * PI;
	int i = int(4 * fTemp / PI);

	switch (m_eState)
	{
	case STATE::IDLE:
		if (m_bEffect1)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BDiaNatural");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DiaNatural");
		GdiTransparentBlt(_DC
			, m_tRect.left - 81 + iScrollX, m_tRect.top - 56 + iScrollY
			, 263, 212
			, hMemDC
			, 263 * (int(m_fTime*m_fActionSpeed) % 12), 212 * i
			, 263, 212
			, RGB(170, 170, 170));
		break;
	case STATE::RUN:
		if ((m_fTime - m_fRunTime) > 22 / m_fActionSpeed)
		{
			m_eState = STATE::IDLE;
			Render(_DC);
		}
		if (m_bEffect1)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BDiaRun");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DiaRun");
		GdiTransparentBlt(_DC
			, m_tRect.left - 100 + iScrollX, m_tRect.top - 60 + iScrollY
			, 309, 249
			, hMemDC
			, 309 * int((m_fTime - m_fRunTime)*m_fActionSpeed), 249 * i
			, 309, 249
			, RGB(170, 170, 170));
		if ((m_fTime - m_fRunTime) > 5 / m_fActionSpeed)
		{
			if (m_bRun)
			{
				CObj* pObj = CAbstractFactory<CInvisible>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle, 10);
				CObjMgr::Get_Instance()->Add_Object(OBJID::MBULLET, pObj);
				m_bRun = false;
			}
			m_tInfo.fX += m_fActionSpeed*cosf(m_fAngle) * 6;
			m_tInfo.fY += m_fActionSpeed*sinf(m_fAngle) * 3;
		}
		break;
	case STATE::ATTACK:
		if ((m_fTime - m_fAttTime) > 32 / m_fActionSpeed)
		{
			m_eState = STATE::IDLE;
			Render(_DC);
		}
		if (m_bEffect1)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BDiaFire");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DiaFire");
		GdiTransparentBlt(_DC
			, m_tRect.left - 90 + iScrollX, m_tRect.top - 96 + iScrollY
			, 288, 237
			, hMemDC
			, 288 * int((m_fTime - m_fAttTime)*m_fActionSpeed*0.5), 237 * i
			, 288, 237
			, RGB(170, 170, 170));
		break;
	case STATE::CASTING:
		if ((m_fTime - m_fCastTime) > 34 / m_fActionSpeed)
		{
			m_eState = STATE::IDLE;
			Render(_DC);
		}
		if (0 < sin(MathMgr::Get_Angle(m_pPlayer->Get_Info().fX, m_pPlayer->Get_Info().fY, m_tInfo.fX, m_tInfo.fY) - m_fAngle))
			m_fAngle += 0.02f;
		else
			m_fAngle -= 0.02f;
		if (m_bEffect1)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BDiaBeam");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DiaBeam");
		GdiTransparentBlt(_DC
			, m_tRect.left - 80 + iScrollX, m_tRect.top - 102 + iScrollY
			, 266, 257
			, hMemDC
			, 266 * int((m_fTime - m_fCastTime)*m_fActionSpeed*0.5), 257 * i
			, 266, 257
			, RGB(170, 170, 170));
		if ((m_fTime - m_fCastTime) > 15 / m_fActionSpeed)
		{
			if (m_fBeamTime < m_fTime)
			{
				CObj* pObj = CAbstractFactory<CDiaLightning>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle, 1);
				CObjMgr::Get_Instance()->Add_Object(OBJID::MBULLET, pObj);
				m_fBeamTime = m_fTime + 0.5f;
			}
		}
		break;
	}

}

void CDiabllo::Release()
{
}
