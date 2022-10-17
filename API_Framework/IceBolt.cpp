#include "stdafx.h"
#include "IceBolt.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "Effect.h"

CIceBolt::CIceBolt()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SKILL);
	CSoundMgr::Get_Instance()->PlaySound(L"sicespike1.wav", CSoundMgr::SKILL);
}


CIceBolt::~CIceBolt()
{
	if (m_bDie)
	{
		CObj* pObj = CAbstractFactory<CEffect>::Create(m_tInfo.fX, m_tInfo.fY, true);
		CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
	}
}

void CIceBolt::Initialize()
{
	m_tInfo.iCX = 31;
	m_tInfo.iCY = 31;
	//이미지크기 70, 39
	m_fSpeed = 10.f;
	m_bEffect = true;
	m_bDie = true;

	float fTemp = m_fAngle + PI / 8;
	if (2*PI < fTemp)
		fTemp -= 2 * PI;
	m_iOption = int(4 * fTemp / PI);

	m_eGroup = GROUPID::EFFECT;
}

int CIceBolt::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed / 2;

	m_fTime += 1;

	return OBJ_NOEVENT;
}

void CIceBolt::Late_Update()
{
	if (m_fTime > 80)
	{
		m_bDead = true;
		m_bDie = false;
	}
}

void CIceBolt::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"IceBoltS");
	GdiTransparentBlt(_DC
		, m_tRect.left - 20 + iScrollX, m_tRect.top - 4 + iScrollY
		, 70, 39
		, hMemDC
		, 70*(int(m_fTime) %6), 39* m_iOption
		, 70, 39
		, RGB(170, 170, 170));
}

void CIceBolt::Release()
{
}
