#include "stdafx.h"
#include "MpBall.h"
#include "BmpMgr.h"
#include "Player.h"
#include "ObjMgr.h"

CMpBall::CMpBall()
{
}


CMpBall::~CMpBall()
{
}

void CMpBall::Initialize()
{
	m_tInfo = { 1208,WINCY - 163 ,140,140 };
	Update_Rect();
}

void CMpBall::Update()
{
	Update_Rect();
}

void CMpBall::Render(HDC _DC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MPBall");
	float iRate = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MpRate();
	int iTemp = int(140 * iRate);
	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MPBall");
	GdiTransparentBlt(_DC
		, m_tRect.left + 1, m_tRect.top + iTemp - 1
		, m_tInfo.iCX, m_tInfo.iCY - iTemp
		, hMemDC
		, 0, iTemp
		, m_tInfo.iCX, m_tInfo.iCY - iTemp
		, RGB(255, 255, 255));
	//반투명피
	if (m_bOpen)
	{
		iTemp = int(140 * static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_MpRestoreRate());
		CBmpMgr::Alpha_Blend(_DC, m_tRect.left, m_tRect.top + iTemp, 140, 140 - iTemp, hMemDC, 0, iTemp, 140, 140 - iTemp, RGB(255, 255, 255), 170);
	}
}

void CMpBall::Release()
{
}

void CMpBall::Function()
{
}

