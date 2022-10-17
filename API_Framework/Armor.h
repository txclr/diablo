#pragma once
#include "Item.h"
class CArmor :
	public CItem
{
public:
	CArmor();
	CArmor(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CArmor();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};

