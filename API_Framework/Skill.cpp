#include "stdafx.h"
#include "Skill.h"
#include "BmpMgr.h"
#include "Player.h"
#include "SorcerSkill.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"

CSkill::CSkill()
	:m_pMainSkill(nullptr), m_iLevel(0)
{
	memset(m_pFSkill, 0, sizeof(m_pFSkill));
	memset(m_pSkill, 0, sizeof(m_pSkill));
}


CSkill::~CSkill()
{
	Release();
}

void CSkill::Initialize()
{
	//SKILLINFO* pTemp = new SKILLINFO;
	//pTemp->Skill = Teleport;
	//pTemp->pFrameKey = L"Teleport";
	//pTemp->iLevel = 0;
	//pTemp->iUseMp = 30;
	//m_vecpSkillInfo.emplace_back(pTemp);
	//m_pSkill[SKILL::TELLEPORT] = pTemp;
	//
	//m_pMainSkill = m_vecpSkillInfo[0];
	//static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);

	m_tInfo = { 1114,720,80,80 };
	Update_Rect();
	m_bOpen = false;
	m_bQuick = false;
	m_bFcheck = true;
	m_iBack = 0;
}

void CSkill::Update()
{
	m_iLevel = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_iRemainSkill();
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		m_bQuick = false;
		m_bOpen = false;
	}
	if (m_iLevel)
	{
		float fX = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fX;
		float fY = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fY;
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ButtonUp");
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			if (985 < fX && 1040 > fX &&
				735 < fY && 787 > fY)
			{
				m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ButtonDown");
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
		{
			if (985 < fX && 1040 > fX && 735 < fY && 787 > fY)
			{
				m_bOpen = true;
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
			}
		}
	}
	SkillUp();
	Key();
}

