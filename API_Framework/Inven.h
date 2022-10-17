#pragma once
#include "UI.h"
#ifndef __INVEN_H__
#define __INVEN_H__

class CItem;
class CInven :
	public CUI
{
public:
	CInven();
	~CInven();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void Function() override;

public:
	void Create_Item(CItem* _pItem);
	void PickItem();
	void PotionUse(POTIONSLOT::SLOT _eSlot);
	void Shop();

public:
	void Set_HandleItem(CItem* _pItem) { m_pHandleItem = _pItem; }

public:
	bool& Get_Shop() { return m_bShop; }

//public:
//	CItem*& Get_PickItem() { return m_pPickItem; }

private:
	bool		m_bShop;
	bool		m_bSash;
	bool		m_bSashUp;
	int			m_iCollNum;
	list<CItem*>m_listItem;
	CItem*		m_pPickItem;
	CItem*		m_pLookItem;
	CItem*		m_pColItem;
	CItem*		m_pHandleItem;
	CItem*		m_pEquip[ITEMSLOT::END];
	list<CItem*>m_listSlot[POTIONSLOT::END];
	HDC			m_hMemDC;
	//list<CItem*>m_list2Slot;
	//list<CItem*>m_list3Slot;
	//list<CItem*>m_list4Slot;
};

#endif // __INVEN_H__