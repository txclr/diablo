#include "stdafx.h"
#include "Lava.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CLava::CLava()
	: m_iDrawID(0)
{
	m_bEffect = true;
	m_pFrameKey = L"Lava";
}



CLava::~CLava()
{
}

void CLava::Initialize()
{
	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;

	m_fTime = 0;
	Update_Rect();
}

int CLava::Update()
{
	return OBJ_NOEVENT;
}

void CLava::Late_Update()
{
}

void CLava::Render(HDC _DC)
{
	m_fTime += 0.1f;
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, m_tInfo.iCX * m_iDrawID, m_tInfo.iCY*(int(m_fTime) % 10)
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 0, 255));
}

void CLava::Release()
{
}