void CSkill::Render(HDC _DC)
{
	HDC hMemDC;
	if (m_bOpen)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"SkillTree");
		BitBlt(_DC, WINCX >> 1, 0, 700, 734, hMemDC, 0, 0, SRCCOPY);

		TCHAR pTemp[32] = L"";
		wsprintf(pTemp, L"%d", m_iLevel);
		TextOut(_DC, 1190, 160, pTemp, lstrlen(pTemp));

		if (m_pSkill[SKILL::ICEBOLT])
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"IceBoltA");
			BitBlt(_DC, 872, 85, 83, 68, hMemDC, 0, 0, SRCCOPY);
			wsprintf(pTemp, L"%d", m_pSkill[SKILL::ICEBOLT]->iLevel);
			TextOut(_DC, 953, 153, pTemp, lstrlen(pTemp));
		}

		if (m_pSkill[SKILL::ICEBLAST])
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"IceBlastA");
			BitBlt(_DC, 872, 180, 83, 68, hMemDC, 0, 0, SRCCOPY);
			wsprintf(pTemp, L"%d", m_pSkill[SKILL::ICEBLAST]->iLevel);
			TextOut(_DC, 953, 248, pTemp, lstrlen(pTemp));
		}

		if (m_pSkill[SKILL::GLACIALSPIKE])
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"GlacialSpikeA");
			BitBlt(_DC, 872, 373, 83, 68, hMemDC, 0, 0, SRCCOPY);
			wsprintf(pTemp, L"%d", m_pSkill[SKILL::GLACIALSPIKE]->iLevel);
			TextOut(_DC, 953, 441, pTemp, lstrlen(pTemp));
		}
		//753 < fX && 835 > fX && 470 < fY && 538 > fY)
		if (m_pSkill[SKILL::FROSTNOVA])
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"FrostNovaA");
			BitBlt(_DC, 753, 180, 83, 68, hMemDC, 0, 0, SRCCOPY);
			wsprintf(pTemp, L"%d", m_pSkill[SKILL::FROSTNOVA]->iLevel);
			TextOut(_DC, 834, 248, pTemp, lstrlen(pTemp));
		}

		if (m_pSkill[SKILL::BLIZZARD])
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BlizzardA");
			BitBlt(_DC, 753, 470, 83, 68, hMemDC, 0, 0, SRCCOPY);
			wsprintf(pTemp, L"%d", m_pSkill[SKILL::BLIZZARD]->iLevel);
			TextOut(_DC, 834, 538, pTemp, lstrlen(pTemp));
		}

		if (m_pSkill[SKILL::FROZENORB])
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"FrozenOrbA");
			BitBlt(_DC, 753, 566, 83, 68, hMemDC, 0, 0, SRCCOPY);
			wsprintf(pTemp, L"%d", m_pSkill[SKILL::FROZENORB]->iLevel);
			TextOut(_DC, 834, 634, pTemp, lstrlen(pTemp));
		}

		if (m_pSkill[SKILL::TELLEPORT])
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"TeleportA");
			BitBlt(_DC, 989, 85, 83, 68, hMemDC, 0, 0, SRCCOPY);
			wsprintf(pTemp, L"%d", m_pSkill[SKILL::TELLEPORT]->iLevel);
			TextOut(_DC, 1070, 153, pTemp, lstrlen(pTemp));
		}

		if (m_pSkill[SKILL::CHARGEDBOLT])
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"ChargedBoltA");
			BitBlt(_DC, 989, 277, 83, 68, hMemDC, 0, 0, SRCCOPY);
			wsprintf(pTemp, L"%d", m_pSkill[SKILL::CHARGEDBOLT]->iLevel);
			TextOut(_DC, 1070, 345, pTemp, lstrlen(pTemp));
		}

		if (m_pSkill[SKILL::MULTISHOT])
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MultiShotA");
			BitBlt(_DC, 989, 470, 83, 68, hMemDC, 0, 0, SRCCOPY);
			wsprintf(pTemp, L"%d", m_pSkill[SKILL::MULTISHOT]->iLevel);
			TextOut(_DC, 1070, 538, pTemp, lstrlen(pTemp));
		}
	}
	if (m_pMainSkill)
	{
		hMemDC = CBmpMgr::Get_Instance()->Find_Image(m_pMainSkill->pFrameKey);
		GdiTransparentBlt(_DC
			, int(m_tInfo.fX + m_iBack), int(m_tInfo.fY + m_iBack)
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, 0, 0
			, m_tInfo.iCX, m_tInfo.iCY
			, RGB(255, 255, 255));
		//SetBkMode(_DC, TRANSPARENT);
		TextOut(_DC, int(m_tInfo.fX + m_iBack), int(m_tInfo.fY + m_iBack), m_pMainSkill->pFKeyMatch, lstrlen(m_pMainSkill->pFKeyMatch));
	}
	if (m_iLevel)
	{
		BitBlt(_DC, 987, 735, 52, 52, m_hMemDC, 0, 0, SRCCOPY);
	}

	if (m_bQuick)
	{
		int i = 0;
		for (auto& Info : m_vecpSkillInfo)
		{
			hMemDC = CBmpMgr::Get_Instance()->Find_Image(Info->pFrameKey);
			GdiTransparentBlt(_DC
				, int(m_tInfo.fX-i*m_tInfo.iCX), int(m_tInfo.fY - m_tInfo.iCY-2)
				, m_tInfo.iCX, m_tInfo.iCY
				, hMemDC
				, 0, 0
				, m_tInfo.iCX, m_tInfo.iCY
				, RGB(255, 255, 255));
			//SetBkMode(_DC, TRANSPARENT);
			TextOut(_DC, int(m_tInfo.fX - i*m_tInfo.iCX), int(m_tInfo.fY - m_tInfo.iCY - 2), Info->pFKeyMatch, lstrlen(Info->pFKeyMatch));
			++i;
		}
	}
	m_iBack = 0;
}

void CSkill::Release()
{
	for (auto& i : m_vecpSkillInfo)
	{
		SAFE_DELETE(i);
	}
	m_vecpSkillInfo.clear();
}

