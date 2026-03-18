#pragma once
#include "CUI.h"
class CCommonHpBar :public CUI
{
public:
	CCommonHpBar();
	~CCommonHpBar();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Setting_Hp(float _fHp) {m_fFullHp = _fHp; m_fHp = _fHp;}
	void DecreaseHp(float _fAttack) { m_fHp -= _fAttack; m_dwTime = (DWORD)GetTickCount64(); }

private:
	float m_fHp;
	float m_fFullHp;

	int	  m_iWhiteBar;
	DWORD m_dwTime;
};

