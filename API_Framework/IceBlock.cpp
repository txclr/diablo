#include "stdafx.h"
#include "IceBlock.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CIceBlock::CIceBlock()
{
	m_tInfo.iCX = 103;
	m_tInfo.iCY = 86;
	m_eGroup = GROUPID::EFFECT;
	Update_Rect();
}


CIceBlock::~CIceBlock()
{
}

void CIceBlock::Initialize()
{
	m_tInfo.iCX = 103;
	m_tInfo.iCY = 86;
	m_eGroup = GROUPID::EFFECT;
	Update_Rect();
	m_fTime = -0.5;

}

int CIceBlock::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (14 > m_fTime)
		m_fTime += 0.2f;
	else
		m_bDead = true;
	return OBJ_NOEVENT;
}

void CIceBlock::Late_Update()
{
}

void CIceBlock::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"IceBlock");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime)), 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 255, 255));

}

void CIceBlock::Release()
{
}
