#pragma once
#include "Obj.h"
class CFire :
	public CObj
{
public:
	CFire();
	~CFire();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	bool	m_bDie;
};

