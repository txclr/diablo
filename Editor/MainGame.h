#pragma once

#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();		// 초기화
	void Update();			// 매 프레임마다 갱신하는 함수
	void Late_Update();
	void Render();			// 매 프레임마다 그려주는 함수
	void Release();			// 메모리 해제

private:
	HDC				m_DC;

	TCHAR			m_szFPS[16];
	int				m_iFPS;
	DWORD			m_dwTime;
};


#endif // !__MAINGAME_H__
