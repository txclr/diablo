#include "stdafx.h"
#include "MyEvent.h"
#include "ObjMgr.h"
#include "MathMgr.h"
#include "Cain.h"
#include "Potal.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "Stage_1.h"
#include "Stage_2.h"

CMyEvent::CMyEvent()
{
}


CMyEvent::~CMyEvent()
{
}

void CMyEvent::Initialize()
{
	m_pPlayer = CObjMgr::Get_Instance()->Get_Player();
	m_bOpen = true;
	m_bPotal = true;
	m_iTime = 0;
	m_iSeal = 0;
}

void CMyEvent::Update()
{
	if (2 < m_iSeal)
	{
		m_iSeal = 0;
		CObj* pObj = CAbstractFactory<CPotal>::Create(1860, 1100, true);
		CObjMgr::Get_Instance()->Add_Object(OBJID::POTAL, pObj);
	}

	m_iTime += 1;
}

void CMyEvent::Render(HDC _DC)
{
	if (m_pPlayer->Get_Dead())
	{
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"DieBack");
		GdiTransparentBlt(_DC
			, 0, 0
			, WINCX, WINCY
			, hMemDC
			, 0, 0
			, WINCX, WINCY
			, RGB(170, 170, 170));
	}
}

void CMyEvent::Release()
{
}

void CMyEvent::Function()
{
}

void CMyEvent::Event()
{
	if (CObjMgr::Get_Instance()->Get_Obj(OBJID::POTAL).empty())
		return;
	else
	{
		if (50 > MathMgr::Get_Distance(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_Obj(OBJID::POTAL).front()))
		{
			if (m_bPotal)
			{
				CSceneMgr::Get_Instance()->Get_Scene()->Set_Scene(SCENE::SCENE_2);
				m_bPotal = false;
			}
			else
				CSceneMgr::Get_Instance()->Get_Scene()->Set_Scene(SCENE::SCENE_3);
		}
	}

}
