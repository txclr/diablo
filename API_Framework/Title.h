#pragma once
#include "Scene.h"
class CTitle :
	public CScene
{
public:
	CTitle();
	~CTitle();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:
	float	m_fTime;
};

