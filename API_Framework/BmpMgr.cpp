#include "stdafx.h"
#include "BmpMgr.h"
#include "MyBitmap.h"

CBmpMgr* CBmpMgr::m_pInstance = nullptr;
CBmpMgr::CBmpMgr()
{
}


CBmpMgr::~CBmpMgr()
{
	Release();
}

void CBmpMgr::Insert_Bmp(const TCHAR * _pFilePath, const TCHAR * _pImageKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStringCMP(_pImageKey));

	if (m_mapBit.end() == iter)
	{
		CMyBitmap* pBmp = new CMyBitmap;
		pBmp->Load_Bmp(_pFilePath);

		m_mapBit.emplace(_pImageKey, pBmp);
	}
}

HDC CBmpMgr::Find_Image(const TCHAR * _pImageKey)
{
	auto iter = find_if(m_mapBit.begin(), m_mapBit.end(), CStringCMP(_pImageKey));

	if (m_mapBit.end() == iter)
		return nullptr;

	return iter->second->Get_MemDC();
}

void CBmpMgr::Release()
{
	for (auto& iter : m_mapBit)
	{
		if (nullptr != iter.second)
			SAFE_DELETE(iter.second);
	}
	m_mapBit.clear();
}

void CBmpMgr::Alpha_Blend(HDC _DC, int _iDstX, int _iDstY, int _iDstW, int _iDstH, HDC _MemDC, int _iSrcX, int _iSrcY, int _iSrcW, int _iSrcH, UINT _rClr, int _iAlpha)
{

	HDC MemAlphaDC;
	HBITMAP   AlphaBit;
	HBITMAP OldAlphaBit;

	MemAlphaDC = CreateCompatibleDC(_DC);

	AlphaBit = CreateCompatibleBitmap(_MemDC, _iDstW, _iDstH);
	OldAlphaBit = (HBITMAP)SelectObject(MemAlphaDC, AlphaBit);

	BLENDFUNCTION bf;
	bf.AlphaFormat = 0;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = _iAlpha;


	BitBlt(MemAlphaDC, 0, 0, _iDstW, _iDstH, _DC, _iDstX, _iDstY, SRCCOPY);
	GdiTransparentBlt(MemAlphaDC, 0, 0, _iDstW, _iDstH, _MemDC, _iSrcX, _iSrcY, _iSrcW, _iSrcH, _rClr);
	GdiAlphaBlend(_DC, _iDstX, _iDstY, _iDstW, _iDstH, MemAlphaDC, 0, 0, _iDstW, _iDstH, bf);


	SelectObject(MemAlphaDC, OldAlphaBit);
	DeleteObject(AlphaBit);
	DeleteDC(MemAlphaDC);
}