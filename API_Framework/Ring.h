#pragma once
#include "Item.h"
class CRing :
	public CItem
{
public:
	CRing();
	CRing(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CRing();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

