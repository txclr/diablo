#pragma once

#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagInfo
{
	float	fX;
	float	fY;
	int		iCX;
	int		iCY;
}INFO;


typedef struct tagLinePos
{
	tagLinePos() { ZeroMemory(this, sizeof(tagLinePos)); }
	tagLinePos(float _x, float _y) : fX(_x), fY(_y) {}

	float	fX;
	float	fY;
}LINEPOS;

typedef struct tagLineInfo
{
	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& _tLeft, LINEPOS& _tRight) : tLeftPos(_tLeft), tRightPos(_tRight) {}

	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;
}LINEINFO;

typedef struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iFrameScene;
	DWORD	dwFrameSpeed;
	DWORD	dwFrameTime;
}FRAME;

typedef struct tagSkillInfo
{
	TCHAR*	pFKeyMatch = {};
	TCHAR*	pFrameKey;
	int		iLevel;
	int		iUseMp;
	void(*Skill)(float&, float&, float, int);
	tagSkillInfo** tKeyFind = nullptr;
}SKILLINFO;

typedef struct tagPlayerInfo
{
	tagPlayerInfo& operator+=(tagPlayerInfo& _Info)
	{
		iStr		+= _Info.iStr;
		iDex		+= _Info.iDex;
		iLife		+= _Info.iLife;
		iEnergy		+= _Info.iEnergy;
		iHp			+= _Info.iHp;
		iMaxHp		+= _Info.iMaxHp;
		iMp			+= _Info.iMp;
		iMaxMp		+= _Info.iMaxMp;
		iMaxExp		+= _Info.iMaxExp;
		iExp		+= _Info.iExp;
		iLevel		+= _Info.iLevel;
		iMaxStamina	+= _Info.iMaxStamina;
		iStamina	+= _Info.iStamina;
		iRemainStat	+= _Info.iRemainStat;
		iAttSpeed	+= _Info.iAttSpeed;
		iMoveSpeed	+= _Info.iMoveSpeed;
		iSkillUp	+= _Info.iSkillUp;
		return *this;
	}
	tagPlayerInfo& operator-=(tagPlayerInfo& _Info)
	{
		iStr		-= _Info.iStr;
		iDex		-= _Info.iDex;
		iLife		-= _Info.iLife;
		iEnergy		-= _Info.iEnergy;
		iHp			-= _Info.iHp;
		iMaxHp		-= _Info.iMaxHp;
		iMp			-= _Info.iMp;
		iMaxMp		-= _Info.iMaxMp;
		iMaxExp		-= _Info.iMaxExp;
		iExp		-= _Info.iExp;
		iLevel		-= _Info.iLevel;
		iMaxStamina	-= _Info.iMaxStamina;
		iStamina	-= _Info.iStamina;
		iRemainStat	-= _Info.iRemainStat;
		iAttSpeed	-= _Info.iAttSpeed;
		iMoveSpeed	-= _Info.iMoveSpeed;
		iSkillUp	-= _Info.iSkillUp;
		return *this;
	}
	int			iStr;
	int			iDex;
	int			iLife;
	int			iEnergy;
	int			iHp;
	int			iMaxHp;
	int			iMp;
	int			iMaxMp;
	int			iMaxExp;
	int			iBeforeExp;
	int			iExp;
	int			iLevel;
	int			iMaxStamina;
	int			iStamina;
	int			iRemainStat;
	int			iAttSpeed;
	int			iMoveSpeed;
	int			iSkillUp;
	int			iGold;
}PLAYERINFO;
#endif // !__STRUCT_H__
