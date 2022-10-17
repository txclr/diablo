#include "stdafx.h"
#include "Inven.h"
#include "Player.h"
#include "Item.h"
#include "HpPotion.h"
#include "MpPotion.h"
#include "Armor.h"
#include "Staff.h"
#include "Boots.h"
#include "GoodBoots.h"
#include "Gloves.h"
#include "GoodGloves.h"
#include "Helm.h"
#include "Necklace.h"
#include "Ring.h"
#include "TheRing.h"
#include "Sash.h"
#include "KeyMgr.h"
#include "BmpMgr.h"
#include "UIMgr.h"
#include "ObjMgr.h"
#include "CollisionMgr.h"
#include "MathMgr.h"
#include "SoundMgr.h"

CInven::CInven()
	:m_pHandleItem(nullptr), m_pPickItem(nullptr), m_pLookItem(nullptr), m_bSash(false), m_bSashUp(false), m_bShop(false)
{
	memset(m_pEquip, 0, sizeof(m_pEquip));
}


CInven::~CInven()
{
	Release();
}

void CInven::Initialize()
{
	m_bOpen = false;

	//실험용
	CItem* pItem = new CArmor(155, 160, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CStaff(260, 160, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CGoodGloves(365, 160, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CGloves(365, 240, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CBoots(467, 160, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CGoodBoots(467, 240, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CHelm(570, 160, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CSash(570, 240, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CTheRing(570, 280, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CRing(620, 280, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CNecklace(520, 513, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CHpPotion(573, 513, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());

	pItem = new CMpPotion(626, 513, ITEMSTATE::SHOP);
	pItem->Initialize();
	m_listItem.emplace_back(pItem);
	pItem->Set_Iter(--m_listItem.end());
}

void CInven::Update()
{
	float fX = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fX;
	float fY = CUIMgr::Get_Instance()->Get_Mouse().front()->Get_Info().fY;
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		m_bOpen = false;
		if (m_bShop)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
			CSoundMgr::Get_Instance()->PlaySound(L"Ghe_farewell.wav", CSoundMgr::UI);
			m_bShop = false;
		}
	}
	if (CKeyMgr::Get_Instance()->Key_Down('I'))
		m_bOpen = !m_bOpen;
	if (m_bShop)
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
	}
	else if (m_pHandleItem)
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
	//템창 열었을때
	if (m_bOpen)
	{
		//템창에서 하는일
		if (WINCX >> 1 < fX)
		{
			if (m_pHandleItem)
			{
				for (auto& pItem : m_listItem)
				{
					if (ITEMSTATE::FIELD == pItem->Get_State())
						continue;
					if (CCollisionMgr::Check_ItemRect(m_pHandleItem, pItem)) // 필드템 충돌하면 안됨
					{
						m_iCollNum += 1;
						m_pColItem = pItem;
					}
				}
				//핸들 프레임키값
				switch (m_iCollNum)
				{
				case 0:
					m_pHandleItem->Set_BackFrame(L"bBack");
					break;
				case 1:
					m_pHandleItem->Set_BackFrame(L"gBack");
					break;
				default:
					m_pHandleItem->Set_BackFrame(L"rBack");
					break;
				}
				if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
				{
					if (415 > fY)
					{
						ITEMTYPE::TYPE eType = m_pHandleItem->Get_ItemType();
						//무기
						if (eType == ITEMTYPE::WEAPON &&
							730 < fX && 838 > fX && 135 < fY && 292 > fY)
						{
							if (m_pEquip[ITEMSLOT::WEAPON])
							{
								CItem* pTemp = m_pHandleItem;
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pEquip[ITEMSLOT::WEAPON]->Set_ItemState(ITEMSTATE::HAND);
								m_pHandleItem->Set_Pos(784.f, 213.f);
								m_pHandleItem = m_pEquip[ITEMSLOT::WEAPON];
								m_pEquip[ITEMSLOT::WEAPON] = pTemp;
							}
							else
							{
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pHandleItem->Set_Pos(784.f, 213.f);
								m_pEquip[ITEMSLOT::WEAPON] = m_pHandleItem;
								m_pHandleItem = nullptr;
							}
						}
						//아머
						else if (eType == ITEMTYPE::ARMOR &&
							936 < fX && 1044 > fX && 172 < fY && 292 > fY)
						{
							if (m_pEquip[ITEMSLOT::ARMOR])
							{
								CItem* pTemp = m_pHandleItem;
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pEquip[ITEMSLOT::ARMOR]->Set_ItemState(ITEMSTATE::HAND);
								m_pHandleItem->Set_Pos(990.f, 232.f);
								m_pHandleItem = m_pEquip[ITEMSLOT::ARMOR];
								m_pEquip[ITEMSLOT::ARMOR] = pTemp;
							}
							else
							{
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pHandleItem->Set_Pos(990.f, 232.f);
								m_pEquip[ITEMSLOT::ARMOR] = m_pHandleItem;
								m_pHandleItem = nullptr;
							}
						}
						//투구
						else if (eType == ITEMTYPE::HELM &&
							936 < fX && 1044 > fX && 77 < fY && 157 > fY)
						{
							if (m_pEquip[ITEMSLOT::HELM])
							{
								CItem* pTemp = m_pHandleItem;
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pEquip[ITEMSLOT::HELM]->Set_ItemState(ITEMSTATE::HAND);
								m_pHandleItem->Set_Pos(990.f, 117.f);
								m_pHandleItem = m_pEquip[ITEMSLOT::HELM];
								m_pEquip[ITEMSLOT::HELM] = pTemp;
							}
							else
							{
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pHandleItem->Set_Pos(990.f, 117.f);
								m_pEquip[ITEMSLOT::HELM] = m_pHandleItem;
								m_pHandleItem = nullptr;
							}
						}
						//목걸이
						else if (eType == ITEMTYPE::NECKLACE &&
							1067 < fX && 1121 > fX && 115 < fY && 157 > fY)
						{
							if (m_pEquip[ITEMSLOT::NECKLACE])
							{
								CItem* pTemp = m_pHandleItem;
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pEquip[ITEMSLOT::NECKLACE]->Set_ItemState(ITEMSTATE::HAND);
								m_pHandleItem->Set_Pos(1094.f, 136.f);
								m_pHandleItem = m_pEquip[ITEMSLOT::NECKLACE];
								m_pEquip[ITEMSLOT::NECKLACE] = pTemp;
							}
							else
							{
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pHandleItem->Set_Pos(1094.f, 136.f);
								m_pEquip[ITEMSLOT::NECKLACE] = m_pHandleItem;
								m_pHandleItem = nullptr;
							}
						}
						//장갑
						else if (eType == ITEMTYPE::GLOVES &&
							730 < fX && 838 > fX && 310 < fY && 392 > fY)
						{
							if (m_pEquip[ITEMSLOT::GLOVES])
							{
								CItem* pTemp = m_pHandleItem;
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pEquip[ITEMSLOT::GLOVES]->Set_ItemState(ITEMSTATE::HAND);
								m_pHandleItem->Set_Pos(784.f, 351.f);
								m_pHandleItem = m_pEquip[ITEMSLOT::GLOVES];
								m_pEquip[ITEMSLOT::GLOVES] = pTemp;
							}
							else
							{
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pHandleItem->Set_Pos(784.f, 351.f);
								m_pEquip[ITEMSLOT::GLOVES] = m_pHandleItem;
								m_pHandleItem = nullptr;
							}
						}
						//반지1
						else if (eType == ITEMTYPE::RING &&
							863 < fX && 917 > fX && 309 < fY && 351 > fY)
						{
							if (m_pEquip[ITEMSLOT::RING1])
							{
								CItem* pTemp = m_pHandleItem;
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pEquip[ITEMSLOT::RING1]->Set_ItemState(ITEMSTATE::HAND);
								m_pHandleItem->Set_Pos(890.f, 330.f);
								m_pHandleItem = m_pEquip[ITEMSLOT::RING1];
								m_pEquip[ITEMSLOT::RING1] = pTemp;
							}
							else
							{
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pHandleItem->Set_Pos(890.f, 330.f);
								m_pEquip[ITEMSLOT::RING1] = m_pHandleItem;
								m_pHandleItem = nullptr;
							}
						}
						//반지2
						else if (eType == ITEMTYPE::RING &&
							1067 < fX && 1121 > fX && 309 < fY && 351 > fY)
						{
							if (m_pEquip[ITEMSLOT::RING2])
							{
								CItem* pTemp = m_pHandleItem;
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pEquip[ITEMSLOT::RING2]->Set_ItemState(ITEMSTATE::HAND);
								m_pHandleItem->Set_Pos(1094.f, 330.f);
								m_pHandleItem = m_pEquip[ITEMSLOT::RING2];
								m_pEquip[ITEMSLOT::RING2] = pTemp;
							}
							else
							{
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pHandleItem->Set_Pos(1094.f, 330.f);
								m_pEquip[ITEMSLOT::RING2] = m_pHandleItem;
								m_pHandleItem = nullptr;
							}
						}
						//벨트
						else if (eType == ITEMTYPE::SASH &&
							936 < fX && 1044 > fX && 309 < fY && 351 > fY)
						{
							if (m_pEquip[ITEMSLOT::SASH])
							{
								CItem* pTemp = m_pHandleItem;
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pEquip[ITEMSLOT::SASH]->Set_ItemState(ITEMSTATE::HAND);
								m_pHandleItem->Set_Pos(990.f, 330.f);
								m_pHandleItem = m_pEquip[ITEMSLOT::SASH];
								m_pEquip[ITEMSLOT::SASH] = pTemp;
							}
							else
							{
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pHandleItem->Set_Pos(990.f, 330.f);
								m_pEquip[ITEMSLOT::SASH] = m_pHandleItem;
								m_pHandleItem = nullptr;
							}
						}
						//부츠
						else if (eType == ITEMTYPE::BOOTS &&
							1143 < fX && 1253 > fX && 310 < fY && 392 > fY)
						{
							if (m_pEquip[ITEMSLOT::BOOTS])
							{
								CItem* pTemp = m_pHandleItem;
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pEquip[ITEMSLOT::BOOTS]->Set_ItemState(ITEMSTATE::HAND);
								m_pHandleItem->Set_Pos(1198.f, 351.f);
								m_pHandleItem = m_pEquip[ITEMSLOT::BOOTS];
								m_pEquip[ITEMSLOT::BOOTS] = pTemp;
							}
							else
							{
								m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
								m_pHandleItem->Set_Pos(1198.f, 351.f);
								m_pEquip[ITEMSLOT::BOOTS] = m_pHandleItem;
								m_pHandleItem = nullptr;
							}
						}
					}
					//아래 인벤토리 위는 장비창
					else
					{
						INFO tTemp = m_pHandleItem->Get_Info();
						if (731 < tTemp.fX && 1253 > tTemp.fX + tTemp.iCX &&
							417 < tTemp.fY && 571 > tTemp.fY + tTemp.iCY)
						{
							switch (m_iCollNum)
							{
							case 0:
								m_pHandleItem->Set_ItemState(ITEMSTATE::INVEN);
								m_pHandleItem = nullptr;
								break;
							case 1:
								m_pHandleItem->Set_ItemState(ITEMSTATE::INVEN);
								m_pHandleItem = m_pColItem;
								m_pColItem->Set_ItemState(ITEMSTATE::HAND);
								m_pColItem = nullptr;
								break;
							default:
								break;
							}
						}
						//템창열고 벨트에 포션넣기
						else if (m_pHandleItem->Get_ItemType() == ITEMTYPE::USE)
						{
							if (m_bSash || m_bSashUp)
							{
								//1번
								if (757 < fX && 809 > fX && 627 < fY && 665 > fY && m_listSlot[POTIONSLOT::ONE].size() < 4)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(757.f, 742.f - 38 * m_listSlot[POTIONSLOT::ONE].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::ONE, m_listSlot[POTIONSLOT::ONE].size());
									m_listSlot[POTIONSLOT::ONE].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (757 < fX && 809 > fX && 665 <= fY && 703 > fY && m_listSlot[POTIONSLOT::ONE].size() < 3)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(757.f, 742.f - 38 * m_listSlot[POTIONSLOT::ONE].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::ONE, m_listSlot[POTIONSLOT::ONE].size());
									m_listSlot[POTIONSLOT::ONE].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (757 < fX && 809 > fX && 703 <= fY && 741 > fY && m_listSlot[POTIONSLOT::ONE].size() < 2)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(757.f, 742.f - 38 * m_listSlot[POTIONSLOT::ONE].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::ONE, m_listSlot[POTIONSLOT::ONE].size());
									m_listSlot[POTIONSLOT::ONE].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (757 < fX && 809 > fX && 741 <= fY && 779 > fY && m_listSlot[POTIONSLOT::ONE].size() < 1)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(757.f, 742.f - 38 * m_listSlot[POTIONSLOT::ONE].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::ONE, m_listSlot[POTIONSLOT::ONE].size());
									m_listSlot[POTIONSLOT::ONE].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								//2번
								else if (809 <= fX && 861 > fX && 627 < fY && 665 > fY && m_listSlot[POTIONSLOT::TWO].size() < 4)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(809.f, 742.f - 38 * m_listSlot[POTIONSLOT::TWO].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::TWO, m_listSlot[POTIONSLOT::TWO].size());
									m_listSlot[POTIONSLOT::TWO].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (809 <= fX && 861 > fX && 665 <= fY && 703 > fY && m_listSlot[POTIONSLOT::TWO].size() < 3)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(809.f, 742.f - 38 * m_listSlot[POTIONSLOT::TWO].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::TWO, m_listSlot[POTIONSLOT::TWO].size());
									m_listSlot[POTIONSLOT::TWO].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (809 <= fX && 861 > fX && 703 <= fY && 741 > fY && m_listSlot[POTIONSLOT::TWO].size() < 2)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(809.f, 742.f - 38 * m_listSlot[POTIONSLOT::TWO].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::TWO, m_listSlot[POTIONSLOT::TWO].size());
									m_listSlot[POTIONSLOT::TWO].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (809 <= fX && 861 > fX && 741 <= fY && 779 > fY && m_listSlot[POTIONSLOT::TWO].size() < 1)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(809.f, 742.f - 38 * m_listSlot[POTIONSLOT::TWO].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::TWO, m_listSlot[POTIONSLOT::TWO].size());
									m_listSlot[POTIONSLOT::TWO].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								//3번
								else if (861 <= fX && 913 > fX && 627 < fY && 665 > fY && m_listSlot[POTIONSLOT::THREE].size() < 4)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(861.f, 742.f - 38 * m_listSlot[POTIONSLOT::THREE].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::THREE, m_listSlot[POTIONSLOT::THREE].size());
									m_listSlot[POTIONSLOT::THREE].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (861 <= fX && 913 > fX && 665 <= fY && 703 > fY && m_listSlot[POTIONSLOT::THREE].size() < 3)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(861.f, 742.f - 38 * m_listSlot[POTIONSLOT::THREE].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::THREE, m_listSlot[POTIONSLOT::THREE].size());
									m_listSlot[POTIONSLOT::THREE].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (861 <= fX && 913 > fX && 703 <= fY && 741 > fY && m_listSlot[POTIONSLOT::THREE].size() < 2)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(861.f, 742.f - 38 * m_listSlot[POTIONSLOT::THREE].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::THREE, m_listSlot[POTIONSLOT::THREE].size());
									m_listSlot[POTIONSLOT::THREE].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (861 <= fX && 913 > fX && 741 <= fY && 779 > fY && m_listSlot[POTIONSLOT::THREE].size() < 1)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(861.f, 742.f - 38 * m_listSlot[POTIONSLOT::THREE].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::THREE, m_listSlot[POTIONSLOT::THREE].size());
									m_listSlot[POTIONSLOT::THREE].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								//4번
								else if (913 <= fX && 965 > fX && 627 < fY && 665 > fY && m_listSlot[POTIONSLOT::FOUR].size() < 4)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(913.f, 742.f - 38 * m_listSlot[POTIONSLOT::FOUR].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::FOUR, m_listSlot[POTIONSLOT::FOUR].size());
									m_listSlot[POTIONSLOT::FOUR].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (913 <= fX && 965 > fX && 665 <= fY && 703 > fY && m_listSlot[POTIONSLOT::FOUR].size() < 3)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(913.f, 742.f - 38 * m_listSlot[POTIONSLOT::FOUR].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::FOUR, m_listSlot[POTIONSLOT::FOUR].size());
									m_listSlot[POTIONSLOT::FOUR].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (913 <= fX && 965 > fX && 703 <= fY && 741 > fY && m_listSlot[POTIONSLOT::FOUR].size() < 2)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(913.f, 742.f - 38 * m_listSlot[POTIONSLOT::FOUR].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::FOUR, m_listSlot[POTIONSLOT::FOUR].size());
									m_listSlot[POTIONSLOT::FOUR].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
								else if (913 <= fX && 965 > fX && 741 <= fY && 779 > fY && m_listSlot[POTIONSLOT::FOUR].size() < 1)
								{
									m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
									m_pHandleItem->Set_Positon(913.f, 742.f - 38 * m_listSlot[POTIONSLOT::FOUR].size());
									m_pHandleItem->Set_SlotNum(POTIONSLOT::FOUR, m_listSlot[POTIONSLOT::FOUR].size());
									m_listSlot[POTIONSLOT::FOUR].emplace_back(m_pHandleItem);
									m_pHandleItem = nullptr;
								}
							}
							else
							{
								if (757 < fX && 809 > fX && 742 < fY && 780 > fY)
								{
									if (m_listSlot[POTIONSLOT::ONE].empty())
									{
										m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
										m_pHandleItem->Set_Positon(757.f, 742.f);
										m_pHandleItem->Set_SlotNum(POTIONSLOT::ONE, m_listSlot[POTIONSLOT::ONE].size());
										m_listSlot[POTIONSLOT::ONE].emplace_back(m_pHandleItem);
										m_pHandleItem = nullptr;
									}
									//else
									//{
									//	포션스왑 아마 안할거임
									//}
								}
								else if (809 <= fX && 861 > fX && 742 < fY && 780 > fY)
								{
									if (m_listSlot[POTIONSLOT::TWO].empty())
									{
										m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
										m_pHandleItem->Set_Positon(809.f, 742.f);
										m_pHandleItem->Set_SlotNum(POTIONSLOT::TWO, m_listSlot[POTIONSLOT::TWO].size());
										m_listSlot[POTIONSLOT::TWO].emplace_back(m_pHandleItem);
										m_pHandleItem = nullptr;
									}
								}
								else if (861 <= fX && 913 > fX && 742 < fY && 780 > fY)
								{
									if (m_listSlot[POTIONSLOT::THREE].empty())
									{
										m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
										m_pHandleItem->Set_Positon(861.f, 742.f);
										m_pHandleItem->Set_SlotNum(POTIONSLOT::THREE, m_listSlot[POTIONSLOT::THREE].size());
										m_listSlot[POTIONSLOT::THREE].emplace_back(m_pHandleItem);
										m_pHandleItem = nullptr;
									}
								}
								else if (913 <= fX && 965 > fX && 742 < fY && 780 > fY)
								{
									if (m_listSlot[POTIONSLOT::FOUR].empty())
									{
										m_pHandleItem->Set_ItemState(ITEMSTATE::EQUIP);
										m_pHandleItem->Set_Positon(913.f, 742.f);
										m_pHandleItem->Set_SlotNum(POTIONSLOT::FOUR, m_listSlot[POTIONSLOT::FOUR].size());
										m_listSlot[POTIONSLOT::FOUR].emplace_back(m_pHandleItem);
										m_pHandleItem = nullptr;
									}
								}
							}
						}
					}
				}
				m_iCollNum = 0;
				m_pColItem = nullptr;
			}
			//손에 없을때
			else
			{
				//실험용
				for (auto& pItem : m_listItem)
				{
					if (ITEMSTATE::FIELD == pItem->Get_State())
						continue;
					if (CCollisionMgr::Check_Item(CUIMgr::Get_Instance()->Get_Mouse().front(), pItem))
					{
						m_pLookItem = pItem;
						CUIMgr::Get_Instance()->Get_Mouse().front()->Set_Open(false);
					}
				}
				//
				if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
				{
					m_pHandleItem = m_pLookItem;
					if (m_pHandleItem)
					{
						if (ITEMSTATE::EQUIP == m_pHandleItem->Get_State())
						{
							ITEMTYPE::TYPE eTemp = m_pHandleItem->Get_ItemType();
							switch (eTemp)
							{
							case ITEMTYPE::WEAPON:
								m_pEquip[ITEMSLOT::WEAPON] = nullptr;
								break;
							case ITEMTYPE::ARMOR:
								m_pEquip[ITEMSLOT::ARMOR] = nullptr;
								break;
							case ITEMTYPE::HELM:
								m_pEquip[ITEMSLOT::HELM] = nullptr;
								break;
							case ITEMTYPE::NECKLACE:
								m_pEquip[ITEMSLOT::NECKLACE] = nullptr;
								break;
							case ITEMTYPE::GLOVES:
								m_pEquip[ITEMSLOT::GLOVES] = nullptr;
								break;
							case ITEMTYPE::RING:
								if (1000 < m_pHandleItem->Get_Info().fX)
									m_pEquip[ITEMSLOT::RING1] = nullptr;
								else
									m_pEquip[ITEMSLOT::RING2] = nullptr;
								break;
							case ITEMTYPE::SASH:
								m_pEquip[ITEMSLOT::SASH] = nullptr;
								break;
							case ITEMTYPE::BOOTS:
								m_pEquip[ITEMSLOT::BOOTS] = nullptr;
								break;
							case ITEMTYPE::USE:
								if (POTIONSLOT::END != m_pHandleItem->Get_SlotNumX())
								{
									auto& iter = m_listSlot[m_pHandleItem->Get_SlotNumX()].begin();
									for (int i = 0; i < m_pHandleItem->Get_SlotNumY(); ++i)
										++iter;
									iter = m_listSlot[m_pHandleItem->Get_SlotNumX()].erase(iter);
									for (; iter != m_listSlot[m_pHandleItem->Get_SlotNumX()].end(); ++iter)
										(*iter)->Slot_Down();
									m_pHandleItem->Set_SlotNum(POTIONSLOT::END, 0);
								}
								break;
							}
						}
						m_pHandleItem->Set_ItemState(ITEMSTATE::HAND);
					}
					else if (732 < fX && 787 > fX && 592 < fY && 633 > fY)
						m_bOpen = false;
				}
				if (m_bShop) //버그나면 볼것
				{
					if (m_pLookItem)
					{
						if (CKeyMgr::Get_Instance()->Key_Up(VK_RBUTTON))
						{
							static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_GoldPlus(m_pLookItem->Get_Gold() >> 1);
							m_listItem.erase(m_pLookItem->Get_Iter());
							SAFE_DELETE(m_pLookItem);
							m_pLookItem = nullptr;
							CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
							CSoundMgr::Get_Instance()->PlaySound(L"igold.wav", CSoundMgr::ITEM);
						}
					}
				}
			}
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
		}
		//템창 반대쪽에서 하는일
		else
		{
			if (m_bShop)
			{
				//템팔기?
				if (m_pHandleItem)
				{
					if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
					{
						if (155 < fX && 670 > fX && 160 < fY && 550 > fY)
						{
							static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_GoldPlus(m_pHandleItem->Get_Gold() >> 1);
							m_listItem.erase(m_pHandleItem->Get_Iter());
							SAFE_DELETE(m_pHandleItem);
							m_pHandleItem = nullptr;
							CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
							CSoundMgr::Get_Instance()->PlaySound(L"igold.wav", CSoundMgr::ITEM);
							//m_pHandleItem->Set_ItemState(ITEMSTATE::SHOP);
							//m_pHandleItem = nullptr;
						}
					}
				}
				else
				{
					//템정보 보기 아이템 구입
					for (auto& pItem : m_listItem)
					{
						if (ITEMSTATE::FIELD == pItem->Get_State())
							continue;
						if (CCollisionMgr::Check_Item(CUIMgr::Get_Instance()->Get_Mouse().front(), pItem))
						{
							m_pLookItem = pItem;
							CUIMgr::Get_Instance()->Get_Mouse().front()->Set_Open(false);
							break;
						}
					}
					if (m_pLookItem)
					{
						if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Gold() >= m_pLookItem->Get_Gold())
						{
							if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
							{
								static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_GoldPlus(-m_pLookItem->Get_Gold());
								if (ITEMTYPE::USE == m_pLookItem->Get_ItemType())
								{
									if (m_pLookItem->Get_PInfo().iHp)
										m_pHandleItem = new CHpPotion(573, 513, ITEMSTATE::HAND);
									else
										m_pHandleItem = new CMpPotion(0, 0, ITEMSTATE::HAND);
									m_pHandleItem->Initialize();
									m_listItem.emplace_back(m_pHandleItem);
									m_pHandleItem->Set_Iter(--m_listItem.end());
								}
								else
								{
									m_pHandleItem = m_pLookItem;
									m_pHandleItem->Set_ItemState(ITEMSTATE::HAND);
								}
							}
							//우클릭 구매
							else if (CKeyMgr::Get_Instance()->Key_Up(VK_RBUTTON))
							{
								static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_GoldPlus(-m_pLookItem->Get_Gold());
								if (ITEMTYPE::USE == m_pLookItem->Get_ItemType())
								{
									if (m_pLookItem->Get_PInfo().iHp)
										m_pLookItem = new CHpPotion(573, 513, ITEMSTATE::HAND);
									else
										m_pLookItem = new CMpPotion(0, 0, ITEMSTATE::HAND);
									m_pLookItem->Initialize();
									m_listItem.emplace_back(m_pLookItem);
									m_pLookItem->Set_Iter(--m_listItem.end());
								}
								bool bCheck = true;
								m_pLookItem->Set_ItemState(ITEMSTATE::INVEN);
								m_pLookItem->SizeReverse();
								for (int i = 0; i < 4; ++i)
								{
									for (int j = 0; j < 10; ++j)
									{
										m_pLookItem->Set_Positon(float(732 + 52 * j), float(418 + 38 * i));
										if (1253 < (m_pLookItem->Get_Info().fX + m_pLookItem->Get_Info().iCX))
											continue;
										if (573 < (m_pLookItem->Get_Info().fY + m_pLookItem->Get_Info().iCY))
											continue;
										for (auto& Item : m_listItem)
										{
											if (ITEMSTATE::INVEN == Item->Get_State())
											{
												if (CCollisionMgr::Check_ItemRect(m_pLookItem, Item))
												{
													bCheck = false;
													break;
												}
											}
										}
										if (bCheck)
										{
											m_pLookItem = nullptr;
											return;
										}
										bCheck = true;
									}
								}
								static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_GoldPlus(m_pLookItem->Get_Gold());
								m_listItem.erase(m_pLookItem->Get_Iter());
								SAFE_DELETE(m_pLookItem);
								m_pLookItem = nullptr;
								//m_pLookItem->Set_ItemState(ITEMSTATE::FIELD);
								//m_pLookItem->Set_Size(50, 40);
								//m_pLookItem->Set_DropPos(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - 20.f, CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - 20.f);
								//m_pLookItem = nullptr;
							}
						}
					}
					else if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON) && 615 < fX && 670 > fX && 594 < fY && 635 > fY)
					{
						CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
						CSoundMgr::Get_Instance()->PlaySound(L"Ghe_farewell.wav", CSoundMgr::UI);
						m_bShop = false;
					}
				}
			}
			else
			{
				for (auto& pItem : m_listItem)
				{
					if (ITEMSTATE::SHOP == pItem->Get_State())
						continue;
					if (CCollisionMgr::Check_Item(CUIMgr::Get_Instance()->Get_Mouse().front(), pItem))
						m_pLookItem = pItem;
				}
				if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
				{
					if (m_pHandleItem)
					{
						m_pHandleItem->Set_ItemState(ITEMSTATE::FIELD);
						m_pHandleItem->Set_Size(50, 40);
						m_pHandleItem->Set_DropPos(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - 20.f, CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - 20.f);
						m_pHandleItem = nullptr;
					}
					else
					{
						m_pPickItem = CCollisionMgr::Collision_Item(CUIMgr::Get_Instance()->Get_Mouse(), m_listItem);
					}
				}
			}
		}
	}
	//템창 닫았을때
	else
	{
		if (m_bShop)
		{
			//템팔기?
			if (m_pHandleItem)
			{
				if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
				{
					if (155 < fX && 670 > fX && 160 < fY && 550 > fY)
					{
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_GoldPlus(m_pHandleItem->Get_Gold() >> 1);
						m_listItem.erase(m_pHandleItem->Get_Iter());
						SAFE_DELETE(m_pHandleItem);
						m_pHandleItem = nullptr;
						//m_pHandleItem->Set_ItemState(ITEMSTATE::SHOP);
						//m_pHandleItem = nullptr;
					}
				}
			}
			else if ((WINCX >> 1) > fX)
			{
				//템정보 보기 아이템 구입
				for (auto& pItem : m_listItem)
				{
					if (ITEMSTATE::FIELD == pItem->Get_State())
						continue;
					if (CCollisionMgr::Check_Item(CUIMgr::Get_Instance()->Get_Mouse().front(), pItem))
					{
						m_pLookItem = pItem;
						CUIMgr::Get_Instance()->Get_Mouse().front()->Set_Open(false);
						break;
					}
				}
				if (m_pLookItem)
				{
					if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Gold() >= m_pLookItem->Get_Gold() && CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
					{
						m_pHandleItem = m_pLookItem;
						m_pHandleItem->Set_ItemState(ITEMSTATE::HAND);
						static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_GoldPlus(-m_pHandleItem->Get_Gold());
					}
				}
				else if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON) && 615 < fX && 670 > fX && 594 < fY && 635 > fY)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
					CSoundMgr::Get_Instance()->PlaySound(L"Ghe_farewell.wav", CSoundMgr::UI);
					m_bShop = false;
				}
			}
		}
		else if (m_pHandleItem)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				m_pHandleItem->Set_ItemState(ITEMSTATE::FIELD);
				m_pHandleItem->Set_Size(50, 40);
				m_pHandleItem->Set_DropPos(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - 20.f, CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - 20.f);
				m_pHandleItem = nullptr;
			}
		}
		else
		{
			for (auto& pItem : m_listItem)
			{
				if (ITEMSTATE::FIELD == pItem->Get_State()
					&& CCollisionMgr::Check_Item(CUIMgr::Get_Instance()->Get_Mouse().front(), pItem))
					m_pLookItem = pItem;
			}
			if (CKeyMgr::Get_Instance()->Key_Up(VK_LBUTTON))
			{
				m_pPickItem = CCollisionMgr::Collision_Item(CUIMgr::Get_Instance()->Get_Mouse(), m_listItem);
			}
		}
	}
	//허리띠
	if (CKeyMgr::Get_Instance()->Key_Down('1'))
		PotionUse(POTIONSLOT::ONE);
	else if (CKeyMgr::Get_Instance()->Key_Down('2'))
		PotionUse(POTIONSLOT::TWO);
	else if (CKeyMgr::Get_Instance()->Key_Down('3'))
		PotionUse(POTIONSLOT::THREE);
	else if (CKeyMgr::Get_Instance()->Key_Down('4'))
		PotionUse(POTIONSLOT::FOUR);
	//치트
	else if (CKeyMgr::Get_Instance()->Key_Down('5'))
	{
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->HpPotion_Use(100);
		static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->MpPotion_Use(100);
	}
	if (m_pEquip[ITEMSLOT::SASH])
	{
		if (m_bSash || m_bSashUp)
		{
			if (755 < fX && 965 > fX && 627 < fY && 743 > fY)
				m_bSashUp = true;
			else
				m_bSashUp = false;
		}
		if (757 < fX && 965 > fX && 742 < fY && 780 > fY)
			m_bSash = true;
		else
			m_bSash = false;
	}
}

