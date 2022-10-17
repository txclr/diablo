#pragma once

#ifndef __OBJMGR_H__
#define __OBJMGR_H__


class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	void Add_Object(OBJID::ID _eID, CObj* _pObj);
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();
	void ReleaseNP();
	void Delete_ID(OBJID::ID _eID);
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
public:
	CObj* Get_Player() { return m_listObj[OBJID::PLAYER].front(); }
	list<CObj*> Get_Obj(OBJID::ID _eID) { return m_listObj[_eID]; }
	CObj* Get_Target(CObj* _Dst, OBJID::ID _eID);

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CObjMgr*	m_pInstance;
	list<CObj*>		m_listObj[OBJID::END];
	list<CObj*>		m_listRenderGroup[GROUPID::END];
	bool			m_bRect;
	CObj*			m_pTarget;
};


#endif // !__OBJMGR_H__
