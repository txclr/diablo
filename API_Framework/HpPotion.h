#pragma once
#include "Item.h"
class CHpPotion :
	public CItem
{
public:
	CHpPotion();
	CHpPotion(float _fX, float _fY, ITEMSTATE::STATE _eState);
	~CHpPotion();

public:
	virtual void Initialize() override;

public:
	virtual void FieldRender(HDC _DC);
	virtual void InfoRender(HDC _DC);
	virtual void SizeReverse();
};