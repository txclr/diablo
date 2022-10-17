#include "stdafx.h"
#include "ChargedBolt.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CChargedBolt::CChargedBolt()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SKILL);
	CSoundMgr::Get_Instance()->PlaySound(L"sElectricOrb.wav", CSoundMgr::SKILL);
}


CChargedBolt::~CChargedBolt()
{
}

void CChargedBolt::Initialize()
{
	m_tInfo.iCX = 85;
	m_tInfo.iCY = 78;

	m_fSpeed = 4.f;

	float fTemp = m_fAngle;
	m_iFrame = int(4 * fTemp / PI);

	m_eGroup = GROUPID::EFFECT;
}

int CChargedBolt::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed / 2;

	m_fTime += 1;

	return OBJ_NOEVENT;
}

void CChargedBolt::Late_Update()
{
	if (m_fTime > 150)
		m_bDead = true;
}

void CChargedBolt::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ChargedBoltS");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime /5)%10), m_tInfo.iCY * m_iFrame
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(170, 170, 170));
}

void CChargedBolt::Release()
{
}
