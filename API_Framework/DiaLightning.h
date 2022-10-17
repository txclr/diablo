#pragma once
#include "Obj.h"
class CDiaLightning :
	public CObj
{
public:
	CDiaLightning();
	~CDiaLightning();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool	m_bDie;
};

