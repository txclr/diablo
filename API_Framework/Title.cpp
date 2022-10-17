#include "stdafx.h"
#include "Title.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"

CTitle::CTitle()
	:m_fTime(0)
{
}


CTitle::~CTitle()
{
	Release();
}

void CTitle::Initialize()
{
	CSoundMgr::Get_Instance()->PlayBGM(L"Intro.wav");
	CUIMgr::Get_Instance()->Add_Object(UIID::MOUSE);
}

void CTitle::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SPACE))
		m_eStage = SCENE::SCENE_1;
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN))
		m_eStage = SCENE::MAP_EDITOR;
	CUIMgr::Get_Instance()->Update();
	m_fTime += 1;
}

void CTitle::Late_Update()
{
}

void CTitle::Render(HDC _DC)
{
	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Image(L"Intro");

	BitBlt(_DC, 0, 0, WINCX, WINCY, hBackBuffer, WINCX*(int(m_fTime*0.2)%10), 0, SRCCOPY);
	CUIMgr::Get_Instance()->Render(_DC);
}

void CTitle::Release()
{
}
