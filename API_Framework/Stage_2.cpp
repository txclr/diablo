#include "stdafx.h"
#include "Stage_2.h"
#include "Player.h"
#include "Monster.h"
#include "Seller.h"
#include "Potal.h"
#include "Seal.h"
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

CStage_2::CStage_2()
{
}


CStage_2::~CStage_2()
{
	Release();
}

void CStage_2::Initialize()
{
	CTileMgr::Get_Instance()->Load_Tile(SCENE::SCENE_2);
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"bDiabloLair.wav");

	CObjMgr::Get_Instance()->Set_Target(nullptr);

	CObjMgr::Get_Instance()->Get_Player()->Set_Pos(2324.f, 1915.f);

	CObj* pObj = CAbstractFactory<CPotal>::Create(2324.f, 1915.f, true);
	pObj->Set_Effect(true);
	CObjMgr::Get_Instance()->Add_Object(OBJID::POTAL, pObj);

	pObj = CAbstractFactory<CSeal>::Create(800, 1300, true);
	CObjMgr::Get_Instance()->Add_Object(OBJID::SEAL, pObj);

	pObj = CAbstractFactory<CSeal>::Create(2050, 700, true);
	CObjMgr::Get_Instance()->Add_Object(OBJID::SEAL, pObj);

	pObj = CAbstractFactory<CSeal>::Create(900, 550, true);
	CObjMgr::Get_Instance()->Add_Object(OBJID::SEAL, pObj);

	pObj = CAbstractFactory<CMonster>::Create(1200, 1300);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(1200, 1500);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(1319, 1200);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(1600, 1000);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(1600, 1200);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(1060, 450);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(890, 520);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(725, 592);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(2100, 650);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(2260, 736);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);

	pObj = CAbstractFactory<CMonster>::Create(2400, 860);
	CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, pObj);
}

void CStage_2::Update()
{
	if (CObjMgr::Get_Instance()->Get_Player()->Get_Dead() && CKeyMgr::Get_Instance()->Key_Down(VK_ESCAPE))
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Resulrect();
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_State(STATE::IDLE);
		CObjMgr::Get_Instance()->Get_Player()->Set_Pos(2324.f, 1915.f);
	}
	CUIMgr::Get_Instance()->Update();
	CObjMgr::Get_Instance()->Update();
	m_iTime += 1;
}

void CStage_2::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CKeyMgr::Get_Instance()->Key_Update();
}

void CStage_2::Render(HDC _DC)
{
	CTileMgr::Get_Instance()->Render(_DC);
	CObjMgr::Get_Instance()->Render(_DC);
	CUIMgr::Get_Instance()->Render(_DC);
}

void CStage_2::Release()
{
	CObjMgr::Get_Instance()->ReleaseNP();
}
