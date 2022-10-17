#include "stdafx.h"
#include "UIMgr.h"
#include "Status.h"
#include "HpBall.h"
#include "MpBall.h"
#include "Mouse.h"
#include "Skill.h"
#include "Inven.h"
#include "MyEvent.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;
CUIMgr::CUIMgr()
{
}


CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Add_Object(UIID::ID _eID)
{
	CUI* pUI;
	switch (_eID)
	{
	case UIID::STATUS:
		pUI = new CStatus;
		pUI->Initialize();
		m_vecUI[UIID::STATUS].emplace_back(pUI);
		break;
	case UIID::HPBALL:
		pUI = new CHpBall;
		pUI->Initialize();
		m_vecUI[UIID::STATUS].emplace_back(pUI);
		break;
	case UIID::MPBALL:
		pUI = new CMpBall;
		pUI->Initialize();
		m_vecUI[UIID::STATUS].emplace_back(pUI);
		break;
	case UIID::MOUSE:
		pUI = new CMouse;
		pUI->Initialize();
		m_vecUI[UIID::MOUSE].emplace_back(pUI);
		break;
	default:
		break;
	}
}

void CUIMgr::Initialize()
{
	CUI* pUI = new CStatus;
	pUI->Initialize();
	m_vecUI[UIID::STATUS].emplace_back(pUI);

	pUI = new CHpBall;
	pUI->Initialize();
	m_vecUI[UIID::HPBALL].emplace_back(pUI);

	pUI = new CMpBall;
	pUI->Initialize();
	m_vecUI[UIID::MPBALL].emplace_back(pUI);

	//pUI = new CMouse;
	//pUI->Initialize();
	//m_vecUI[UIID::MOUSE].emplace_back(pUI);

	pUI = new CSkill;
	pUI->Initialize();
	m_vecUI[UIID::SKILL].emplace_back(pUI);

	pUI = new CInven;
	pUI->Initialize();
	m_vecUI[UIID::INVEN].emplace_back(pUI);

	pUI = new CMyEvent;
	pUI->Initialize();
	m_vecUI[UIID::EVENT].emplace_back(pUI);
}

void CUIMgr::Update()
{
	for (int i = 0; i < UIID::END; ++i)
	{
		for (auto& pObj : m_vecUI[i])
			pObj->Update();
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		CCollisionMgr::Collision_UI(m_vecUI[UIID::MOUSE], m_vecUI[UIID::SKILL]);
	}

	if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
	{
		CCollisionMgr::Collision_UI1(m_vecUI[UIID::MOUSE], m_vecUI[UIID::SKILL]);
	}
}

void CUIMgr::Render(HDC _DC)
{
	for (int i = 0; i < UIID::END; ++i)
	{
		for (auto& pObj : m_vecUI[i])
			pObj->Render(_DC);
	}
}

void CUIMgr::Release()
{
	for (int i = 0; i < UIID::END; ++i)
	{
		for_each(m_vecUI[i].begin(), m_vecUI[i].end(), Safe_Delete<CUI*>);
		m_vecUI[i].clear();
	}
}
