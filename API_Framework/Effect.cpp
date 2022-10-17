#include "stdafx.h"
#include "Effect.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CEffect::CEffect()
{
}


CEffect::~CEffect()
{
}

void CEffect::Initialize()
{
	m_tInfo.iCX = 130;
	m_tInfo.iCY = 140;
	m_eGroup = GROUPID::EFFECT;
	Update_Rect();
}

int CEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fTime += 1;
	return OBJ_NOEVENT;
}

void CEffect::Late_Update()
{
	if (m_fTime > 32)
		m_bDead = true;
}

void CEffect::Render(HDC _DC)
{

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"IceHit");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime*0.5) % 16), 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(170, 170, 170));
}

void CEffect::Release()
{
}
