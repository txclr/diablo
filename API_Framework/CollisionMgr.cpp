#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "UI.h"
#include "Item.h"
#include "Player.h"
#include "Tile.h"
#include "Skill.h"
#include "Effect.h"
#include "ScrollMgr.h"
#include "ObjMgr.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_A(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};
	float fTemp;
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				fTemp = Dst->Get_Angle() + PI;
				if (fTemp > 2 * PI)
					fTemp -= 2 * PI;
				Src->Set_Angle(fTemp);
				Src->Set_Effect(Dst->Get_Effect());
				Dst->Set_Dead();
	/*			Src->Set_Pos_X(5 * cosf(fTemp));
				Src->Set_Pos_Y(5 * sinf(fTemp));*/
			}
		}
	}
}

void CCollisionMgr::Collision_Att(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				Src->Set_Damage(Dst->Get_Life());
				Src->Set_Effect(Dst->Get_Effect());
				Dst->Set_Dead();
				CObjMgr::Get_Instance()->Set_Target(Src);
			}
		}
	}
}

void CCollisionMgr::Collision_AttM(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dst->Get_Rect()), &(Src->Get_Rect())))
			{
				if (static_cast<CPlayer*>(Src)->Set_DDamage(Dst->Get_Life()))
					Dst->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Tile(vector<CUI*>& _Dst, vector<CObj*>& _Src, int& _iTer)
{
	int iTemp = 0;
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Tile(Dst, Src))
			{
				static_cast<CTile*>(Src)->Set_Image();
				_iTer = iTemp;
			}
			++iTemp;
		}
	}
}

//bool CCollisionMgr::Collision_PTile(vector<CUI*>& _Dst, vector<CObj*>& _Src)
//{
//	for (auto& Dst : _Dst)
//	{
//		for (auto& Src : _Src)
//		{
//			if (Check_Tile(Dst, Src))
//			{
//				if(!Src->Get_Effect())
//					return true;
//				return false;
//			}
//		}
//	}
//	return false;
//}

void CCollisionMgr::Collision_UI(vector<CUI*>& _Dst, vector<CUI*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_UI(Dst, Src))
			{
				static_cast<CSkill*>(Src)->Set_Back(2);
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
			}
		}
	}
}

void CCollisionMgr::Collision_UI1(vector<CUI*>& _Dst, vector<CUI*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_UI(Dst, Src))
			{
				Src->Function();
				static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Set_Move(false);
			}
		}
	}
}

CItem* CCollisionMgr::Collision_Item(vector<CUI*>& _Dst, list<CItem*>& _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Item(Dst, Src))
			{
				if(ITEMSTATE::FIELD ==  Src->Get_State())
					return Src;
			}
		}
	}
	return nullptr;
}

//void CCollisionMgr::Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src)
//{
//	for (auto& Dst : _Dst)
//	{
//		for (auto& Src : _Src)
//		{
//			if (Check_Sphere(Dst, Src))
//			{
//				Dst->Set_Dead();
//				Src->Set_Dead();
//			}
//		}
//	}
//}

bool CCollisionMgr::Check_Sphere(CObj* _pDst, CObj* _pSrc)
{
	float fX = abs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX);
	float fY = abs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY);
	float fDis = sqrtf(fX * fX + fY * fY);

	float fRad = (float)((_pDst->Get_Info().iCX + _pSrc->Get_Info().iCX) >> 1);

	return fDis <= fRad;
}

bool CCollisionMgr::Check_Rect(CObj* _pDst, CObj* _pSrc, float* _x, float* _y)
{
	// 중점간의 거리
	float fX = abs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX);
	float fY = abs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY);

	// 반지름 합
	float fCX = (float)((_pDst->Get_Info().iCX + _pSrc->Get_Info().iCX) >> 1);
	float fCY = (float)((_pDst->Get_Info().iCY + _pSrc->Get_Info().iCY) >> 1);

	if (fCX > fX && fCY > fY)
	{
		*_x = fCX - fX;
		*_y = fCY - fY;
		return true;
	}
	return false;
}

//bool CCollisionMgr::Check_ItemRect(CUI* _pDst, CUI* _pSrc)
//{
//	if (_pDst == _pSrc)
//		return false;
//	// 중점간의 거리
//	float fX = abs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX + _pDst->Get_Info().iCX - _pSrc->Get_Info().iCX);
//	float fY = abs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY);
//
//	// 반지름 합
//	float fCX = (float)((_pDst->Get_Info().iCX + _pSrc->Get_Info().iCX) >> 1);
//	float fCY = (float)((_pDst->Get_Info().iCY + _pSrc->Get_Info().iCY) >> 1);
//
//	if (fCX > fX && fCY > fY)
//	{
//		return true;
//	}
//	return false;
//}

bool CCollisionMgr::Check_ItemRect(CItem* _pDst, CItem* _pSrc)
{
	if (_pDst == _pSrc)
		return false;

	RECT tTemp;
	RECT tDst = { LONG(_pDst->Get_Info().fX),LONG(_pDst->Get_Info().fY), LONG(_pDst->Get_Info().fX + _pDst->Get_Info().iCX), LONG(_pDst->Get_Info().fY + _pDst->Get_Info().iCY) };
	RECT tSrc = { LONG(_pSrc->Get_Info().fX),LONG(_pSrc->Get_Info().fY), LONG(_pSrc->Get_Info().fX + _pSrc->Get_Info().iCX), LONG(_pSrc->Get_Info().fY + _pSrc->Get_Info().iCY) };
	if (IntersectRect(&tTemp, &tDst, &tSrc))
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::Check_Tile(CUI* _pDst, CObj* _pSrc)
{
	// 중점간의 거리
	float fX = abs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX - CScrollMgr::Get_Instance()->Get_Scroll_X());
	float fY = abs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY - CScrollMgr::Get_Instance()->Get_Scroll_Y());
	//TILECX, TILECY 는 사실 pSrc의 x,y크기여야함 TileCX체크 필요 없음
	if (TILECX > fX &&
		TILECY - fX > 2*fY )
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::Check_Tile(CObj* _pDst, CObj* _pSrc)
{
	// 중점간의 거리
	float fX = abs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX);
	float fY = abs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY);
	//TILECX, TILECY 는 사실 pSrc의 x,y크기여야함
	if (TILECY + 20 - fX > 2 * fY)
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::Check_UI(CUI* _pDst, CUI* _pSrc)
{
	POINT tTemp = { LONG(_pDst->Get_Info().fX),LONG(_pDst->Get_Info().fY) };
	RECT tRect = _pSrc->Get_Rect();
	if(PtInRect(&tRect, tTemp))
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::Check_Item(CUI* _pDst, CItem* _pSrc)
{
	POINT tTemp = { LONG(_pDst->Get_Info().fX),LONG(_pDst->Get_Info().fY) };
	RECT tRect = _pSrc->Get_Rect();
	if (PtInRect(&tRect, tTemp))
	{
		return true;
	}
	return false;
}