#pragma once
#include "CBuilding.h"
class CSewingStation : public CBuilding
{
public:
	CSewingStation();
	~CSewingStation();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Change_Ground();

};

