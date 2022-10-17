#pragma once
#include "Item.h"
class CGoodBoots :
	public CItem
{
public:
	CGoodBoots();
	CGoodBoots(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CGoodBoots();

public:
	virtual void Initialize() override;
	void Set_ItemState(ITEMSTATE::STATE _eState);

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

