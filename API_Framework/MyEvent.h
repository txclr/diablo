#pragma once
#include "UI.h"
class CMyEvent :
	public CUI
{
public:
	CMyEvent();
	~CMyEvent();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	virtual void Function() override;

public:
	void Set_SealPlus() { m_iSeal += 1; }

public:
	void Event();

private:
	CObj* m_pPlayer;
	int	m_iTime;
	bool m_bPotal;
	int	m_iSeal;
};

