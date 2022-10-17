#include "stdafx.h"
#include "GlacilBom.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CGlacilBom::CGlacilBom()
{
}


CGlacilBom::~CGlacilBom()
{
}

void CGlacilBom::Initialize()
{
	m_tInfo.iCX = 143;
	m_tInfo.iCY = 107;
	m_eGroup = GROUPID::EFFECT;
	m_bEffect = true;
	m_bDie = false;
	switch (int(m_tInfo.fX) % 3)
	{
	case 0:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SKILL);
		CSoundMgr::Get_Instance()->PlaySound(L"sblizzboom1.wav", CSoundMgr::SKILL);
		break;
	case 1:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SKILL);
		CSoundMgr::Get_Instance()->PlaySound(L"sblizzboom2.wav", CSoundMgr::SKILL);
		break;
	case 2:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SKILL);
		CSoundMgr::Get_Instance()->PlaySound(L"sblizzboom3.wav", CSoundMgr::SKILL);
		break;
	}
	Update_Rect();
}

int CGlacilBom::Update()
{
	if (m_bDie)
		return OBJ_DEAD;

	m_fTime += 1;
	return OBJ_NOEVENT;
}

void CGlacilBom::Late_Update()
{
	if (m_fTime > 15)
		m_bDie = true;
}

void CGlacilBom::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"FreezeExplode");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime) % 15), 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(0, 0, 0));
}

void CGlacilBom::Release()
{
}
