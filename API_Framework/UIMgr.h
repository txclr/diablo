#pragma once

#ifndef __UIMGR__H__
#define __UIMGR__H__

class CUI;
class CUIMgr
{
public:
	CUIMgr();
	~CUIMgr();

public:
	void Add_Object(UIID::ID _eID);
	void Initialize();
	void Update();
	void Render(HDC _DC);
	void Release();

public:
	vector<CUI*> Get_Mouse() { return m_vecUI[UIID::MOUSE]; }
	vector<CUI*> Get_Statu() { return m_vecUI[UIID::STATUS]; }
	vector<CUI*> Get_Skill() { return m_vecUI[UIID::SKILL]; }
	vector<CUI*> Get_Inven() { return m_vecUI[UIID::INVEN]; }
	vector<CUI*> Get_Event() { return m_vecUI[UIID::EVENT]; }
	vector<CUI*> Get_HpBal() { return m_vecUI[UIID::HPBALL]; }
	vector<CUI*> Get_MpBal() { return m_vecUI[UIID::MPBALL]; }

public:
	static CUIMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CUIMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CUIMgr*	m_pInstance;
	vector<CUI*>	m_vecUI[UIID::END];
};

#endif // !__UIMGR__H__