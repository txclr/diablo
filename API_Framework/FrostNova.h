#pragma once
#include "Obj.h"
class CFrostNova :
	public CObj
{
public:
	CFrostNova();
	~CFrostNova();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	bool m_bDie;
};

