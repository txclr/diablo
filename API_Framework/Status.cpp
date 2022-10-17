#include "stdafx.h"
#include "Status.h"
#include "Player.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"

CStatus::CStatus()
	:m_bRun(false), m_bLevel(false)
{
}


CStatus::~CStatus()
{
	Release();
}

void CStatus::Initialize()
{
	m_tInfo = { 0,WINCY - 180,1400,180 };
	m_bOpen = false;
	Update_Rect();
}

void CStatus::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE))
		m_bOpen = false;
	m_tPlayerInfo = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_PlayerInfo();
	m_bLevel = 0 < m_tPlayerInfo.iRemainStat;
	if (m_bOpen)
	{
		float fX = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fX;
		float fY = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fY;

		if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
		{
			if (0 < m_tPlayerInfo.iRemainStat)
			{
				//Èû½ºÅÈ
				if (350 < fX && 402 > fX && 170 < fY && 222 > fY)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
					CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Str(1);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainStat();
				}
				//¹Î½ºÅÈ
				if (350 < fX && 402 > fX && 254 < fY && 306 > fY)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
					CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Dex(1);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainStat();
				}
				//»ý½ºÅÈ
				if (350 < fX && 402 > fX && 371 < fY && 423 > fY)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
					CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Life(1);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainStat();
				}
				//¿¡³ÊÁö
				if (350 < fX && 402 > fX && 455 < fY && 507 > fY)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
					CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Energy(1);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainStat();
				}
			}
			//´Ý±â
			if (350 < fX && 406 > fX && 599 < fY && 640 > fY)
			{
				m_bOpen = false;
			}
		}

		if (WINCX >> 1 > fX)
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
	}
	if (m_bLevel)
	{
		float fX = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fX;
		float fY = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fY;
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ButtonUp");
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			if (360 < fX && 412 > fX &&
				735 < fY && 787 > fY)
			{
				m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ButtonDown");
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
		{
			if (360 < fX && 412 > fX && 735 < fY && 787 > fY)
			{
				m_bOpen = true;
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
			}
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down('C'))
		m_bOpen = !m_bOpen;
}

void CStatus::Render(HDC _DC)
{
	HDC hMemDC;
	//ÅØ½ºÆ®Ã¢ º¯°æ
	SetTextColor(_DC, RGB(255, 255, 255));
	SetBkMode(_DC, TRANSPARENT);
	TCHAR pTemp[32] = L"";

	if (m_bOpen)
	{
		//Ä³¸¯ÅÍÃ¢
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"CharicInfo");
		BitBlt(_DC, 0, 0, 700, 734, hMemDC, 0, 0, SRCCOPY);
		//½ºÅÈ
		wsprintf(pTemp, L"%d", m_tPlayerInfo.iLevel);
		TextOut(_DC, 170, 135, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iStr);
		TextOut(_DC, 280, 190, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iDex);
		TextOut(_DC, 280, 275, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iLife);
		TextOut(_DC, 280, 390, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iEnergy);
		TextOut(_DC, 280, 475, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iRemainStat);
		TextOut(_DC, 305, 545, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iExp);
		TextOut(_DC, 320, 135, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iMaxExp);
		TextOut(_DC, 565, 135, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iStamina);
		TextOut(_DC, 560, 390, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iMaxStamina);
		TextOut(_DC, 635, 390, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iHp);
		TextOut(_DC, 560, 422, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iMaxHp);
		TextOut(_DC, 635, 422, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iMp);
		TextOut(_DC, 560, 475, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iMaxMp);
		TextOut(_DC, 635, 475, pTemp, lstrlen(pTemp));

		wsprintf(pTemp, L"%d", m_tPlayerInfo.iStr);
		TextOut(_DC, 625, 190, pTemp, lstrlen(pTemp));
		//½ºÅÈ¾÷ ¹öÆ°
		if (m_bLevel)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ButtonUp");
			BitBlt(_DC, 350, 170, 52, 52, hMemDC, 0, 0, SRCCOPY);

			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ButtonUp");
			BitBlt(_DC, 350, 254, 52, 52, hMemDC, 0, 0, SRCCOPY);

			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ButtonUp");
			BitBlt(_DC, 350, 371, 52, 52, hMemDC, 0, 0, SRCCOPY);

			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ButtonUp");
			BitBlt(_DC, 350, 455, 52, 52, hMemDC, 0, 0, SRCCOPY);
		}
	}

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"UI");
	GdiTransparentBlt(_DC
		, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_tInfo.iCX, m_tInfo.iCY
		, RGB(255, 255, 255));

	//°æÇèÄ¡¹Ù
	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ExpBar");
	BitBlt(_DC, 447, 734, 210 * (m_tPlayerInfo.iExp-m_tPlayerInfo.iBeforeExp) / (m_tPlayerInfo.iLevel * 100), 6, hMemDC, 0, 0, SRCCOPY);

	if (!m_bRun)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Walk");
		BitBlt(_DC, 447, 752, 26, 33, hMemDC, 0, 0, SRCCOPY);
	}
	if (m_bLevel)
		BitBlt(_DC, 360, 735, 52, 52, m_hMemDC, 0, 0, SRCCOPY);

	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"StaminaBar");
	BitBlt(_DC, 476, 751, int(181* (float(m_tPlayerInfo.iStamina) / float(m_tPlayerInfo.iMaxStamina))), 34, hMemDC, 0, 0, SRCCOPY);

	wsprintf(pTemp, L"¶óÀÌÇÁ : %u / %u", m_tPlayerInfo.iHp, m_tPlayerInfo.iMaxHp);
	TextOut(_DC, 50, 610, pTemp, lstrlen(pTemp));

	wsprintf(pTemp, L"¸¶³ª : %u / %u", m_tPlayerInfo.iMp, m_tPlayerInfo.iMaxMp);
	TextOut(_DC, 1240, 610, pTemp, lstrlen(pTemp));

}

void CStatus::Release()
{
}

void CStatus::Function()
{
}

