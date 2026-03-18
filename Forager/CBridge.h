#pragma once
#include "CBuilding.h"
class CBridge : public CBuilding
{
public:
	CBridge();
	~CBridge();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	//이동 가능 , 짓기 가능
	void Change_Ground();
};

