#include "stdafx.h"
#include "MyEdit.h"
#include "KeyMgr.h"
#include "Line.h"
#include "ScrollMgr.h"

CMyEdit* CMyEdit::m_pInstance = nullptr;
CMyEdit::CMyEdit()
	: m_bCheck(true)
{
	ZeroMemory(m_tLinePos, sizeof(m_tLinePos));
}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
}

void CMyEdit::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_Scroll_X(5.f);
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_Scroll_X(-5.f);

	Key_Check();
}

void CMyEdit::Late_Update()
{
}

void CMyEdit::Render(HDC _DC)
{
	for (auto& pLine : m_listLIne)
		pLine->Render(_DC);
}

void CMyEdit::Release()
{
	for_each(m_listLIne.begin(), m_listLIne.end(), Safe_Delete<CLine*>);
	m_listLIne.clear();
}

void CMyEdit::Key_Check()
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (LONG)CScrollMgr::Get_Instance()->Get_Scroll_X();

	if (CKeyMgr::Get_Instance()->Key_Down('A'))
		Save_Line();
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
		Load_Line();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (m_bCheck)
		{
			m_tLinePos[0].fX = (float)pt.x;
			m_tLinePos[0].fY = (float)pt.y;
			m_bCheck = false;
		}
		else
		{
			m_tLinePos[1].fX = (float)pt.x;
			m_tLinePos[1].fY = (float)pt.y;

			m_listLIne.emplace_back(new CLine(m_tLinePos[0], m_tLinePos[1]));

			//m_bCheck = true;
			m_tLinePos[0].fX = m_tLinePos[1].fX;
			m_tLinePos[0].fY = m_tLinePos[1].fY;
		}
	}
}

void CMyEdit::Save_Line()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_WRITE
	, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, __T("Save Fail"), L"FAIL", MB_OK);
		return;
	}

	DWORD	dwByte = 0;
	for (auto& pLine : m_listLIne)
	{
		WriteFile(hFile, &pLine->Get_Info(), sizeof(LINEINFO), &dwByte, NULL);
	}
	CloseHandle(hFile);
	MessageBox(g_hWnd, __T("Save Success"), L"SUCCESS", MB_OK);
}

void CMyEdit::Load_Line()
{
	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, __T("Load Fail"), L"FAIL", MB_OK);
		return;
	}

	Release();

	DWORD	dwByte = 0;

	LINEINFO tInfo = {};
	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(LINEINFO), &dwByte, NULL);

		if (0 == dwByte)
			break;

		m_listLIne.emplace_back(new CLine(tInfo.tLeftPos, tInfo.tRightPos));
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, __T("Load Success"), L"SUCCESS", MB_OK);
}
