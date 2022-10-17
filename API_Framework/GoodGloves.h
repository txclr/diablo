#pragma once
#include "Item.h"
class CGoodGloves :
	public CItem
{
public:
	CGoodGloves();
	CGoodGloves(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CGoodGloves();

public:
	virtual void Initialize() override;
	void Set_ItemState(ITEMSTATE::STATE _eState);

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

