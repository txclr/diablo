#pragma once
#include "Item.h"
class CGloves :
	public CItem
{
public:
	CGloves();
	CGloves(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CGloves();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

