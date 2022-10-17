#pragma once
#include "UI.h"

#ifndef __MPBALL_H__
#define __MPBALL_H__

class CMpBall :
	public CUI
{
public:
	CMpBall();
	~CMpBall();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void Function() override;
};

#endif // !__MPBALL_H__