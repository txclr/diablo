#pragma once
#include "Obj.h"
class COrbDes :
	public CObj
{
public:
	COrbDes();
	~COrbDes();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

