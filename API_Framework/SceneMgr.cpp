#include "stdafx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "TileEdit.h"
#include "Stage_1.h"
#include "Stage_2.h"
#include "Stage_3.h"
#include "Title.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;
CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
{
}


CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize()
{
}

void CSceneMgr::Update()
{
	if(m_pScene->Get_Scen() != SCENE::END)
		SetScene(m_pScene->Get_Scen());
	if (m_pScene)
		m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	if (m_pScene)
		m_pScene->Late_Update();
}

void CSceneMgr::Render(HDC _DC)
{
	if (m_pScene)
		m_pScene->Render(_DC);
}

void CSceneMgr::Release()
{
	if (m_pScene)
		Safe_Delete(m_pScene);
}

//Scene 을 설정한다
void CSceneMgr::SetScene(SCENE::SCENE _eScene)
{
	switch (_eScene)
	{
	case SCENE::SCENE_TITLE:
		SAFE_DELETE(m_pScene);
		m_pScene = new CTitle;
		break;
	case SCENE::SCENE_1:
		SAFE_DELETE(m_pScene);
		m_pScene = new CStage_1;
		break;
	case SCENE::SCENE_2:
		SAFE_DELETE(m_pScene);
		m_pScene = new CStage_2;
		break;
	case SCENE::SCENE_3:
		SAFE_DELETE(m_pScene);
		m_pScene = new CStage_3;
		break;
	case SCENE::MAP_EDITOR:
		SAFE_DELETE(m_pScene);
		m_pScene = new CTileEdit;
		break;
	}

	m_pScene->Initialize();
}
