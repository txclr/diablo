#pragma once
#include "Obj.h"
class CDiabllo :
	public CObj
{
public:
	CDiabllo();
	~CDiabllo();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	float	m_fEffectTime;
	float	m_fActionSpeed;
	float	m_fAttTime;
	float	m_fAtt;
	float	m_fCastTime;
	float	m_fRunTime;
	float	m_fBeamTime;
	bool	m_bEffect1;
	bool	m_bAtt;
	bool	m_bRun;
	STATE::STATE m_eState;
	CObj*	m_pPlayer;
};

