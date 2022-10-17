#pragma once

#ifndef __LINEMGR_H__
#define __LINEMGR_H__


class CLine;
class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();

public:
	void Initialize();
	void Render(HDC _DC);
	void Release();

public:
	bool Collision_Line(float& _x, float& _y, int _iCY);

private:
	void Load_Line();

public:
	static CLineMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CLineMgr*	m_pInstance;
	list<CLine*>		m_listLine;
};


#endif // !__LINEMGR_H__
