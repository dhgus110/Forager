#pragma once
#include "CBuilding.h"
class CFishTrap : public CBuilding
{
public:
	CFishTrap();
	~CFishTrap();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
public:
	const bool Get_Fishing() const { return m_bfishing; }
public:
	void Set_Fishing(bool _b) { m_bfishing = _b; m_dwTime = (DWORD)GetTickCount64(); }

private:
	void Fishing();
	void Change_Ground();
private:
	bool m_bfishing; //Æ÷È¹ ½Ã true
	DWORD m_dwTime;
	DWORD m_dwIntervalTime;

};

