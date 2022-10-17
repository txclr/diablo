#include "stdafx.h"
#include "TileMgr.h"
#include "Tile.h"
#include "Lava.h"
#include "AllTile.h"
#include "Player.h"
#include "ScrollMgr.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;
CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX * TILEY);
}


CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	CObj* pObj;
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = float((TILECX >> 1)*j);
			float fY = float((TILECY * i) + (j%2)*(TILECY>>1));

			pObj = CAbstractFactory<CTile>::Create(fX, fY, true);
			m_vecTile.emplace_back(pObj);
		}
	}
}

void CTileMgr::Update()
{
	for (auto& i: m_vecTile)
	{
		i->Update();
	}
}

void CTileMgr::Late_Update()
{
}

void CTileMgr::Render(HDC _DC)
{
	Rectangle(_DC, 0, 0, 2000, 2000);
	float fSX = -CScrollMgr::Get_Instance()->Get_Scroll_X();
	if (0 > fSX)
		fSX = 0;
	int iCullX = (int)fSX / (TILECX >> 1);
	int iCullEndX = iCullX + (WINCX / (TILECX>>1)) + 3;
	float fSY = -CScrollMgr::Get_Instance()->Get_Scroll_Y();
	if (0 > fSY)
		fSY = 0;
	int iCullY = (int)fSY / (TILECY);
	int iCullEndY = iCullY + (WINCY / TILECY ) + 2;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int iIdx = i * TILEX + j;

			if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
				continue;

			m_vecTile[iIdx]->Render(_DC);
			if (m_vecTile[iIdx]->Get_Effect() && CCollisionMgr::Check_Tile(CObjMgr::Get_Instance()->Get_Player(), m_vecTile[iIdx]))
			{
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_ReSet();
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(STATE::IDLE);
			}
		}
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}

void CTileMgr::Picking_Tile(int& _iIter, int _iDrawID, int _iOption, bool _bAniCheck)
{
	static_cast<CTile*>(m_vecTile[_iIter])->Set_DrawID(_iDrawID);
	static_cast<CTile*>(m_vecTile[_iIter])->Set_Option(_iOption);
	static_cast<CTile*>(m_vecTile[_iIter])->Set_AniCheck(_bAniCheck);
}

void CTileMgr::Save_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, NULL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장 실패", L"실패", MB_OK);
		return;
	}

	int iDrawID = 0;
	int iOption = 0;
	bool bAniCheck = false;
	DWORD dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		bAniCheck = dynamic_cast<CTile*>(pTile)->Get_AniCheck();
		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();

		WriteFile(hFile, &bAniCheck, sizeof(bool), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"저장 성공", L"성공", MB_OK);
}

void CTileMgr::Load_Tile(SCENE::SCENE _eScene)
{
	HANDLE hFile = {};
	switch (_eScene)
	{
	case SCENE::SCENE_1:
		hFile = CreateFile(L"../Data/TTile.dat", GENERIC_READ
			, NULL, NULL, OPEN_EXISTING, NULL, NULL);
		break;
	case SCENE::SCENE_2:
		hFile = CreateFile(L"../Data/DTile.dat", GENERIC_READ
			, NULL, NULL, OPEN_EXISTING, NULL, NULL);
		break;
	case SCENE::SCENE_3:
		hFile = CreateFile(L"../Data/DiaTile.dat", GENERIC_READ
			, NULL, NULL, OPEN_EXISTING, NULL, NULL);
		break;
	}

	if (INVALID_HANDLE_VALUE == hFile)
	{
		//MessageBox(g_hWnd, L"불러오기 실패", L"실패", MB_OK);
		return;
	}

	Release();

	INFO tTemp = {};
	int iDrawID = 0, iOption = 0;
	bool bAniCheck = false;
	DWORD dwByte = 0;
	CObj* pObj;
	while (true)
	{
		ReadFile(hFile, &bAniCheck, sizeof(bool), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);
		if (0 == dwByte)
			break;
		//pObj = CAbstractFactory<CTile>::Create(tTemp.fX, tTemp.fY, true);
		if (bAniCheck)
		{
			pObj = CAbstractFactory<CLava>::Create(tTemp.fX, tTemp.fY, true);
			dynamic_cast<CLava*>(pObj)->Set_DrawID(iDrawID);
			dynamic_cast<CLava*>(pObj)->Set_Option(iOption);
		}
		else
		{
			pObj = CAbstractFactory<CAllTile>::Create(tTemp.fX, tTemp.fY, true);
			dynamic_cast<CAllTile*>(pObj)->Set_DrawID(iDrawID);
			dynamic_cast<CAllTile*>(pObj)->Set_Option(iOption);
		}
		//dynamic_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		//dynamic_cast<CTile*>(pObj)->Set_Option(iOption);
	
		m_vecTile.emplace_back(pObj);
	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"불러오기 성공", L"성공", MB_OK);
}
