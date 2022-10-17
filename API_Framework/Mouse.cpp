#include "stdafx.h"
#include "Mouse.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"

CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.iCX = 31;
	m_tInfo.iCY = 27;
	m_bOpen = true;
}

void CMouse::Update()
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);
	ShowCursor(FALSE);

	m_tInfo.fX = (float)pt.x;
	m_tInfo.fY = (float)pt.y;
	Update_Rect();
}

void CMouse::Render(HDC _DC)
{
	if (m_bOpen)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Mouse");
		GdiTransparentBlt(_DC
			, m_tRect.left, m_tRect.top
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, 0, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 255, 255));
	}
	m_bOpen = true;
}

void CMouse::Release()
{
}

void CMouse::Function()
{
}

