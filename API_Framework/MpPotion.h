#pragma once
#include "Item.h"
class CMpPotion :
	public CItem
{
public:
	CMpPotion();
	CMpPotion(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CMpPotion();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

