#pragma once

#ifndef __MATHMGR_H__
#define __MATHMGR_H__

class CObj;
class MathMgr
{
public:
	MathMgr();
	~MathMgr();

public:
	static float Get_Distance(CObj* _pDst, CObj* _pSrc);
	static float Get_Distance(float _DstX, float _DstY, float _SrcX, float _SrcY);
	static float Get_Angle(CObj* _pDst, CObj* _pSrc);
	static float Get_Angle(float _DstX, float _DstY, float _SrcX, float _SrcY);
};


#endif // !__MATHMGR_H__
