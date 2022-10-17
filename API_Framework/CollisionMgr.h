#pragma once

#ifndef __COLLISIONMGR_H__
#define __COLLISIONMGR_H__

class CObj;
class CUI;
class CItem;
class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_A(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Att(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_AttM(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Tile(vector<CUI*>& _Dst, vector<CObj*>& _Src, int& _iter);
	//static bool Collision_PTile(vector<CUI*>& _Dst, vector<CObj*>& _Src);
	static void Collision_UI(vector<CUI*>& _Dst, vector<CUI*>& _Src);
	static void Collision_UI1(vector<CUI*>& _Dst, vector<CUI*>& _Src);
	static CItem* Collision_Item(vector<CUI*>& _Dst, list<CItem*>& _Src);
	//static void Collision_Sphere(list<CObj*>& _Dst, list<CObj*>& _Src);

	static bool Check_Sphere(CObj* _pDst, CObj* _pSrc);
	static bool Check_Rect(CObj* _pDst, CObj* _pSrc, float* _x, float* _y);
	static bool Check_ItemRect(CItem* _pDst, CItem* _pSrc);
	static bool Check_Tile(CUI* _pDst, CObj* _pSrc);
	static bool Check_Tile(CObj * _pDst, CObj * _pSrc);
	static bool Check_UI(CUI* _pDst, CUI* _pSrc);
	static bool Check_Item(CUI* _pDst, CItem* _pSrc);
};

#endif // !__COLLISIONMGR_H__
