#pragma once
#include "Obj.h"
class CPotal :
	public CObj
{
public:
	CPotal();
	~CPotal();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Update_Rect()
	{
		m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
		m_tRect.top = (LONG)(m_tInfo.fY - m_tInfo.iCY);
		m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
		m_tRect.bottom = (LONG)(m_tInfo.fY);
	}
};

