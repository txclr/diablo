#pragma once

#ifndef __TILE_H__
#define __TILE_H__


#include "Obj.h"
class CTile : public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }
	void Set_AniCheck(bool _bCheck) { m_bAniCheck = _bCheck; }
	void Set_Image() { m_bCheck = true; }

public:
	int Get_DrawID() { return m_iDrawID; }
	bool Get_AniCheck() { return m_bAniCheck; }

private:
	int		m_iDrawID;
	bool	m_bCheck;
	bool	m_bAniCheck;
	float	m_fTime;
	DWORD	m_dwTime;
};


#endif // !__TILE_H__
