#pragma once
#include "Obj.h"
class CGlacialSpike :
	public CObj
{
public:
	CGlacialSpike();
	~CGlacialSpike();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

