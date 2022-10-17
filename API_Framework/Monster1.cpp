#include "stdafx.h"
#include "Monster1.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SkelletonDie.h"
#include "Bullet.h"
#include "IceBlock.h"
#include "Player.h"
#include "ObjMgr.h"
#include "MathMgr.h"
#include "SoundMgr.h"

CMonster1::CMonster1()
{
	m_tInfo.fX = 2100.f;
	m_tInfo.fY = 1100.f;
}


CMonster1::~CMonster1()
{
	CObj* pObj;
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
	CSoundMgr::Get_Instance()->PlaySound(L"Mdeath1.wav", CSoundMgr::UI);
	if (m_bEffect1)
	{
		pObj = CAbstractFactory<CIceBlock>::Create(m_tInfo.fX, m_tInfo.fY, true);
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
	}
	else
	{
		pObj = CAbstractFactory<CSkelletonDie>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle, true);
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
	}
	static_cast<CPlayer*>(m_pPlayer)->Set_ExpPlus(100);
}

void CMonster1::Initialize()
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_bEffect = false;
	m_bEffect1 = true;
	m_bAtt = false;
	m_tInfo.iCX = 40;
	m_tInfo.iCY = 90;
	m_pFrameKey = L"SkeletonIdle";
	m_fSpeed = 1.f;
	m_fActionSpeed = 2;
	m_fAngle = 0.f;
	m_eState = STATE::IDLE;
	m_iMaxLife = 1000;
	m_iLife = m_iMaxLife;
	m_bOut = false;
	m_eGroup = GROUPID::GAMEOBJECT;
}

int CMonster1::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (m_bEffect)
	{
		m_bEffect1 = true;
		m_fEffectTime = m_fTime + 80;
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
	m_fAngle = MathMgr::Get_Angle(m_pPlayer->Get_Info().fX, m_pPlayer->Get_Info().fY, m_tInfo.fX, m_tInfo.fY);

	m_fTime += 0.5f;
	Update_Rect();
	return OBJ_NOEVENT;
}

void CMonster1::Late_Update()
{
	if (m_iLife < 0)
		m_bDead = true;
}

void CMonster1::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();
	//Rectangle(_DC, m_tRect.left + iScrollX, m_tRect.top+ iScrollY, m_tRect.right + iScrollX, m_tRect.bottom+ iScrollY);

	HDC hMemDC;

	float fTemp = m_fAngle + 5 * PI / 8;
	if (2 * PI < fTemp)
		fTemp -= 2 * PI;
	int i = int(4 * fTemp / PI);
	if (i >= 8)
		i = 7;

	switch (m_eState)
	{
	case STATE::IDLE:
		if (m_bEffect1)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BSkeletonIdle");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SkeletonIdle");
		GdiTransparentBlt(_DC
			, int(m_tInfo.fX - 40) + iScrollX, m_tRect.top + iScrollY
			, 80, 90
			, hMemDC
			, 80 * (int(m_fTime*m_fActionSpeed) % 16), 90 * i
			, 80, 90
			, RGB(255, 0, 153));
		break;
	case STATE::WALK:
		if (m_bEffect1)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BSkeletonWalk");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SkeletonWalk");
		GdiTransparentBlt(_DC
			, int(m_tInfo.fX - 41) + iScrollX, m_tRect.top + iScrollY
			, 82, 92
			, hMemDC
			, 82 * (int(m_fTime*m_fActionSpeed) % 11), 92 * i
			, 82, 92
			, RGB(255, 0, 153));
		break;
	case STATE::ATTACK:
		if ((m_fTime - m_fAttTime) > 20 / m_fActionSpeed)
		{
			m_eState = STATE::ATTACKIDLE;
			Render(_DC);
		}
		if (m_bEffect1)
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BSkeletonAttack");
		else
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SkeletonAttack");
		GdiTransparentBlt(_DC
			, int(m_tInfo.fX - 53) + iScrollX, m_tRect.top + iScrollY
			, 95, 95
			, hMemDC
			, 95 * int((m_fTime - m_fAttTime)*m_fActionSpeed), 95 * i
			, 95, 95
			, RGB(255, 0, 153));
		break;
	}
}

void CMonster1::Release()
{
}
