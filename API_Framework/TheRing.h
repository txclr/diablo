#pragma once
#include "Item.h"
class CTheRing :
	public CItem
{
public:
	CTheRing();
	CTheRing(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CTheRing();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

