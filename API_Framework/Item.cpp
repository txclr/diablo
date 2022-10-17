#include "stdafx.h"
#include "Item.h"
#include "BmpMgr.h"
#include "Mouse.h"
#include "Player.h"
#include "UIMgr.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CItem::CItem()
	:m_bDrop(false), m_bSash(false), m_bShop(false), m_iDropTime(0), m_eSlot(POTIONSLOT::END), m_iSlotNum(0)
{
	m_bOpen = false;
}

CItem::CItem(TCHAR * _pFramekey, INFO _tInfo, ITEMSTATE::STATE _eState)
{
	m_pFrameKey = _pFramekey;
	m_tInfo = _tInfo;
	m_eState = _eState;
	m_pBackFrame = L"";
	m_pDropFrame = L"AmorDrop";
	m_eType = ITEMTYPE::ARMOR;
	m_tItemInfo = {};
	m_tItemInfo.iDex = 10;
}


CItem::~CItem()
{
}

void CItem::Initialize()
{
}

void CItem::Update()
{
}

void CItem::Render(HDC _DC)
{
	Update_Rect();
	switch (m_eState)
	{
	case ITEMSTATE::FIELD:
		break;
	case ITEMSTATE::INVEN:
		if (!m_bOpen)
			return;
		//Rectangle(_DC, int(m_tInfo.fX), int(m_tInfo.fY), int(m_tInfo.fX + m_tInfo.iCX), int(m_tInfo.fY + m_tInfo.iCY));
		//m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"bBack");
		//CBmpMgr::Alpha_Blend(_DC, int(m_tInfo.fX), int(m_tInfo.fY), m_tInfo.iCX, m_tInfo.iCY, m_hMemDC, 0, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 255, 255), 150);
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(_DC
			, m_tRect.left, m_tRect.top
			, m_tInfo.iCX, m_tInfo.iCY
			, m_hMemDC
			, 0, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 0, 255));
		break;
	case ITEMSTATE::EQUIP:
		if (!m_bOpen && (ITEMTYPE::USE != m_eType))
			return;
		if (0 < m_iSlotNum && !m_bSash)
			return;
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(_DC
			, m_tRect.left, m_tRect.top
			, m_tInfo.iCX, m_tInfo.iCY
			, m_hMemDC
			, 0, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 0, 255));
		break;
	case ITEMSTATE::SHOP:
		if (!m_bShop)
			return;
		//Rectangle(_DC, int(m_tInfo.fX), int(m_tInfo.fY), int(m_tInfo.fX + m_tInfo.iCX), int(m_tInfo.fY + m_tInfo.iCY));
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(_DC
			, m_tRect.left, m_tRect.top
			, m_tInfo.iCX, m_tInfo.iCY
			, m_hMemDC
			, 0, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 0, 255));
		break;
	}
}

void CItem::Release()
{
}

void CItem::Function()
{
}

void CItem::Update_Rect()
{
	m_tRect = { LONG(m_tInfo.fX),LONG(m_tInfo.fY),LONG(m_tInfo.fX + m_tInfo.iCX),LONG(m_tInfo.fY + m_tInfo.iCY) };
}

void CItem::HandRender(HDC _DC)
{
	if (ITEMSTATE::HAND == m_eState)
	{
		INFO tTemp = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info();
		m_tInfo.fX = float(4 + 52 * int((tTemp.fX + 22 - (m_tInfo.iCX >> 1)) / 52));
		m_tInfo.fY = float(38 * int((tTemp.fY + 19 - (m_tInfo.iCY >> 1)) / 38));
		//µÞ¹è°æ
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pBackFrame);
		CBmpMgr::Alpha_Blend(_DC, int(tTemp.fX - (m_tInfo.iCX >> 1)), int(tTemp.fY - (m_tInfo.iCY >> 1)), m_tInfo.iCX, m_tInfo.iCY, m_hMemDC, 0, 0, m_tInfo.iCX, m_tInfo.iCY, RGB(255, 255, 255), 150);
		//
		//Rectangle(_DC, int(m_tInfo.fX), int(m_tInfo.fY), int(m_tInfo.fX + m_tInfo.iCX), int(m_tInfo.fY + m_tInfo.iCY));
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pFrameKey);
		GdiTransparentBlt(_DC
			, int(tTemp.fX - (m_tInfo.iCX >> 1)), int(tTemp.fY - (m_tInfo.iCY >> 1))
			, m_tInfo.iCX, m_tInfo.iCY
			, m_hMemDC
			, 0, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 0, 255));
	}
}

void CItem::Set_ItemState(ITEMSTATE::STATE _eState)
{
	switch (m_eType)
	{
	case ITEMTYPE::WEAPON:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"istaff.wav", CSoundMgr::ITEM);
		break;
	case ITEMTYPE::ARMOR:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"iplatearmor.wav", CSoundMgr::ITEM);
		break;
	case ITEMTYPE::HELM:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"ihelm.wav", CSoundMgr::ITEM);
		break;
	case ITEMTYPE::NECKLACE:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"iamulet.wav", CSoundMgr::ITEM);
		break;
	case ITEMTYPE::GLOVES:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"igloves.wav", CSoundMgr::ITEM);
		break;
	case ITEMTYPE::RING:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"iring.wav", CSoundMgr::ITEM);
		break;
	case ITEMTYPE::SASH:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"ibelt.wav", CSoundMgr::ITEM);
		break;
	case ITEMTYPE::BOOTS:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"iboots.wav", CSoundMgr::ITEM);
		break;
	case ITEMTYPE::USE:
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"ipotionui.wav", CSoundMgr::ITEM);
		break;
	case ITEMTYPE::END:
		break;
	default:
		break;
	}
	if(_eState == ITEMSTATE::EQUIP)
	{
		if(ITEMTYPE::USE != m_eType)
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
		if (ITEMTYPE::USE != m_eType)
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_ItemMinus(m_tItemInfo);
	}
	m_eState = _eState;
}
