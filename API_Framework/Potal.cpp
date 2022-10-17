#include "stdafx.h"
#include "Potal.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "MathMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CPotal::CPotal()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"portalcast.wav", CSoundMgr::EFFECT);
	m_tInfo.fX = 1518;
	m_tInfo.fY = 1210;
	m_tInfo.iCX = 200;
	m_tInfo.iCY = 200;
}


CPotal::~CPotal()
{
}

void CPotal::Initialize()
{
	Update_Rect();
	m_eGroup = GROUPID::GAMEOBJECT;
}

int CPotal::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	m_fTime += 0.5f;
	return OBJ_NOEVENT;
}

void CPotal::Late_Update()
{
	if (m_bEffect && m_fTime > 30)
		m_bDead = true;
		
}

void CPotal::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();
	//Rectangle(_DC, m_tRect.left + iScrollX, m_tRect.top+ iScrollY, m_tRect.right + iScrollX, m_tRect.bottom+ iScrollY);
	if (15 > m_fTime)
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"CreatePortal");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, m_tInfo.iCX * (int(m_fTime) % 15), 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(0, 0, 0));
	}
	else
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ProgressPortal");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, m_tInfo.iCX * (int(m_fTime) % 15), 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(0, 0, 0));
	}

}

void CPotal::Release()
{
}
