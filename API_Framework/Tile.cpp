#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"


CTile::CTile()
	: m_iDrawID(0),m_bCheck(false), m_bAniCheck(false)
{
	m_iOption = 0;
	m_bEffect = false;
	m_pFrameKey = L"Base";
}


CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;

	m_fTime = 0;
	Update_Rect();
}

int CTile::Update()
{
	m_fTime += 0.1f;
	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC _DC)
{
	//m_fTime += 0.1f;
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	HDC hMemDC;
	if (m_bAniCheck)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Lava");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, m_tInfo.iCX * m_iDrawID, m_tInfo.iCY*(int(m_fTime) % 10)
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 0, 255));
	}
	else
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Tile");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, m_tInfo.iCX * m_iDrawID, m_iOption*m_tInfo.iCY
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 0, 255));
	}
	if (m_bCheck)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Target");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, 0, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 0, 255));
		m_bCheck = false;
	}
}

void CTile::Release()
{
}
