#pragma once
#include "Obj.h"

#ifndef __CHARGEDBOLT_H__
#define __CHARGEDBOLT_H__

class CChargedBolt :
	public CObj
{
public:
	CChargedBolt();
	~CChargedBolt();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	int		m_iFrame;
};

#endif // !__CHARGEDBOLT_H__