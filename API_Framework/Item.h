#pragma once

#ifndef __ITEM_H__
#define __ITEM_H__

class CItem
{
public:
	CItem();
	CItem(TCHAR* _pFramekey, INFO _tInfo, ITEMSTATE::STATE _eState);
	~CItem();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render(HDC _DC);
	virtual void Release();
	virtual void Function();

public:
	ITEMSTATE::STATE Get_State() { return m_eState; }
	ITEMTYPE::TYPE	 Get_ItemType() { return m_eType; }

public:
	void Update_Rect();

public:
	//void Set_KeyInfo(TCHAR* _pFramekey, INFO _tInfo) { m_pFrameKey = _pFramekey; m_tInfo = _tInfo; }
	//void Set_Info(INFO _tInfo) { m_tInfo = _tInfo; }
	void Set_Open(bool _bOpen) { m_bOpen = _bOpen; }
	void Set_Shop(bool _bShop) { m_bShop = _bShop; }
	void Set_Positon(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void Set_BackFrame(TCHAR* _pKey) { m_pBackFrame = _pKey; }
	void Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX - (m_tInfo.iCX>>1); m_tInfo.fY = _fY - (m_tInfo.iCY>>1); }
	void Set_DropPos(float _iX, float _iY) { m_tDropPos.x = LONG(_iX); m_tDropPos.y = LONG(_iY); }
	void Set_Size(int _iCX, int _ICY) { m_tInfo.iCX = _iCX; m_tInfo.iCY = _ICY; }
	void Set_SlotNum(POTIONSLOT::SLOT _eNum, int _iNum) { m_eSlot = _eNum; m_iSlotNum = _iNum; }
	void Set_Sash(bool _bCheck) { m_bSash = _bCheck; }
	void Set_Iter(list<CItem*>::iterator& _Iter) { m_Iter = _Iter; }
	virtual void Set_ItemState(ITEMSTATE::STATE _eState);

public:
	const bool& Get_Open() { return m_bOpen; }
	const INFO& Get_Info() { return m_tInfo; }
	const RECT& Get_Rect() { return m_tRect; }
	const int& Get_Gold() { return m_tItemInfo.iGold; }
	const PLAYERINFO& Get_PInfo() { return m_tItemInfo; }
	const POTIONSLOT::SLOT& Get_SlotNumX() { return m_eSlot; }
	const int& Get_SlotNumY() { return m_iSlotNum; }
	const list<CItem*>::iterator& Get_Iter() { return m_Iter; }

public:
	void HandRender(HDC _DC);
	virtual void FieldRender(HDC _DC) = 0;
	virtual void InfoRender(HDC _DC) = 0;
	virtual void SizeReverse() = 0;

public:
	void Slot_Down() { m_tInfo.fY += 38; m_iSlotNum -= 1; }

protected:
	bool				m_bOpen;
	bool				m_bSash;
	bool				m_bDrop;
	bool				m_bShop;
	INFO				m_tInfo;
	RECT				m_tRect;
	TCHAR*				m_pFrameKey;
	HDC					m_hMemDC;
	RECT				m_tFeildSize;
	PLAYERINFO			m_tItemInfo;
	ITEMSTATE::STATE	m_eState;
	ITEMTYPE::TYPE		m_eType;
	TCHAR*				m_pBackFrame;
	TCHAR*				m_pDropFrame;
	int					m_iDropTime;
	POINT				m_tDropPos;
	POTIONSLOT::SLOT	m_eSlot;
	int					m_iSlotNum;
	list<CItem*>::iterator m_Iter;
};

#endif // !__ITEM_H__