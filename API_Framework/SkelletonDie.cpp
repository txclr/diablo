#include "stdafx.h"
#include "SkelletonDie.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CSkelletonDie::CSkelletonDie()
{
}


CSkelletonDie::~CSkelletonDie()
{
}

void CSkelletonDie::Initialize()
{
	m_tInfo.iCX = 230;
	m_tInfo.iCY = 191;
	m_eGroup = GROUPID::EFFECT;
	Update_Rect();
	m_fTime = -0.5;

	float fTemp = m_fAngle + 5 * PI / 8;
	if (2 * PI < fTemp)
		fTemp -= 2 * PI;
	m_iOption = int(4 * fTemp / PI);
}

int CSkelletonDie::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	if (10 > m_fTime)
		m_fTime += 0.5f;
	else
		m_bDead = true;

	return OBJ_NOEVENT;
}

void CSkelletonDie::Late_Update()
{

}

void CSkelletonDie::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));
	
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SkeletonDie");
	GdiTransparentBlt(_DC
		, int(m_tInfo.fX) - 53 + iScrollX, m_tRect.top + iScrollY
		, 120, 112
		, hMemDC
		, 120 * (int(m_fTime)), 112 * m_iOption
		, 120, 112
		, RGB(255, 0, 153));

}

void CSkelletonDie::Release()
{
}
