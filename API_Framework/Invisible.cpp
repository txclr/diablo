#include "stdafx.h"
#include "Invisible.h"
#include "ScrollMgr.h"

CInvisible::CInvisible()
{
}


CInvisible::~CInvisible()
{
}

void CInvisible::Initialize()
{
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 100;

	m_fSpeed = 6.f;

	m_eGroup = GROUPID::EFFECT;
}

int CInvisible::Update()
{
	if (m_bEffect)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed*2;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed;

	Update_Rect();

	m_fTime += 1;

	return OBJ_NOEVENT;
}

void CInvisible::Late_Update()
{
	if (m_fTime > 80)
		m_bEffect = true;
}

void CInvisible::Render(HDC _DC)
{
	//Update_Rect();

	//int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	//int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));
}

void CInvisible::Release()
{
}
