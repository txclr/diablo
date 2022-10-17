#include "stdafx.h"
#include "Sash.h"
#include "UIMgr.h"
#include "Mouse.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CSash::CSash()
{
}

CSash::CSash(float _fX, float _fY, ITEMSTATE::STATE _eState)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
	m_eState = _eState;
}


CSash::~CSash()
{
}

void CSash::Initialize()
{
	m_pFrameKey = L"Sash";
	m_pBackFrame = L"";
	m_pDropFrame = L"ArmorDrop";
	m_tInfo.iCX = 104;
	m_tInfo.iCY = 38;
	m_eType = ITEMTYPE::SASH;
	m_tItemInfo = {};
	m_tItemInfo.iGold = 300;
}

void CSash::FieldRender(HDC _DC)
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

void CSash::InfoRender(HDC _DC)
{
	INFO tTemp = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info();
	SetTextColor(_DC, RGB(0, 0, 0));
	SetBkMode(_DC, OPAQUE);
	TCHAR pTemp[32] = L"";
	wsprintf(pTemp, L"��Ʈ", m_tInfo.fX);
	TextOut(_DC, int(tTemp.fX), int(tTemp.fY), pTemp, lstrlen(pTemp));
	if (ITEMSTATE::FIELD == m_eState)
		return;
	wsprintf(pTemp, L"���ཽ�� �߰�", m_tInfo.fX);
	TextOut(_DC, int(tTemp.fX), int(tTemp.fY) + 15, pTemp, lstrlen(pTemp));
	wsprintf(pTemp, L"300 ���", m_tInfo.fX);
	TextOut(_DC, int(tTemp.fX), int(tTemp.fY) + 30, pTemp, lstrlen(pTemp));
}

void CSash::SizeReverse()
{
	m_tInfo.iCX = 104;
	m_tInfo.iCY = 38;
}
