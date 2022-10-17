#pragma once
#include "Scene.h"

class CObj;
class CStage_1 : public CScene {
public:
	CStage_1();
	virtual ~CStage_1();
public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	int m_iTime;
};

