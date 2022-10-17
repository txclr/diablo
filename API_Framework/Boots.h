#pragma once
#include "Item.h"
class CBoots :
	public CItem
{
public:
	CBoots();
	CBoots(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CBoots();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

