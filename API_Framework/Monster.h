#pragma once

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Obj.h"
class CMonster : public CObj
{
public:
	CMonster();
	virtual ~CMonster();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Update_Rect()
	{
		m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
		m_tRect.top = (LONG)(m_tInfo.fY - m_tInfo.iCY);
		m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
		m_tRect.bottom = (LONG)(m_tInfo.fY);
	}

private:
	float	m_fEffectTime;
	float	m_fActionSpeed;
	float	m_fAttTime;
	float	m_fAtt;
	bool	m_bEffect1;
	bool	m_bAtt;
	bool	m_bOut;
	STATE::STATE m_eState;
	CObj*	m_pPlayer;
};


#endif // !__MONSTER_H__
