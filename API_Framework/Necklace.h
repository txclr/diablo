#pragma once
#include "Item.h"
class CNecklace :
	public CItem
{
public:
	CNecklace();
	CNecklace(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CNecklace();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

