#pragma once
#include "Define.h"

class CScene
{
public:
	CScene();
	~CScene();

public:
	virtual void Initailize() PURE;
	virtual void Update() PURE;
	virtual void Late_Update() PURE;
	virtual void Render(HDC hDC) PURE;
	virtual void Release() PURE;

};

