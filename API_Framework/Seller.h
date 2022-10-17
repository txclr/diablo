#pragma once
#include "Obj.h"
class CSeller :
	public CObj
{
public:
	CSeller();
	~CSeller();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

