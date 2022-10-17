#pragma once
#include "Item.h"
class CSash :
	public CItem
{
public:
	CSash();
	CSash(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CSash();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

