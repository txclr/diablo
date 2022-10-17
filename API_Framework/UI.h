#pragma once

#ifndef __CUI_H__
#define __CUI_H__

class CUI
{
public:
	CUI();
	virtual ~CUI();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;
	virtual void Function() = 0;

public:
	void Update_Rect();

public:
	void Set_KeyInfo(TCHAR* _pFramekey, INFO _tInfo) { m_pFrameKey = _pFramekey; m_tInfo = _tInfo; }
	void Set_Info(INFO _tInfo) { m_tInfo = _tInfo; }
	void Set_Open(bool _bOpen) { m_bOpen = _bOpen; }
	void Set_Positon(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }

public:
	const bool& Get_Open() { return m_bOpen; }
	const INFO& Get_Info() { return m_tInfo; }
	const RECT& Get_Rect() { return m_tRect; }

protected:
	bool			m_bOpen;
	INFO			m_tInfo;
	RECT			m_tRect;

	TCHAR*			m_pFrameKey;
};

#endif // !__CUI_H__