#pragma once
#include "CBuilding.h"
class CLighthouse : public CBuilding
{
public:
	CLighthouse();
	~CLighthouse();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Change_Ground();
	void Income();
	void Render_Coin(HDC hDC);
	void Coin_LifeCycle();


private:
	bool m_bIncome;
	int m_iIncome;
	float m_fRaise;
	DWORD m_dwIncomeTime;
	DWORD m_dwCoinRenderLifeTime;

};

