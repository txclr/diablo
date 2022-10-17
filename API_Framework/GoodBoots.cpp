#include "stdafx.h"
#include "GoodBoots.h"
#include "UIMgr.h"
#include "Mouse.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"
#include "Player.h"
#include "ObjMgr.h"

CGoodBoots::CGoodBoots()
{
}

CGoodBoots::CGoodBoots(float _fX, float _fY, ITEMSTATE::STATE _eState)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eState = _eState;
}


CGoodBoots::~CGoodBoots()
{
}

void CGoodBoots::Initialize()
{
	m_pFrameKey = L"Boots1";
	m_pBackFrame = L"";
	m_pDropFrame = L"ArmorDrop";
	m_tInfo.iCX = 104;
	m_tInfo.iCY = 76;
	m_eType = ITEMTYPE::BOOTS;
	m_tItemInfo = {};
	m_tItemInfo.iMoveSpeed = 2;
	m_tItemInfo.iGold = 300;
}

void CGoodBoots::Set_ItemState(ITEMSTATE::STATE _eState)
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
	CSoundMgr::Get_Instance()->PlaySound(L"ibootsmetal.wav", CSoundMgr::ITEM);
	if (_eState == ITEMSTATE::EQUIP)
	{
		if (ITEMTYPE::USE != m_eType)
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_ItemPlus(m_tItemInfo);
	}
	else if (_eState == ITEMSTATE::FIELD)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"iflippy.wav", CSoundMgr::ITEM);
		m_bDrop = true;
		m_iDropTime = 0;
	}
	else if (m_eState == ITEMSTATE::EQUIP)
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_ItemMinus(m_tItemInfo);
	}
	m_eState = _eState;
}

void CGoodBoots::FieldRender(HDC _DC)
{
	if (ITEMSTATE::FIELD == m_eState)
	{
		if (m_bDrop)
		{
			m_iDropTime += 1;
			if (14 == m_iDropTime)
				m_bDrop = false;
		}
		m_tInfo.fX = m_tDropPos.x + CScrollMgr::Get_Instance()->Get_Scroll_X();
		m_tInfo.fY = m_tDropPos.y + CScrollMgr::Get_Instance()->Get_Scroll_Y();
		Update_Rect();
		//Rectangle(_DC, int(m_tInfo.fX), int(m_tInfo.fY), int(m_tInfo.fX + m_tInfo.iCX), int(m_tInfo.fY + m_tInfo.iCY));
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pDropFrame);
		GdiTransparentBlt(_DC
			, m_tRect.left - 20, m_tRect.top - 125
			, 96, 160
			, m_hMemDC
			, 96 * m_iDropTime, 0
			, 96, 160
			, RGB(255, 0, 255));
	}
}

void CGoodBoots::InfoRender(HDC _DC)
{
	INFO tTemp = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info();
	SetTextColor(_DC, RGB(0, 0, 0));
	SetBkMode(_DC, OPAQUE);
	TCHAR pTemp[32] = L"";
	wsprintf(pTemp, L"¡¡¿∫∫Œ√˜", m_tInfo.fX);
	TextOut(_DC, int(tTemp.fX), int(tTemp.fY), pTemp, lstrlen(pTemp));
	if (ITEMSTATE::FIELD == m_eState)
		return;
	wsprintf(pTemp, L"¿Ãµøº”µµ: 2", m_tInfo.fX);
	TextOut(_DC, int(tTemp.fX), int(tTemp.fY) + 15, pTemp, lstrlen(pTemp));
	wsprintf(pTemp, L"300 ∞ÒµÂ", m_tInfo.fX);
	TextOut(_DC, int(tTemp.fX), int(tTemp.fY) + 30, pTemp, lstrlen(pTemp));
}

void CGoodBoots::SizeReverse()
{
	m_tInfo.iCX = 104;
	m_tInfo.iCY = 76;
}