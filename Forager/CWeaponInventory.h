#pragma once
#include "CUI.h"
class CWeaponInventory :public CUI
{
public:
	CWeaponInventory();
	~CWeaponInventory();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

};

