#pragma once

#ifndef __SCENE__H_
#define __SCENE__H_

class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;

public:
	SCENE::SCENE Get_Scen() { return m_eStage; }
	void Set_Scene(SCENE::SCENE _eStage) { m_eStage = _eStage; }

protected:
	SCENE::SCENE m_eStage;
};

#endif // !__SCENE__H_