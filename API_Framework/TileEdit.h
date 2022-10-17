#pragma once

#ifndef __TILEEDIT_H__
#define __TILEEDIT_H__


#include "Scene.h"
class CTileEdit : public CScene
{
public:
	CTileEdit();
	virtual ~CTileEdit();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	void	Key_Check();
	float	m_fScrollX;
	float	m_fScrollY;
	float	m_fMX;
	float	m_fMY;
	POINT	m_tMouse;

	int		m_iIter;
	int		m_iDrawID;
	int		m_iOption;
	TCHAR*	m_pFrameKey;
	bool	m_bAniCheck;
};


#endif // !__TILEEDIT_H__