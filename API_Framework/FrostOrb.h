#pragma once
#include "Obj.h"
class CFrostOrb :
	public CObj
{
public:
	CFrostOrb();
	~CFrostOrb();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	float	m_fShotTime;
	float	m_fAngle1;
};