void CInven::Render(HDC _DC)
{
	for (auto& pItem : m_listItem)
	{
		pItem->FieldRender(_DC);
	}
	//아이템창 랜더
	if (m_bOpen)
	{
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Inven");
		BitBlt(_DC, WINCX>>1, 0, 700, 734, m_hMemDC, 0, 0, SRCCOPY);

		TCHAR pTemp[32] = L"";
		wsprintf(pTemp, L"%d",static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_Gold());
		TextOut(_DC, 900, 604, pTemp, lstrlen(pTemp));
	}
	if (m_bSash || m_bSashUp)
	{
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"BeltSlot");
		BitBlt(_DC, 755, 627, 208, 114, m_hMemDC, 0, 0, SRCCOPY);
	}
	//상점 랜더
	if (m_bShop)
	{
		m_hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Shop");

		BitBlt(_DC, 0, 0, 700, 734, m_hMemDC, 0, 0, SRCCOPY);

		if (50 < MathMgr::Get_Distance(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_Obj(OBJID::NPC).front()))
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
			CSoundMgr::Get_Instance()->PlaySound(L"Ghe_farewell.wav", CSoundMgr::UI);
			m_bShop = false;
		}
	}
	//아이템 랜더
	for (auto& pItem : m_listItem)
	{
		pItem->Set_Sash(m_bSash || m_bSashUp);
		pItem->Set_Open(m_bOpen);
		pItem->Set_Shop(m_bShop);
		pItem->Render(_DC);
	}
	for (auto& pItem : m_listItem)
	{
		pItem->HandRender(_DC);
	}
	if (m_pLookItem)
	{
		m_pLookItem->Set_BackFrame(L"gBack");
		m_pLookItem->InfoRender(_DC);
		m_pLookItem = nullptr;
	}
}

