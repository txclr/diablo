#pragma once

#ifndef __MYEDIT_H__
#define __MYEDIT_H__

class CLine;
class CMyEdit
{
private:
	CMyEdit();
	~CMyEdit();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

private:
	void Key_Check();

public:
	void Save_Line();
	void Load_Line();

public:
	static CMyEdit* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CMyEdit;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

public:
	static CMyEdit*	m_pInstance;
	list<CLine*>	m_listLIne;
	LINEPOS			m_tLinePos[2];
	bool			m_bCheck;
};


#endif // !__MYEDIT_H__
