#include "stdafx.h"
#include "Blizzard.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "GlacialSpike.h"

CBlizzard::CBlizzard()
{
}


CBlizzard::~CBlizzard()
{
}

void CBlizzard::Initialize()
{
	m_eGroup = GROUPID::EFFECT;
	m_fShotTime = 0;
	m_fTime = 0;
}

int CBlizzard::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	if (m_fShotTime < m_fTime)
	{
		CObj* pObj = CAbstractFactory<CGlacialSpike>::Create(m_tInfo.fX + float(rand()*0.0122-225), m_tInfo.fY + float(rand()*0.0122 - 560), m_fAngle, m_iLife);
		CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
		m_fShotTime = m_fTime + 15;
	}

	m_fTime += 1;
	return OBJ_NOEVENT;
}

void CBlizzard::Late_Update()
{
	if (m_fTime > 150)
		m_bDead = true;
}

void CBlizzard::Render(HDC _DC)
{
}

void CBlizzard::Release()
{
}
