#pragma once
#include "Item.h"
class CStaff :
	public CItem
{
public:
	CStaff();
	CStaff(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CStaff();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

