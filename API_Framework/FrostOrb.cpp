#include "stdafx.h"
#include "FrostOrb.h"
#include "IceBolt.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "OrbDes.h"

CFrostOrb::CFrostOrb()
{
}


CFrostOrb::~CFrostOrb()
{
	CObj* pObj = CAbstractFactory<COrbDes>::Create(m_tInfo.fX, m_tInfo.fY, true);
	CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
	for (int i = 0; i < 16; ++i)
	{
		CObj* pObj = CAbstractFactory<CIceBolt>::Create(m_tInfo.fX + 50 * cosf(float(i*PI*0.125 + PI*0.5)), m_tInfo.fY + 25 * sinf(float(i*PI*0.125 + PI*0.5)), float(i*PI*0.125), m_iLife);
		CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
	}
}

void CFrostOrb::Initialize()
{
	m_tInfo.iCX = 54;
	m_tInfo.iCY = 53;
	m_fSpeed = 4.f;
	m_fAngle1 = 0;
	m_fShotTime = 0;

	m_eGroup = GROUPID::EFFECT;
}

int CFrostOrb::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed / 2;

	if (m_fShotTime < m_fTime)
	{
		CObj* pObj = CAbstractFactory<CIceBolt>::Create(m_tInfo.fX, m_tInfo.fY, m_fAngle1,m_iLife);
		CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
		m_fAngle1 += PI*1.25;
		if (2 * PI < m_fAngle1)
			m_fAngle1 -= 2 * PI;
		m_fShotTime = m_fTime + 4;
	}

	m_fTime += 1;
	return OBJ_NOEVENT;
}

void CFrostOrb::Late_Update()
{
	if (m_fTime > 100)
		m_bDead = true;
}

void CFrostOrb::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"FrostOrbS");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime) % 16),0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(170, 170, 170));
}

void CFrostOrb::Release()
{
}
