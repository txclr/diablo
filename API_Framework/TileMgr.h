#pragma once

#ifndef __TILEMGR_H__
#define __TILEMGR_H__

class CTile;
class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	vector<CObj*> Get_TileList() { return m_vecTile; }

public:
	void Picking_Tile(int& _iIter, int _iDrawID, int _iOption, bool _bAniCheck);

public:
	void Save_Tile();
	void Load_Tile(SCENE::SCENE _eScene);

public:
	static CTileMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CTileMgr*	m_pInstance;
	vector<CObj*>		m_vecTile;
};


#endif // !__TILEMGR_H__
