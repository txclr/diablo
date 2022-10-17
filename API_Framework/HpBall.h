#pragma once
#include "UI.h"

#ifndef __HPBALL_H__
#define __HPBALL_H__

class CHpBall :
	public CUI
{
public: 
	CHpBall();
	~CHpBall();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void Function() override;

};

#endif // !__HPBALL_H__
