#include "stdafx.h"
#include "IceBlast.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "Effect.h"
#include "ObjMgr.h"

CIceBlast::CIceBlast()
{
}


CIceBlast::~CIceBlast()
{
	CObj* pObj = CAbstractFactory<CEffect>::Create(m_tInfo.fX, m_tInfo.fY, true);
	CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
}

void CIceBlast::Initialize()
{
	m_tInfo.iCX = 31;
	m_tInfo.iCY = 31;
	m_fSpeed = 7.f;
	m_bEffect = true;

	float fTemp = m_fAngle + PI / 16;
	if (2 * PI < fTemp)
		fTemp -= 2 * PI;
	m_iOption = int(8 * fTemp / PI);

	m_eGroup = GROUPID::EFFECT;
}

int CIceBlast::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed / 2;

	m_fTime += 1;

	return OBJ_NOEVENT;
}

void CIceBlast::Late_Update()
{
	if (m_fTime > 150)
		m_bDead = true;
}

void CIceBlast::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"IceBlastS");
	GdiTransparentBlt(_DC
		, m_tRect.left - 69 + iScrollX, m_tRect.top - 31 + iScrollY
		, 169, 94
		, hMemDC
		, 169 * (int(m_fTime) % 5), 94 * m_iOption
		, 169, 94
		, RGB(170, 170, 170));
}

void CIceBlast::Release()
{
}