void CSkill::Key()
{
	float fX = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fX;
	float fY = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fY;
	if (CKeyMgr::Get_Instance()->Key_Down('K'))
		m_bOpen = !m_bOpen;
	if (m_bQuick)
	{
		if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					m_pMainSkill = iter;
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
				}
				++i;
			}
		}

		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F1])
					{
						m_pFSkill[SKILLSLOT::F1]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F1]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F1] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F1];
					iter->pFKeyMatch = L"F1";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F1])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F1];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F2])
					{
						m_pFSkill[SKILLSLOT::F2]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F2]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F2] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F2];
					iter->pFKeyMatch = L"F2";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F2])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F2];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F3])
					{
						m_pFSkill[SKILLSLOT::F3]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F3]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F3] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F3];
					iter->pFKeyMatch = L"F3";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F3])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F3];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F4))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F4])
					{
						m_pFSkill[SKILLSLOT::F4]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F4]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F4] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F4];
					iter->pFKeyMatch = L"F4";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F4])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F4];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F5))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F5])
					{
						m_pFSkill[SKILLSLOT::F5]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F5]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F5] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F5];
					iter->pFKeyMatch = L"F5";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F5])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F5];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F6))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F6])
					{
						m_pFSkill[SKILLSLOT::F6]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F6]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F6] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F6];
					iter->pFKeyMatch = L"F6";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F6])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F6];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F7))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F7])
					{
						m_pFSkill[SKILLSLOT::F7]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F7]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F7] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F7];
					iter->pFKeyMatch = L"F7";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F7])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F7];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F8))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F8])
					{
						m_pFSkill[SKILLSLOT::F8]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F8]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F8] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F8];
					iter->pFKeyMatch = L"F8";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F8])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F8];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F9))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F9])
					{
						m_pFSkill[SKILLSLOT::F9]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F9]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F9] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F9];
					iter->pFKeyMatch = L"F9";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F9])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F9];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F10))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F10])
					{
						m_pFSkill[SKILLSLOT::F10]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F10]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F10] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F10];
					iter->pFKeyMatch = L"F10";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F10])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F10];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F11))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F11])
					{
						m_pFSkill[SKILLSLOT::F11]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F11]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F11] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F11];
					iter->pFKeyMatch = L"F11";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F11])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F11];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F12))
		{
			int i = 0;
			for (auto& iter : m_vecpSkillInfo)
			{
				if (m_tInfo.fX - i*m_tInfo.iCX < fX && m_tInfo.fX - m_tInfo.iCX*(i - 1) > fX &&
					(m_tInfo.fY - m_tInfo.iCY - 2) < fY && (m_tInfo.fY - 2) > fY)
				{
					if (m_pFSkill[SKILLSLOT::F12])
					{
						m_pFSkill[SKILLSLOT::F12]->pFKeyMatch = L"";
						m_pFSkill[SKILLSLOT::F12]->tKeyFind = nullptr;
					}
					m_pFSkill[SKILLSLOT::F12] = iter;
					if (iter->tKeyFind)
						*(iter->tKeyFind) = nullptr;
					iter->tKeyFind = &m_pFSkill[SKILLSLOT::F12];
					iter->pFKeyMatch = L"F12";
					m_bFcheck = false;
				}
				++i;
			}
			if (m_bFcheck)
				if (m_pFSkill[SKILLSLOT::F12])
				{
					m_pMainSkill = m_pFSkill[SKILLSLOT::F12];
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
				}
		}
		m_bFcheck = true;
	}
	else
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
		{
			if (m_pFSkill[SKILLSLOT::F1])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F1];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
		{
			if (m_pFSkill[SKILLSLOT::F2])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F2];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F3))
		{
			if (m_pFSkill[SKILLSLOT::F3])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F3];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F4))
		{
			if (m_pFSkill[SKILLSLOT::F4])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F4];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F5))
		{
			if (m_pFSkill[SKILLSLOT::F5])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F5];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F6))
		{
			if (m_pFSkill[SKILLSLOT::F6])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F6];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F7))
		{
			if (m_pFSkill[SKILLSLOT::F7])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F7];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F8))
		{
			if (m_pFSkill[SKILLSLOT::F8])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F8];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F9))
		{
			if (m_pFSkill[SKILLSLOT::F9])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F9];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F10))
		{
			if (m_pFSkill[SKILLSLOT::F10])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F10];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F11))
		{
			if (m_pFSkill[SKILLSLOT::F11])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F11];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
		else if (CKeyMgr::Get_Instance()->Key_Down(VK_F12))
		{
			if (m_pFSkill[SKILLSLOT::F12])
			{
				m_pMainSkill = m_pFSkill[SKILLSLOT::F12];
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_MainSkill(m_pMainSkill);
			}
		}
	}
}

