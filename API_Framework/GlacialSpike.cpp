#include "stdafx.h"
#include "GlacialSpike.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "GlacilBom.h"

CGlacialSpike::CGlacialSpike()
{
}


CGlacialSpike::~CGlacialSpike()
{
	CObj* pObj = CAbstractFactory<CGlacilBom>::Create(m_tInfo.fX, m_tInfo.fY+100, m_fAngle, m_iLife);
	CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
}

void CGlacialSpike::Initialize()
{
	m_tInfo.iCX = 56;
	m_tInfo.iCY = 198;

	m_fSpeed = 10.f;
	m_bEffect = true;

	m_eGroup = GROUPID::EFFECT;
}

int CGlacialSpike::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += 1;
	m_tInfo.fY += 20;

	m_fTime += 1;

	return OBJ_NOEVENT;
}

void CGlacialSpike::Late_Update()
{
	if (m_fTime > 12)
		m_bDead = true;
}

void CGlacialSpike::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"IceStorm");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime) % 6),0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(170, 170, 170));
}

void CGlacialSpike::Release()
{
}
