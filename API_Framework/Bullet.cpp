#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	m_tInfo.iCX = 47;
	m_tInfo.iCY = 24;

	m_fSpeed = 10.f;

	m_pFrameKey = L"Arrow";
	float fTemp = m_fAngle - 15 * PI / 32;
	if (0 > fTemp)
		fTemp += 2 * PI;
	m_iOption = int(16 * fTemp / PI);

	m_eGroup = GROUPID::EFFECT;
}

int CBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed/2;

	m_fTime += 1;

	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{
	if (m_fTime > 150)
		m_bDead = true;
}

void CBullet::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * m_iOption, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(0, 0, 0));
}

void CBullet::Release()
{
}
