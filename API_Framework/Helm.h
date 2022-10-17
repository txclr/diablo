#pragma once
#include "Item.h"
class CHelm :
	public CItem
{
public:
	CHelm();
	CHelm(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CHelm();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