void CInven::Release()
{
	for_each(m_listItem.begin(), m_listItem.end(), Safe_Delete<CItem*>);
	m_listItem.clear();
	m_pHandleItem = nullptr;
}

void CInven::Function()
{
}

void CInven::Create_Item(CItem* _pItem)
{
	m_listItem.emplace_back(_pItem);
	_pItem->Set_Iter(--m_listItem.end());
}

void CInven::PickItem()
{
	if (m_pPickItem)
	{
		if (m_bOpen)
		{
			m_pPickItem->Set_ItemState(ITEMSTATE::HAND);
			m_pPickItem->SizeReverse();
			m_pHandleItem = m_pPickItem;
			m_pPickItem = nullptr;
		}
		else
		{
			bool bCheck = true;
			m_pPickItem->Set_ItemState(ITEMSTATE::INVEN);
			m_pPickItem->SizeReverse();
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					m_pPickItem->Set_Positon(float(732 + 52 * j), float(418 + 38 * i));
					if (1253 < (m_pPickItem->Get_Info().fX + m_pPickItem->Get_Info().iCX))
						continue;
					if (573 < (m_pPickItem->Get_Info().fY + m_pPickItem->Get_Info().iCY))
						continue;
					for (auto& Item : m_listItem)
					{
						if (ITEMSTATE::INVEN == Item->Get_State())
						{
							if (CCollisionMgr::Check_ItemRect(m_pPickItem, Item))
							{
								bCheck = false;
								break;
							}
						}
					}
					if (bCheck)
					{
						m_pPickItem = nullptr;
						return;
					}
					bCheck = true;
				}
			}
			m_pPickItem->Set_ItemState(ITEMSTATE::FIELD);
			m_pPickItem->Set_Size(50, 40);
			m_pPickItem->Set_DropPos(CObjMgr::Get_Instance()->Get_Player()->Get_Info().fX - 20.f, CObjMgr::Get_Instance()->Get_Player()->Get_Info().fY - 20.f);
			m_pPickItem = nullptr;
		}
	}
}

