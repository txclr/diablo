#include "stdafx.h"
#include "HpBall.h"
#include "BmpMgr.h"
#include "Player.h"
#include "ObjMgr.h"

CHpBall::CHpBall()
{
	m_bOpen = false;
}


CHpBall::~CHpBall()
{
}

void CHpBall::Initialize()
{
	m_tInfo = { 48,WINCY - 163,140 ,140 };
	Update_Rect();
}

void CHpBall::Update()
{
	Update_Rect();
}

void CHpBall::Render(HDC _DC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"HPBall");
	float iRate = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_HpRate();
	int iTemp = int(140 * iRate);
	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"HPBall");
	GdiTransparentBlt(_DC
		, m_tRect.left, m_tRect.top + iTemp
		, m_tInfo.iCX, m_tInfo.iCY - iTemp
		, hMemDC
		, 0, iTemp
		, m_tInfo.iCX, m_tInfo.iCY - iTemp
		, RGB(255, 255, 255));
	//반투명피
	if (m_bOpen)
	{
		iTemp = int(140 * static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_HpRestoreRate());
		CBmpMgr::Alpha_Blend(_DC,m_tRect.left,m_tRect.top + iTemp,140,140 - iTemp,hMemDC,0, iTemp,140,140 - iTemp,RGB(255,255,255),170);
	}
}

void CHpBall::Release()
{
}

void CHpBall::Function()
{
}

