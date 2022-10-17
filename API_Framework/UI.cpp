#include "stdafx.h"
#include "UI.h"


CUI::CUI()
	:m_bOpen(false)
{
}


CUI::~CUI()
{
}

void CUI::Update_Rect()
{
	m_tRect = { LONG(m_tInfo.fX),LONG(m_tInfo.fY),LONG(m_tInfo.fX + m_tInfo.iCX),LONG(m_tInfo.fY + m_tInfo.iCY) };
}
