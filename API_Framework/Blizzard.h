#pragma once
#include "Obj.h"
class CBlizzard :
	public CObj
{
public:
	CBlizzard();
	~CBlizzard();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	float	m_fShotTime;
};

