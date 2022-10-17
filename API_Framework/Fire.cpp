#include "stdafx.h"
#include "Fire.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CFire::CFire()
{
}


CFire::~CFire()
{
}

void CFire::Initialize()
{
	m_tInfo.iCX = 66;
	m_tInfo.iCY = 167;
	m_fSpeed = 10.f;
	m_bDie = false;

	m_eGroup = GROUPID::EFFECT;
}

int CFire::Update()
{
	if (m_bDie)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed / 2;

	m_fTime += 0.2f;

	return OBJ_NOEVENT;
}

void CFire::Late_Update()
{
	if (m_fTime > 37)
		m_bDie = true;
}

void CFire::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Fire");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * int(m_fTime),0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(0, 0, 0));
}

void CFire::Release()
{
}
