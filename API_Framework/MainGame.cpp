#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "Player.h"
#include "Monster.h"
#include "LineMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "SceneMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "UIMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame()
	:m_iFPS(0), m_dwTime(GetTickCount())
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	//맵
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/DieBack.bmp", L"DieBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Intro.bmp", L"Intro");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Harrogath.bmp", L"Harrogath");
	//이펙트
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/IceHit.bmp", L"IceHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/IceOrbExplode.bmp", L"IceOrbExplode");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/FreezeExplode.bmp", L"FreezeExplode");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/IceBlock.bmp", L"IceBlock");
	//플레어이
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Run.bmp", L"Run");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Idle.bmp", L"Idle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Attack.bmp", L"Attack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Attackwalk.bmp", L"Attackwalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/AttackIdle.bmp", L"AttackIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Casting.bmp", L"Casting");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/GetHit.bmp", L"GetHit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/PlayerDie.bmp", L"PlayerDie");
	//몬스터
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/SkeletonIdle.bmp"), L"SkeletonIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/BSkeletonIdle.bmp"), L"BSkeletonIdle");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/SkeletonWalk.bmp"), L"SkeletonWalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/BSkeletonWalk.bmp"), L"BSkeletonWalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/SkeletonAttack.bmp"), L"SkeletonAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/BSkeletonAttack.bmp"), L"BSkeletonAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/SkeletonDie.bmp"), L"SkeletonDie");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/BDiaBeam.bmp"), L"BDiaBeam");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/BDiaFire.bmp"), L"BDiaFire");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/BDiaNatural.bmp"), L"BDiaNatural");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/BDiaRun.bmp"), L"BDiaRun");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/DiaBeam.bmp"), L"DiaBeam");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/DiaFire.bmp"), L"DiaFire");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/DiaNatural.bmp"), L"DiaNatural");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/DiaRun.bmp"), L"DiaRun");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/DiaWalk.bmp"), L"DiaWalk");
	CBmpMgr::Get_Instance()->Insert_Bmp(__T("../Image/Monster/DiaDie.bmp"), L"DiaDie");
	//NPC
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/Seller.bmp", L"Seller");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/CreatePortal.bmp", L"CreatePortal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/ProgressPortal.bmp", L"ProgressPortal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/Cain.bmp", L"Cain");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/Quest.bmp", L"Quest");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/SealLeft.bmp", L"SealLeft");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/SealMid.bmp", L"SealMid");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Npc/SealRight.bmp", L"SealRight");
	//UI
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/StatusBar.bmp", L"UI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Walk.bmp", L"Walk");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/HPBall.bmp", L"HPBall");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MPBall.bmp", L"MPBall");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/CharicInfo.bmp", L"CharicInfo");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ButtonUp.bmp", L"ButtonUp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ButtonDown.bmp", L"ButtonDown");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/StaminaBar.bmp", L"StaminaBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inven.bmp", L"Inven");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/BeltSlot.bmp", L"BeltSlot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Mouse.bmp", L"Mouse");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Shop.bmp", L"Shop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/SkillTree.bmp", L"SkillTree");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/ExpBar.bmp", L"ExpBar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/MonsterBar.bmp", L"MonsterBar");
	//미니맵
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Minimap.bmp", L"Minimap");
	//타일
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Base.bmp", L"Base");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Target.bmp", L"Target");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile.bmp", L"Tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Lava.bmp", L"Lava");
	//스킬아이콘
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/Blizzard.bmp", L"Blizzard");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/ChargedBolt.bmp", L"ChargedBolt");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/FrostNova.bmp", L"FrostNova");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/FrozenOrb.bmp", L"FrozenOrb");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/GlacialSpike.bmp", L"GlacialSpike");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/IceBlast.bmp", L"IceBlast");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/IceBolt.bmp", L"IceBolt");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/MultiShot.bmp", L"MultiShot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/NomalAttack.bmp", L"NomalAttack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill/Teleport.bmp", L"Teleport");
	//스킬창스킬아이콘
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill2/Blizzard.bmp", L"BlizzardA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill2/ChargedBolt.bmp", L"ChargedBoltA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill2/FrostNova.bmp", L"FrostNovaA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill2/FrozenOrb.bmp", L"FrozenOrbA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill2/GlacialSpike.bmp", L"GlacialSpikeA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill2/IceBlast.bmp", L"IceBlastA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill2/IceBolt.bmp", L"IceBoltA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill2/MultiShot.bmp", L"MultiShotA");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Skill2/Teleport.bmp", L"TeleportA");
	//스킬
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SkillShot/ChargedBolt.bmp", L"ChargedBoltS");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SkillShot/IceBolt.bmp", L"IceBoltS");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SkillShot/IceBlast.bmp", L"IceBlastS");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SkillShot/FrostNova.bmp", L"FrostNovaS");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SkillShot/FrostOrb.bmp", L"FrostOrbS");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SkillShot/IceStorm.bmp", L"IceStorm");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SkillShot/DiaLightning.bmp", L"DiaLightning");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/SkillShot/Fire.bmp", L"Fire");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Arrow.bmp", L"Arrow");
	//아이템
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Staff.bmp", L"Staff");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Armor.bmp", L"Armor");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Boots1.bmp", L"Boots1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Boots2.bmp", L"Boots2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Gloves1.bmp", L"Gloves1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Gloves2.bmp", L"Gloves2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Helm.bmp", L"Helm");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Necklace.bmp", L"Necklace");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Ring1.bmp", L"Ring1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Ring2.bmp", L"Ring2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Sash.bmp", L"Sash");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/HpPotion.bmp", L"HpPotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/MpPotion.bmp", L"MpPotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/HMpPotion.bmp", L"HMpPotion");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/PotionDrop.bmp", L"PotionDrop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/WDrop.bmp", L"WDrop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/ArmorDrop.bmp", L"ArmorDrop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/HelmDrop.bmp", L"HelmDrop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/RingDrop.bmp", L"RingDrop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/GoldDrop.bmp", L"GoldDrop");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/bBack.bmp", L"bBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/rBack.bmp", L"rBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/gBack.bmp", L"gBack");
	m_DC = GetDC(g_hWnd);

	CSoundMgr::Get_Instance()->Initialize();

	srand((unsigned)time(NULL));
	//시작스테이지
	CSceneMgr::Get_Instance()->SetScene(SCENE::SCENE_TITLE);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Image(L"Back");

	CSceneMgr::Get_Instance()->Render(hBackBuffer);
	
	BitBlt(m_DC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);

	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount())
	{
		wsprintf(m_szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount();
	}
}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_DC);
	CTileMgr::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CUIMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
}
