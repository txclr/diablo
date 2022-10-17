#pragma once

#ifndef __STATUS_H__
#define __STATUS_H__

#include "UI.h"

class CStatus :
	public CUI
{
public:
	CStatus();
	~CStatus();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void Function() override;

public:
	void Set_Run(bool _bRun) { m_bRun = _bRun; }

private:
	bool m_bRun;
	bool m_bLevel;
	HDC  m_hMemDC;
	PLAYERINFO m_tPlayerInfo;
};


#endif // !__STATUS_H__