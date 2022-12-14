#pragma once

#ifndef __KEYMGR_H__
#define __KEYMGR_H__

#define VK_MAX 0xFF
class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public:
	bool Key_Pressing(int _Key);
	bool Key_Down(int _Key);
	bool Key_Up(int _Key);
	void Key_Update();

public:
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CKeyMgr* m_pInstance;
	bool			m_bKeyState[VK_MAX];
};


#endif // !__KEYMGR_H__
