#pragma once
#include "Scene.h"
class CStage_2 :
	public CScene
{
public:
	CStage_2();
	~CStage_2();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	int m_iTime;
};

