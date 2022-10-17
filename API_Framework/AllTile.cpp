#include "stdafx.h"
#include "AllTile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CAllTile::CAllTile()
	: m_iDrawID(0)
{
	m_iOption = 0;
	m_bEffect = false;
	m_pFrameKey = L"Tile";
}


CAllTile::~CAllTile()
{
}

void CAllTile::Initialize()
{
	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;

	Update_Rect();
}

int CAllTile::Update()
{
	return OBJ_NOEVENT;
}

void CAllTile::Late_Update()
{
}

void CAllTile::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * m_iDrawID, m_iOption*m_tInfo.iCY
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 0, 255));
}

void CAllTile::Release()
{
}
