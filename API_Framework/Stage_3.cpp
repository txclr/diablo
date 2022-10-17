#include "stdafx.h"
#include "Stage_3.h"
#include "Player.h"
#include "Monster.h"
#include "Seller.h"
#include "Potal.h"
#include "Diabllo.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "TileMgr.h"
#include "Potal.h"
#include "UIMgr.h"
#include "SoundMgr.h"

CStage_3::CStage_3()
{
}


CStage_3::~CStage_3()
{
	Release();
}

void CStage_3::Initialize()
{
	CTileMgr::Get_Instance()->Load_Tile(SCENE::SCENE_3);
	CObjMgr::Get_Instance()->Set_Target(nullptr);

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1360, 1520);

	CObj* pObj = CAbstractFactory<CDiabllo>::Create(1600,800);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CPotal>::Create(1360, 1520, true);
	pObj->Set_Effect(true);
	CObjMgr::Get_Instance()->Add_Object(OBJID::POTAL, pObj);
}

void CStage_3::Update()
{
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Dead() && CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Resulrect();
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(STATE::IDLE);
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(1360, 1520);
	}
	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
}

void CStage_3::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Key_Update();
}

void CStage_3::Render(HDC _DC)
{
	CTileMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
	CUIMgr::Get_Instance()->Render(_DC);
}

void CStage_3::Release()
{
}
