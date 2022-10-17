#pragma once

#ifndef __MOUSE_H__
#define __MOUSE_H__


#include "UI.h"
class CMouse : public CUI
{
public:
	CMouse();
	virtual ~CMouse();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void Function() override;
};


#endif // !__MOUSE_H__
