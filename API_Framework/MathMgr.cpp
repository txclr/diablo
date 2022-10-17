#include "stdafx.h"
#include "MathMgr.h"
#include "Obj.h"

MathMgr::MathMgr()
{
}


MathMgr::~MathMgr()
{
}

//두 점 객체 사이의 거리
float MathMgr::Get_Distance(CObj * _pDst, CObj * _pSrc)
{
	float fWidth = abs(_pDst->Get_Info().fX - _pSrc->Get_Info().fX);
	float fHeight = abs(_pDst->Get_Info().fY - _pSrc->Get_Info().fY)*2;
	float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fDistance;
}
//두 점 사이의 거리
float MathMgr::Get_Distance(float _DstX, float _DstY, float _SrcX, float _SrcY)
{
	float fWidth = abs(_DstX - _SrcX);
	float fHeight = abs(_DstY - _SrcY)*2;
	float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fDistance;
}

//두 객체 사이의 각도
float MathMgr::Get_Angle(CObj * _pDst, CObj * _pSrc)
{
	float fWidth = _pDst->Get_Info().fX - _pSrc->Get_Info().fX;
	float fHeight = (_pDst->Get_Info().fY - _pSrc->Get_Info().fY)*2;
	float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float fAngle = acosf(fWidth / fDistance);

	if (_pDst->Get_Info().fY < _pSrc->Get_Info().fY)
	{
		fAngle *= -1.f;
		fAngle += PI;
	}

	return fAngle;
}

//두 점 사이의 각도
float MathMgr::Get_Angle(float _DstX, float _DstY, float _SrcX, float _SrcY)
{
	float fWidth = _DstX - _SrcX;
	float fHeight = (_DstY - _SrcY)*2;
	float fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float fAngle = acosf(fWidth / fDistance);

	if (_SrcY > _DstY)
	{
		fAngle *= -1.f;
		fAngle += 2*PI;
	}

	return fAngle;
}
