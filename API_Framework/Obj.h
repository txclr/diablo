#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

public:
	void Update_Rect();
	//void Move_Frame();

public:
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x; m_tInfo.fY = _y; }
	void Set_Dead() { m_bDead = true; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void Set_Pos_Y(float _y) { m_tInfo.fY += _y; }
	void Set_Pos_X(float _x) { m_tInfo.fX += _x; }
	void Set_XPos(float _x) { m_tInfo.fX = _x; }
	void Set_YPos(float _y) { m_tInfo.fY = _y; }
	void Set_FrameKey(TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }
	void Set_GroupID(GROUPID::ID _ID) { m_eGroup = _ID; }
	void Set_Option(int _iOption) { m_iOption = _iOption; }
	void Set_Effect(bool _bEffect) { m_bEffect = _bEffect; }
	void Set_Life(int _iLife) { m_iLife = _iLife; }
	void Set_Damage(int _iLife) { m_iLife -= _iLife; }

public:
	const RECT& Get_Rect() const { return m_tRect; }
	const INFO& Get_Info() const { return m_tInfo; }
	const bool& Get_Dead() const { return m_bDead; }
	const float& Get_Angle() const { return m_fAngle; }
	const bool& Get_Effect() const { return m_bEffect; }
	const int& Get_Life() const { return m_iLife; }
	const int& Get_MaxLife() const { return m_iMaxLife; }
	float Get_Liferate() { return float(m_iLife) / m_iMaxLife; }
	int Get_Option() { return m_iOption; }
	TCHAR* Get_FrameKey() { return m_pFrameKey; }

public:
	GROUPID::ID Get_GroupID() { return m_eGroup; }

protected:
	INFO			m_tInfo;
	RECT			m_tRect;

	float			m_fSpeed;

	bool			m_bDead;
	bool			m_bEffect;
	bool			m_bRect;

	float			m_fAngle;
	
	CObj*			m_pTarget;

	TCHAR*			m_pFrameKey;

	//FRAME	m_tFrame;

	GROUPID::ID		m_eGroup;
	int				m_iOption;
	int				m_iMaxLife;
	int				m_iLife;
	float			m_fTime;
};


#endif // !__OBJ_H__
