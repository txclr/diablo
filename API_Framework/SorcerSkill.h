#pragma once
#include "stdafx.h"
#include "Bullet.h"
#include "ChargedBolt.h"
#include "IceBolt.h"
#include "IceBlast.h"
#include "GlacialSpike.h"
#include "FrostNova.h"
#include "Blizzard.h"
#include "FrostOrb.h"
#include "ObjMgr.h"
#include "SoundMgr.h"

#ifndef __SORCERSKILL_H__
#define __SORCERSKILL_H__

void Shot(float& _fX, float& _fY, float _fAngle, int _iLevel);
void MultiShot(float& _fX, float& _fY, float _fAngle, int _iLevel);
void ChargedBolt(float& _fX, float& _fY, float _fAngle, int _iLevel);
void IceBolt(float& _fX, float& _fY, float _fAngle, int _iLevel);
void IceBlast(float& _fX, float& _fY, float _fAngle, int _iLevel);
void FrostNova(float& _fX, float& _fY, float _fAngle, int _iLevel);
void FrozenOrb(float& _fX, float& _fY, float _fAngle, int _iLevel);
void GlacialSpike(float& _fX, float& _fY, float _fAngle, int _iLevel);
void Blizzard(float& _fX, float& _fY, float _fAngle, int _iLevel);

void Shot(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	CObj* pObj = CAbstractFactory<CBullet>::Create(_fX, _fY - 38, _fAngle, 10);
	CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
}

void MultiShot(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	CObj* pObj;
	float fTemp;
	for (int i = 0; i < 8; ++i)
	{
		fTemp = _fAngle - 7 * PI / 32 + i*PI / 16;
		if (0 > fTemp)
			fTemp += 2 * PI;
		if (2 * PI < fTemp)
			fTemp -= 2 * PI;
		pObj = CAbstractFactory<CBullet>::Create(_fX, _fY - 38, fTemp, _iLevel*5);
		CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
	}
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
	CSoundMgr::Get_Instance()->PlaySound(L"smulti4.wav", CSoundMgr::EFFECT);
}

void ChargedBolt(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	CObj* pObj;
	float fTemp;
	for (int i = 0; i < (_iLevel+1); ++i)
	{
		fTemp = _fAngle - _iLevel*PI / 32 + i*PI / 16;
		if (0 > fTemp)
			fTemp += 2 * PI;
		if (2 * PI < fTemp)
			fTemp -= 2 * PI;
		pObj = CAbstractFactory<CChargedBolt>::Create(_fX, _fY - 38, fTemp, 10);
		CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
	}
}

void IceBolt(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	CObj* pObj = CAbstractFactory<CIceBolt>::Create(_fX, _fY - 38, _fAngle, _iLevel*5);
	CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
}

void IceBlast(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	CObj* pObj = CAbstractFactory<CIceBlast>::Create(_fX, _fY - 38, _fAngle, _iLevel * 10);
	CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
}

void FrostNova(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	CObj* pObj;
	for (int i = 0; i < 8; ++i)
	{
		pObj = CAbstractFactory<CFrostNova>::Create(_fX, _fY, i*PI/4, _iLevel);
		CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, pObj);
	}
}

void FrozenOrb(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	CObj* pObj = CAbstractFactory<CFrostOrb>::Create(_fX, _fY - 38, _fAngle, _iLevel * 5);
	CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
}

void GlacialSpike(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	float fX = float(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MPoint().x)-25;
	float fY = float(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MPoint().y)-360;
	CObj* pObj = CAbstractFactory<CGlacialSpike>::Create(fX, fY, _fAngle, _iLevel * 2);
	CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
}

void Blizzard(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	float fX = float(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MPoint().x);
	float fY = float(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MPoint().y);
	CObj* pObj = CAbstractFactory<CBlizzard>::Create(fX, fY, _fAngle, _iLevel);
	CObjMgr::Get_Instance()->Add_Object(OBJID::EFFECT, pObj);
}

void Teleport(float& _fX, float& _fY, float _fAngle, int _iLevel)
{
	_fX = float(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MPoint().x);
	_fY = float(static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MPoint().y);
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SKILL);
	CSoundMgr::Get_Instance()->PlaySound(L"steleport.wav", CSoundMgr::SKILL);
}

#endif // !__SORCERSKILL_H__