#include "stdafx.h"
#include "OrbDes.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

COrbDes::COrbDes()
{
}


COrbDes::~COrbDes()
{
}

void COrbDes::Initialize()
{
	m_tInfo.iCX = 230;
	m_tInfo.iCY = 191;
	m_eGroup = GROUPID::EFFECT;
	Update_Rect();
}

int COrbDes::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fTime += 1;
	return OBJ_NOEVENT;
}

void COrbDes::Late_Update()
{
	if (m_fTime > 32)
		m_bDead = true;
}

void COrbDes::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"IceOrbExplode");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime*0.5) % 17), 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(0, 0, 0));
}

void COrbDes::Release()
{
}
