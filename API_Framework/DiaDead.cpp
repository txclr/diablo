#include "stdafx.h"
#include "DiaDead.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CDiaDead::CDiaDead()
{
	m_tInfo.iCX = 279;
	m_tInfo.iCY = 329;
	m_eGroup = GROUPID::BACKGROUND;
	Update_Rect();
}


CDiaDead::~CDiaDead()
{
}

void CDiaDead::Initialize()
{
	Update_Rect();
	m_fTime = -0.3f;
}

int CDiaDead::Update()
{

	if (141 > m_fTime)
		m_fTime += 0.3f;

	return OBJ_NOEVENT;
}

void CDiaDead::Late_Update()
{
}

void CDiaDead::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DiaDie");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime)), 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(170, 170, 170));
}

void CDiaDead::Release()
{
}
