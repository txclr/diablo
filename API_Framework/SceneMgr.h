#pragma once
#ifndef __CSCENEMGR
#define __CSCENEMGR

class CScene;
class CSceneMgr
{
public:
	CSceneMgr();
	~CSceneMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	void SetScene(SCENE::SCENE _eScene);
	CScene* Get_Scene() { return m_pScene; }

public:
	static CSceneMgr* Get_Instance() 
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CSceneMgr*		m_pInstance;
	CScene*					m_pScene;
};

#endif // !__CSCENEMGR