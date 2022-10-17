#include "stdafx.h"
#include "LineMgr.h"
#include "Line.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;
CLineMgr::CLineMgr()
{
}


CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	Load_Line();
}

void CLineMgr::Render(HDC _DC)
{
	for (auto& pLine : m_listLine)
		pLine->Render(_DC);
}

void CLineMgr::Release()
{
	for_each(m_listLine.begin(), m_listLine.end(), Safe_Delete<CLine*>);
	m_listLine.clear();
}

bool CLineMgr::Collision_Line(float& _x, float& _y, int _iCY)
{
	if (m_listLine.empty())
		return false;

	//선생님처럼 타겟을 정해서 하면 2,3층이 안돼서 모든 라인에 대한걸로 바꿈
	for (auto& pLine : m_listLine)
	{
		if (pLine->Get_Info().tLeftPos.fX <= _x
			&& pLine->Get_Info().tRightPos.fX >= _x)
		{
			float	x1 = pLine->Get_Info().tLeftPos.fX;
			float	y1 = pLine->Get_Info().tLeftPos.fY;
			float	x2 = pLine->Get_Info().tRightPos.fX;
			float	y2 = pLine->Get_Info().tRightPos.fY;
			float	fY = 0.f;

			fY = ((y2 - y1) / (x2 - x1)) * (_x - x1) + y1;

			if (fY < (_y + _iCY / 2)
				&& (fY + 15) >(_y + _iCY / 2))
			{
				_y = fY - _iCY / 2;
				return true;
			}
		}
	}
		return false;

}

void CLineMgr::Load_Line()
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

		m_listLine.emplace_back(new CLine(tInfo.tLeftPos, tInfo.tRightPos));
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, __T("Load Success"), L"SUCCESS", MB_OK);
}
