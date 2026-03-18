#pragma once
#include "CUI.h"
class CWordIsland : public CUI
{
public:
	CWordIsland();
	~CWordIsland();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

