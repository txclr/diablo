#include "stdafx.h"
#include "Cain.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "MathMgr.h"
#include "Potal.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CCain::CCain()
{
}


CCain::~CCain()
{
}

void CCain::Initialize()
{
	m_tInfo.fX = 1300.f;
	m_tInfo.fY = 900.f;
	m_tInfo.iCX = 57;
	m_tInfo.iCY = 86;
	m_bEffect = true;
	m_bQuest = false;
	Update_Rect();
	m_eGroup = GROUPID::GAMEOBJECT;
}

int CCain::Update()
{
	if (40 > m_fTime && !m_bEffect)
	{
		Function();
	}
	if (70 > MathMgr::Get_Distance(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_Obj(OBJID::CAIN).front()) && m_bEffect)
	{
		CObj* pObj = CAbstractFactory<CPotal>::Create();
		CObjMgr::Get_Instance()->Add_Object(OBJID::POTAL, pObj);
		m_bEffect = false;
		m_bQuest = true;
		m_fTime = 0;
	}

	m_fTime += 0.1f;
	return OBJ_NOEVENT;
}

void CCain::Late_Update()
{
}

void CCain::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();
	//Rectangle(_DC, m_tRect.left + iScrollX, m_tRect.top+ iScrollY, m_tRect.right + iScrollX, m_tRect.bottom+ iScrollY);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Cain");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime) % 5), 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(170, 170, 170));
	if (m_bEffect)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Quest");
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX-30, m_tRect.top + iScrollY-70
			, 128, 128
			, hMemDC
			, 0, 0
			, 128, 128
			, RGB(255, 255, 255));
	}
	if (m_bQuest)
	{
		TCHAR		szBuff[32] = L"";
		wsprintf(szBuff, L"포탈을 열어주겠네 포탈을 타고 들어가서 봉인을 해제하고");
		TextOut(_DC, m_tRect.left-170 + iScrollX, m_tRect.top-20 + iScrollY, szBuff, lstrlen(szBuff));
		wsprintf(szBuff, L"디아블로를 처치해주게");
		TextOut(_DC, m_tRect.left-60 + iScrollX, m_tRect.top + iScrollY, szBuff, lstrlen(szBuff));

		if (50 < m_fTime)
			m_bQuest = false;
	}
}

void CCain::Release()
{
}

void CCain::Function()
{
	switch (int(m_fTime*7) % 3)
	{
	case 0:
		CSoundMgr::Get_Instance()->PlaySound(L"Cain_help1.wav", CSoundMgr::UI);
		break;
	case 1:
		CSoundMgr::Get_Instance()->PlaySound(L"Cain_help2.wav", CSoundMgr::UI);
		break;
	case 2:
		CSoundMgr::Get_Instance()->PlaySound(L"Cain_help2.wav", CSoundMgr::UI);
		break;
	}
}
