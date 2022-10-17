#include "stdafx.h"
#include "FrostNova.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CFrostNova::CFrostNova()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SKILL);
	CSoundMgr::Get_Instance()->PlaySound(L"snovaice.wav", CSoundMgr::SKILL);
}


CFrostNova::~CFrostNova()
{
}

void CFrostNova::Initialize()
{
	m_tInfo.iCX = 31;
	m_tInfo.iCY = 31;
	//이미지크기 70, 39
	m_fSpeed = 8.f;
	m_bEffect = true;
	m_bDie = false;
	float fTemp = m_fAngle + PI / 8;
	if (2 * PI < fTemp)
		fTemp -= 2 * PI;
	m_iOption = int(4 * fTemp / PI);

	m_eGroup = GROUPID::BACKGROUND;
}

int CFrostNova::Update()
{
	if (m_bDie)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle) * m_fSpeed;
	m_tInfo.fY += sinf(m_fAngle) * m_fSpeed / 2;

	m_fTime += 1;

	return OBJ_NOEVENT;
}

void CFrostNova::Late_Update()
{
	if (m_fTime > 20)
		m_bDie = true;
}

void CFrostNova::Render(HDC _DC)
{
	Update_Rect();

	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();

	//Ellipse(_DC,long(m_tRect.left + iScrollX), long(m_tRect.top + iScrollY), long(m_tRect.right + iScrollX), long(m_tRect.bottom + iScrollY));

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"FrostNovaS");
	GdiTransparentBlt(_DC
		, m_tRect.left - 102 + iScrollX, m_tRect.top - 53 + iScrollY
		, 236, 138
		, hMemDC
		, 236 * (int(m_fTime*0.7) % 14), 138 * m_iOption
		, 236, 138
		, RGB(170, 170, 170));
}

void CFrostNova::Release()
{
}
