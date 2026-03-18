#pragma once
#include "CUI.h"
class CWeaponSlot : public CUI
{
public:
	CWeaponSlot();
	~CWeaponSlot();
	
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

};

