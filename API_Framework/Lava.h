#pragma once
#include "Obj.h"
class CLava :
	public CObj
{
public:
	CLava();
	~CLava();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Set_DrawID(int _iDrawID) { m_iDrawID = _iDrawID; }

public:
	int Get_DrawID() { return m_iDrawID; }

private:
	int		m_iDrawID;
	float	m_fTime;
};

