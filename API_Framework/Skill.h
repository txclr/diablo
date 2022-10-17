#pragma once
#include "UI.h"

#ifndef __SKILL_H__
#define __SKILL_H__

class CSkill :
	public CUI
{
public:
	CSkill();
	~CSkill();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	SKILLINFO*& Get_SkillInfo() { return m_pMainSkill; }

public:
	void Set_Back(int _iBack) { m_iBack = _iBack; }
	void Function() { m_bQuick = !m_bQuick; }
	void Key();
	void SkillUp();

private:
	bool				m_bQuick;
	bool				m_bFcheck;
	int					m_iLevel;
	int					m_iBack;
	SKILLINFO*			m_pMainSkill;
	SKILLINFO*			m_pFSkill[SKILLSLOT::END];
	SKILLINFO*			m_pSkill[SKILL::END];
	vector<SKILLINFO*>	m_vecpSkillInfo;
	HDC					m_hMemDC;
};

#endif // !__SKILL_H__