#include "stdafx.h"
#include "DiaLightning.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CDiaLightning::CDiaLightning()
{
}


CDiaLightning::~CDiaLightning()
{
}

void CDiaLightning::Initialize()
{
	m_tInfo.iCX = 50;
	m_tInfo.iCY = 50;
	m_fSpeed = 15.f;
	m_bDie = false;

	float fTemp = m_fAngle + PI / 8;
	if (2 * PI < fTemp)
		fTemp -= 2 * PI;
	m_iOption = int(4 * fTemp / PI);


	m_eGroup = GROUPID::EFFECT;
}

int CDiaLightning::Update()
{
	if (m_bDie)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed / 2;

	m_fTime += 0.2f;

	return OBJ_NOEVENT;
}

void CDiaLightning::Late_Update()
{
	if (m_fTime > 15)
		m_bDie = true;
}

void CDiaLightning::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DiaLightning");
	GdiTransparentBlt(_DC
		, m_tRect.left - 101 + iScrollX, m_tRect.top - 70 + iScrollY
		, 252, 190
		, hMemDC
		, 252 * (int(m_fTime*5)%14), 190 *m_iOption
		, 252, 190
		, RGB(0, 0, 0));
}

void CDiaLightning::Release()
{
}
