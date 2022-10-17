#include "stdafx.h"
#include "Seller.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "MathMgr.h"
#include "ObjMgr.h"

CSeller::CSeller()
{
}


CSeller::~CSeller()
{
}

void CSeller::Initialize()
{
	m_tInfo.fX = 1000.f;
	m_tInfo.fY = 1100.f;
	m_tInfo.iCX = 200;
	m_tInfo.iCY = 200;
	Update_Rect();
	m_eGroup = GROUPID::GAMEOBJECT;
}

int CSeller::Update()
{
	m_fTime += 0.1f;
	return OBJ_NOEVENT;
}

void CSeller::Late_Update()
{
}

void CSeller::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();
	//Rectangle(_DC, m_tRect.left + iScrollX, m_tRect.top+ iScrollY, m_tRect.right + iScrollX, m_tRect.bottom+ iScrollY);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Seller");

	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime) % 9), 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(170, 170, 170));
}

void CSeller::Release()
{
}