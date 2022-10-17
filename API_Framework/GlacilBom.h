#pragma once
#include "Obj.h"
class CGlacilBom :
	public CObj
{
public:
	CGlacilBom();
	~CGlacilBom();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	bool m_bDie;
};