void CInven::PotionUse(POTIONSLOT::SLOT _eSlot)
{
	if (!m_listSlot[_eSlot].empty())
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ITEM);
		CSoundMgr::Get_Instance()->PlaySound(L"ipotionui.wav", CSoundMgr::ITEM);
		if (m_listSlot[_eSlot].front()->Get_PInfo().iHp)
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->HpPotion_Use(m_listSlot[_eSlot].front()->Get_PInfo().iHp);
		if (m_listSlot[_eSlot].front()->Get_PInfo().iMp)
			static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->MpPotion_Use(m_listSlot[_eSlot].front()->Get_PInfo().iMp);
		m_listItem.erase(m_listSlot[_eSlot].front()->Get_Iter());
		SAFE_DELETE(m_listSlot[_eSlot].front());
		if (m_pLookItem)
			m_pLookItem = nullptr;
		m_listSlot[_eSlot].pop_front();
		for (auto& i : m_listSlot[_eSlot])
			i->Slot_Down();
	}
}

void CInven::Shop()
{
	if (CObjMgr::Get_Instance()->Get_Obj(OBJID::NPC).empty())
		return;
	if (50 > MathMgr::Get_Distance(CObjMgr::Get_Instance()->Get_Player(), CObjMgr::Get_Instance()->Get_Obj(OBJID::NPC).front()))
	{
		m_bOpen = true;
		if (!m_bShop)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::UI);
			CSoundMgr::Get_Instance()->PlaySound(L"Ghe_goodday.wav", CSoundMgr::UI);
			m_bShop = true;
		}
	}
}
