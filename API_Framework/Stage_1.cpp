#include "stdafx.h"
#include "Stage_1.h"
#include "Player.h"
#include "Monster1.h"
#include "Seller.h"
#include "Cain.h"
#include "Potal.h"
#include "Seal.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"
#include "Diabllo.h"



CStage_1::CStage_1()
	:m_iTime(0) 
{
}


CStage_1::~CStage_1() 
{
	Release();
}

void CStage_1::Initialize() 
{
	CTileMgr::Get_Instance()->Load_Tile(SCENE::SCENE_1);
	//CTileMgr::Get_Instance()->Initialize();

	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"btown1.wav");
	CObj* pObj;

	if (CObjMgr::Get_Instance()->Get_Obj(OBJID::PLAYER).empty())
	{
		CObj* pObj = CAbstractFactory<CPlayer>::Create();
		CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, pObj);
	}

	//pObj = CAbstractFactory<CDiabllo>::Create(2100,1100);
	//CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster1>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster1>::Create(2300, 1100);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CSeller>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJID::NPC, pObj);

	pObj = CAbstractFactory<CCain>::Create();
	CObjMgr::Get_Instance()->Add_Object(OBJID::CAIN, pObj);

	CUIMgr::Get_Instance()->Initialize();
}

void CStage_1::Update() 
{
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Dead() && CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Resulrect();
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(STATE::IDLE);
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1150,1100);
	}

	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	//CTileMgr::Get_Instance()->Update();
	
	m_iTime += 1;
}
void CStage_1::Late_Update() 
{
	CObjMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Key_Update();
}

void CStage_1::Render(HDC _DC) 
{
	CTileMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
	CUIMgr::Get_Instance()->Render(_DC);
}

void CStage_1::Release() 
{
	CObjMgr::Get_Instance()->ReleaseNP();
}