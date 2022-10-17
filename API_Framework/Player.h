#pragma once
#include "Obj.h"

#ifndef __PLAYER_H__
#define __PLAYER_H__

class CPlayer : public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Move();
	void Skill();
	void Attack();
	void Ani(HDC _DC);
	void Map(HDC _DC);

public:
	float Get_HpRestoreRate();
	float Get_MpRestoreRate();
	float Get_HpRate() { return (float(m_tPInfo.iMaxHp - m_tPInfo.iHp) / m_tPInfo.iMaxHp); }
	float Get_MpRate() { return (float(m_tPInfo.iMaxMp - m_tPInfo.iMp) / m_tPInfo.iMaxMp); }
	const int& Get_Gold() { return m_tPInfo.iGold; }
	const PLAYERINFO& Get_PlayerInfo() { return m_tPInfo; }
	const POINT& Get_MPoint() { return m_tMPoint; }
	int	Get_iRemainSkill() { return m_iRemainSkill; }

public:
	void Set_Str(int _iStr) { m_tPInfo.iStr += _iStr; }
	void Set_Dex(int _iDex) { m_tPInfo.iDex += _iDex; m_tPInfo.iMaxStamina += _iDex*10; m_tPInfo.iStamina += _iDex*10; }
	void Set_Life(int _iLife) { m_tPInfo.iLife += _iLife; m_tPInfo.iMaxHp += _iLife*10; m_tPInfo.iHp += _iLife*10; }
	void Set_Energy(int _iEnergy) { m_tPInfo.iEnergy += _iEnergy; m_tPInfo.iMaxMp += _iEnergy*10; m_tPInfo.iMp += _iEnergy*10; }
	void Set_RemainStat() { m_tPInfo.iRemainStat -= 1; }
	void Set_RemainSkill() { m_iRemainSkill -= 1; }
	void Set_ItemPlus(PLAYERINFO _tInfo) { m_tPInfo += _tInfo; Set_Stat(); };
	void Set_ItemMinus(PLAYERINFO _tInfo) { m_tPInfo -= _tInfo; Set_Stat(); };
	void Set_Move(bool _bMove) { m_bMove = _bMove; }
	void Set_State(STATE::STATE _eState) { m_eState = _eState; }
	void Set_MainSkill(SKILLINFO*& _pSkillInfo) { m_tMainSkill = _pSkillInfo; }
	void Set_GoldPlus(int _iGold) { m_tPInfo.iGold += _iGold; }
	void Set_Resulrect() { m_tPInfo.iHp = m_tPInfo.iMaxHp; m_tPInfo.iMp = m_tPInfo.iMaxMp; m_bDead = false; }
	bool Set_DDamage(int _Damage) 
	{ 
		if (STATE::DEAD != m_eState)
		{
			m_tPInfo.iHp -= _Damage; Set_Hitted();
			return true;
		}
		else
			return false;
	}
	void Set_Hitted();
	void Set_Stat() 
	{
		m_tPInfo.iMaxHp = 100 + 10 * m_tPInfo.iLife; 
		m_tPInfo.iMaxMp = 100 + 10 * m_tPInfo.iEnergy;
		m_tPInfo.iMaxStamina = 100 + 10 * m_tPInfo.iDex;
		if (m_tPInfo.iMaxHp < m_tPInfo.iHp)
			m_tPInfo.iHp = m_tPInfo.iMaxHp;
		if (m_tPInfo.iMaxMp < m_tPInfo.iMp)
			m_tPInfo.iMp = m_tPInfo.iMaxMp;
	}
	void Set_ReSet() { m_tInfo = m_tBeforePos; }
	void Set_ExpPlus(int _Exp) { m_tPInfo.iExp += _Exp; }

public:
	void OffSet();
	void HpPotion_Use(int _iHp);
	void MpPotion_Use(int _iMp);

public:
	void Update_Rect()
	{
		m_tRect.left = (LONG)(m_tBeforePos.fX - (m_tBeforePos.iCX >> 1));
		m_tRect.top = (LONG)(m_tBeforePos.fY - m_tBeforePos.iCY);
		m_tRect.right = (LONG)(m_tBeforePos.fX + (m_tBeforePos.iCX >> 1));
		m_tRect.bottom = (LONG)(m_tBeforePos.fY);
	}

private:
	PLAYERINFO	m_tPInfo;
	int			m_iRemainSkill;
	INFO		m_tBeforePos;
	POINT		m_tMPoint;
	bool		m_bRun;
	bool		m_bMove;
	bool		m_bMap;
	bool		m_bOffset;
	bool		m_bSkill;
	bool		m_bAtt;
	float		m_fSkill;
	float		m_fAtt;
	STATE::STATE m_eState;

	float		m_fCastingTime;
	float		m_fAttTime;
	float		m_fHittedTime;

	bool		m_bHpRestore;
	bool		m_bMpRestore;
	int			m_iHpRestore;
	int			m_iMpRestore;

	SKILLINFO*	m_tMainSkill;
};


#endif // !__PLAYER_H__