void CSkill::SkillUp()
{
	if (m_bOpen)
	{
		float fX = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fX;
		float fY = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fY;
		if (700 < fX)
		{
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
			if (m_iLevel && CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
			{
				//아이스볼트
				if (872 < fX && 954 > fX && 85 < fY && 153 > fY)
				{
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainSkill();
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
					CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
					if (m_pSkill[SKILL::ICEBOLT])
					{
						m_pSkill[SKILL::ICEBOLT]->iLevel += 1;
						m_pSkill[SKILL::ICEBOLT]->iUseMp += 5;
					}
					else
					{
						SKILLINFO* pTemp = new SKILLINFO;
						pTemp->Skill = IceBolt;
						pTemp->pFrameKey = L"IceBolt";
						pTemp->iLevel = 1;
						pTemp->iUseMp = 10;
						m_vecpSkillInfo.emplace_back(pTemp);
						m_pSkill[SKILL::ICEBOLT] = pTemp;
					}
				}
				//아이스블라스트
				if (m_pSkill[SKILL::ICEBOLT])
				{
					if (872 < fX && 954 > fX && 180 < fY && 249 > fY)
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainSkill();
						CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
						CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
						if (m_pSkill[SKILL::ICEBLAST])
						{
							m_pSkill[SKILL::ICEBLAST]->iLevel += 1;
							m_pSkill[SKILL::ICEBLAST]->iUseMp += 5;
						}
						else
						{
							SKILLINFO* pTemp = new SKILLINFO;
							pTemp->Skill = IceBlast;
							pTemp->pFrameKey = L"IceBlast";
							pTemp->iLevel = 1;
							pTemp->iUseMp = 15;
							m_vecpSkillInfo.emplace_back(pTemp);
							m_pSkill[SKILL::ICEBLAST] = pTemp;
						}
					}
				}
				//프로스트노바
				if (753 < fX && 835 > fX && 180 < fY && 249 > fY)
				{
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainSkill();
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
					CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
					if (m_pSkill[SKILL::FROSTNOVA])
					{
						m_pSkill[SKILL::FROSTNOVA]->iLevel += 1;
						m_pSkill[SKILL::FROSTNOVA]->iUseMp += 5;
					}
					else
					{
						SKILLINFO* pTemp = new SKILLINFO;
						pTemp->Skill = FrostNova;
						pTemp->pFrameKey = L"FrostNova";
						pTemp->iLevel = 1;
						pTemp->iUseMp = 10;
						m_vecpSkillInfo.emplace_back(pTemp);
						m_pSkill[SKILL::FROSTNOVA] = pTemp;
					}
				}
				//글래셜스파이크
				if (m_pSkill[SKILL::ICEBLAST])
				{
					if (872 < fX && 954 > fX && 373 < fY && 441 > fY)
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainSkill();
						CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
						CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
						if (m_pSkill[SKILL::GLACIALSPIKE])
						{
							m_pSkill[SKILL::GLACIALSPIKE]->iLevel += 1;
							m_pSkill[SKILL::GLACIALSPIKE]->iUseMp += 5;
						}
						else
						{
							SKILLINFO* pTemp = new SKILLINFO;
							pTemp->Skill = GlacialSpike;
							pTemp->pFrameKey = L"GlacialSpike";
							pTemp->iLevel = 1;
							pTemp->iUseMp = 20;
							m_vecpSkillInfo.emplace_back(pTemp);
							m_pSkill[SKILL::GLACIALSPIKE] = pTemp;
						}
					}
				}
				//블리자드
				if (m_pSkill[SKILL::GLACIALSPIKE] && m_pSkill[SKILL::FROSTNOVA])
				{
					if (753 < fX && 835 > fX && 470 < fY && 538 > fY)
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainSkill();
						CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
						CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
						if (m_pSkill[SKILL::BLIZZARD])
						{
							m_pSkill[SKILL::BLIZZARD]->iLevel += 1;
							m_pSkill[SKILL::BLIZZARD]->iUseMp += 5;
						}
						else
						{
							SKILLINFO* pTemp = new SKILLINFO;
							pTemp->Skill = Blizzard;
							pTemp->pFrameKey = L"Blizzard";
							pTemp->iLevel = 1;
							pTemp->iUseMp = 30;
							m_vecpSkillInfo.emplace_back(pTemp);
							m_pSkill[SKILL::BLIZZARD] = pTemp;
						}
					}
				}
				//프로스트오브
				if (m_pSkill[SKILL::BLIZZARD])
				{
					if (753 < fX && 835 > fX && 566 < fY && 635 > fY)
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainSkill();
						CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
						CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
						if (m_pSkill[SKILL::FROZENORB])
						{
							m_pSkill[SKILL::FROZENORB]->iLevel += 1;
							m_pSkill[SKILL::FROZENORB]->iUseMp += 5;
						}
						else
						{
							SKILLINFO* pTemp = new SKILLINFO;
							pTemp->Skill = FrozenOrb;
							pTemp->pFrameKey = L"FrozenOrb";
							pTemp->iLevel = 1;
							pTemp->iUseMp = 40;
							m_vecpSkillInfo.emplace_back(pTemp);
							m_pSkill[SKILL::FROZENORB] = pTemp;
						}
					}
				}
				//텔레포트
				if (989 < fX && 1073 > fX && 85 < fY && 153 > fY && (!m_pSkill[SKILL::TELLEPORT] || 5 > m_pSkill[SKILL::TELLEPORT]->iLevel))
				{
					static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainSkill();
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
					CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
					if (m_pSkill[SKILL::TELLEPORT])
					{
						m_pSkill[SKILL::TELLEPORT]->iLevel += 1;
						m_pSkill[SKILL::TELLEPORT]->iUseMp -= 5;
					}
					else
					{
						SKILLINFO* pTemp = new SKILLINFO;
						pTemp->Skill = Teleport;
						pTemp->pFrameKey = L"Teleport";
						pTemp->iLevel = 1;
						pTemp->iUseMp = 50;
						m_vecpSkillInfo.emplace_back(pTemp);
						m_pSkill[SKILL::TELLEPORT] = pTemp;
					}
				}
				//차지드볼트
				if (m_pSkill[SKILL::TELLEPORT])
				{
					if (989 < fX && 1073 > fX && 277 < fY && 345 > fY)
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainSkill();
						CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
						CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
						if (m_pSkill[SKILL::CHARGEDBOLT])
						{
							m_pSkill[SKILL::CHARGEDBOLT]->iLevel += 1;
							m_pSkill[SKILL::CHARGEDBOLT]->iUseMp += 5;
						}
						else
						{
							SKILLINFO* pTemp = new SKILLINFO;
							pTemp->Skill = ChargedBolt;
							pTemp->pFrameKey = L"ChargedBolt";
							pTemp->iLevel = 1;
							pTemp->iUseMp = 15;
							m_vecpSkillInfo.emplace_back(pTemp);
							m_pSkill[SKILL::CHARGEDBOLT] = pTemp;
						}
					}
				}
				//멀티샷
				if (m_pSkill[SKILL::CHARGEDBOLT])
				{
					if (989 < fX && 1073 > fX && 470 < fY && 538 > fY)
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_RemainSkill();
						CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
						CSoundMgr::Get_Instance()->PlaySound(L"pselect.wav", CSoundMgr::UI);
						if (m_pSkill[SKILL::MULTISHOT])
						{
							m_pSkill[SKILL::MULTISHOT]->iLevel += 1;
							m_pSkill[SKILL::MULTISHOT]->iUseMp += 5;
						}
						else
						{
							SKILLINFO* pTemp = new SKILLINFO;
							pTemp->Skill = MultiShot;
							pTemp->pFrameKey = L"MultiShot";
							pTemp->iLevel = 1;
							pTemp->iUseMp = 20;
							m_vecpSkillInfo.emplace_back(pTemp);
							m_pSkill[SKILL::MULTISHOT] = pTemp;
						}
					}
				}
				if (1020 < fX && 1075 > fX && 610 < fY && 655 > fY)
					m_bOpen = false;
			}
		}
	}
}
