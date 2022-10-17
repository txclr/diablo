#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false), m_bRect(false), m_bEffect(false), m_fAngle(0.f), m_fTime(0.f), m_pTarget(nullptr), m_eGroup(GROUPID::END), m_iMaxLife(0)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}


CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}

//void CObj::Move_Frame()
//{
//	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
//	{
//		++m_tFrame.iFrameStart;
//		m_tFrame.dwFrameTime = GetTickCount();
//
//		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
//			m_tFrame.iFrameStart = 0;
//	}
//}
