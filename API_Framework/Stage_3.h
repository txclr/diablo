#pragma once
#include "Scene.h"
class CStage_3 :
	public CScene
{
public:
	CStage_3();
	~CStage_3();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
};

