#include "stdafx.h"
#include "TileEdit.h"
#include "Mouse.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "ObjMgr.h"
#include "UIMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CTileEdit::CTileEdit()
	:m_iIter(0), m_iDrawID(0), m_iOption(0)
{
}


CTileEdit::~CTileEdit()
{
	Release();
}

void CTileEdit::Initialize()
{
	m_tMouse = {};
	CTileMgr::Get_Instance()->Initialize();
	CSoundMgr::Get_Instance()->StopAll();
	//CUIMgr::Get_Instance()->Add_Object(UIID::MOUSE);
	m_pFrameKey = L"Lava";
	m_bAniCheck = true;
}

void CTileEdit::Update()
{
	Key_Check();
	CTileMgr::Get_Instance()->Update();
	//CObjMgr::Get_Instance()->Update();
	CUIMgr::Get_Instance()->Update();
	CCollisionMgr::Collision_Tile(CUIMgr::Get_Instance()->Get_Mouse(), CTileMgr::Get_Instance()->Get_TileList(), m_iIter);

	if(CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
		m_eStage = SCENE::SCENE_TITLE;
}

void CTileEdit::Late_Update()
{
	CKeyMgr::Get_Instance()->Key_Update();
}

void CTileEdit::Render(HDC _DC)
{
	CTileMgr::Get_Instance()->Render(_DC);
	//CObjMgr::Get_Instance()->Render(_DC);
	CUIMgr::Get_Instance()->Render(_DC);

	GetCursorPos(&m_tMouse);
	ScreenToClient(g_hWnd, &m_tMouse);

	m_tMouse.x -= LONG(CScrollMgr::Get_Instance()->Get_Scroll_X());
	m_tMouse.y -= LONG(CScrollMgr::Get_Instance()->Get_Scroll_Y());

	TCHAR	szBuff[32] = L"";
	wsprintf(szBuff, L"MX: %d", int(m_tMouse.x));
	TextOut(_DC, 1200, 0, szBuff, lstrlen(szBuff));

	wsprintf(szBuff, L"MY: %d", int(m_tMouse.y));
	TextOut(_DC, 1300, 0, szBuff, lstrlen(szBuff));

	wsprintf(szBuff, L"Iter: %d", int(m_iIter));
	TextOut(_DC, 0, 0, szBuff, lstrlen(szBuff));
}

void CTileEdit::Release()
{
	//CTileMgr::Get_Instance()->Release();
	//CUIMgr::Get_Instance()->Release();
	//CTileMgr::Destroy_Instance();
	//CKeyMgr::Destroy_Instance();
	//CScrollMgr::Destroy_Instance();
	//CBmpMgr::Destroy_Instance();
	//CObjMgr::Destroy_Instance();
	CUIMgr::Destroy_Instance();
}

void CTileEdit::Key_Check()
{
	//시드 내에서 이미지 변경
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
		m_iDrawID = 0;
	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
		m_iDrawID = 1;
	else if (CKeyMgr::Get_Instance()->Key_Down('3'))
		m_iDrawID = 2;
	else if (CKeyMgr::Get_Instance()->Key_Down('4'))
		m_iDrawID = 3;
	else if (CKeyMgr::Get_Instance()->Key_Down('5'))
		m_iDrawID = 4;
	else if (CKeyMgr::Get_Instance()->Key_Down('6'))
		m_iDrawID = 5;
	else if (CKeyMgr::Get_Instance()->Key_Down('7'))
		m_iDrawID = 6;
	else if (CKeyMgr::Get_Instance()->Key_Down('8'))
		m_iDrawID = 7;
	else if (CKeyMgr::Get_Instance()->Key_Down('9'))
		m_iDrawID = 8;
	else if (CKeyMgr::Get_Instance()->Key_Down('0'))
		m_iDrawID = 9;
	//맵 시드 변경
	else if (CKeyMgr::Get_Instance()->Key_Down('Q'))
		m_iOption = 0;
	else if (CKeyMgr::Get_Instance()->Key_Down('W'))
		m_iOption = 1;
	else if (CKeyMgr::Get_Instance()->Key_Down('E'))
		m_iOption = 2;
	else if (CKeyMgr::Get_Instance()->Key_Down('R'))
		m_iOption = 3;
	else if (CKeyMgr::Get_Instance()->Key_Down('T'))
		m_iOption = 4;
	else if (CKeyMgr::Get_Instance()->Key_Down('Y'))
		m_iOption = 5;
	else if (CKeyMgr::Get_Instance()->Key_Down('U'))
		m_iOption = 6;
	else if (CKeyMgr::Get_Instance()->Key_Down('I'))
		m_iOption = 7;
	else if (CKeyMgr::Get_Instance()->Key_Down('O'))
		m_iOption = 8;
	else if (CKeyMgr::Get_Instance()->Key_Down('P'))
		m_iOption = 9;
	else if (CKeyMgr::Get_Instance()->Key_Down('A'))
		m_iOption = 10;
	else if (CKeyMgr::Get_Instance()->Key_Down('S'))
		m_iOption = 11;
	else if (CKeyMgr::Get_Instance()->Key_Down('D'))
		m_iOption = 12;
	else if (CKeyMgr::Get_Instance()->Key_Down('F'))
		m_iOption = 13;
	else if (CKeyMgr::Get_Instance()->Key_Down('G'))
		m_iOption = 14;
	else if (CKeyMgr::Get_Instance()->Key_Down('H'))
		m_iOption = 15;
	else if (CKeyMgr::Get_Instance()->Key_Down('J'))
		m_iOption = 16;
	else if (CKeyMgr::Get_Instance()->Key_Down('K'))
		m_iOption = 17;
	//용암선택
	else if (CKeyMgr::Get_Instance()->Key_Down('Z'))
		m_bAniCheck = true;
	else if (CKeyMgr::Get_Instance()->Key_Down('X'))
		m_bAniCheck = false;

	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		CTileMgr::Get_Instance()->Picking_Tile(m_iIter, m_iDrawID, m_iOption, m_bAniCheck );

	float fX = m_tMouse.x + CScrollMgr::Get_Instance()->Get_Scroll_X();
	float fY = m_tMouse.y + CScrollMgr::Get_Instance()->Get_Scroll_Y();

	if (20 > fX)
		CScrollMgr::Get_Instance()->Set_Scroll_XP(10);
	else if (1380 < fX)
		CScrollMgr::Get_Instance()->Set_Scroll_XP(-10);
	if (20 > fY)
		CScrollMgr::Get_Instance()->Set_Scroll_YP(10);
	else if (780 < fY)
		CScrollMgr::Get_Instance()->Set_Scroll_YP(-10);

	//CScrollMgr::Get_Instance()->Set_Boundary();

	if (CKeyMgr::Get_Instance()->Key_Down(VK_F1))
		CTileMgr::Get_Instance()->Save_Tile();
	//if (CKeyMgr::Get_Instance()->Key_Down(VK_F2))
	//	CTileMgr::Get_Instance()->Load_Tile();
}