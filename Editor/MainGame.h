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
	void Initialize();		// �ʱ�ȭ
	void Update();			// �� �����Ӹ��� �����ϴ� �Լ�
	void Late_Update();
	void Render();			// �� �����Ӹ��� �׷��ִ� �Լ�
	void Release();			// �޸� ����

private:
	HDC				m_DC;

	TCHAR			m_szFPS[16];
	int				m_iFPS;
	DWORD			m_dwTime;
};


#endif // !__MAINGAME_H__
