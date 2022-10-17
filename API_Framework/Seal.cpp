#include "stdafx.h"
#include "Seal.h"
#include "MyEvent.h"
#include "UIMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "MathMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

CSeal::CSeal()
{
	m_tInfo.fX = 1518;
	m_tInfo.fY = 1210;
	m_tInfo.iCX = 213;
	m_tInfo.iCY = 339;
}


CSeal::~CSeal()
{
}

void CSeal::Initialize()
{
	Update_Rect();
	m_eGroup = GROUPID::BACKGROUND;
}

int CSeal::Update()
{
	if (!m_bEffect)
	{
		if (100 > MathMgr::Get_Distance(CObjMgr::Get_Instance()->Get_Player(), this))
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
			CSoundMgr::Get_Instance()->PlaySound(L"Seal.wav", CSoundMgr::UI);
			m_bEffect = true;
			static_cast<CMyEvent*>(CUIMgr::Get_Instance()->Get_Event().front())->Set_SealPlus();
		}
	}
	if(m_bEffect && m_fTime < 19)
		m_fTime += 0.2f;
	return OBJ_NOEVENT;
}

void CSeal::Late_Update()
{
}

void CSeal::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_Scroll_X();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_Scroll_Y();
	//Rectangle(_DC, m_tRect.left + iScrollX, m_tRect.top+ iScrollY, m_tRect.right + iScrollX, m_tRect.bottom+ iScrollY);

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SealLeft");
	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tInfo.iCX * (int(m_fTime) % 20), 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(0, 0, 0));
}

void CSeal::Release()
{
}
