#pragma once
#include "CUI.h"
class CPlayerHpBar :  public CUI
{
public:
	CPlayerHpBar();
	~CPlayerHpBar();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

	void Move_Frame();
	void Motion_Change();

public:
	void Setting_Hp(float _fHp)
	{
		m_fFullHp = _fHp;
		m_fHp = _fHp;
		if (0 <= _fHp && _fHp <= 100) { m_iCurStep = 0; m_fStamina = _fHp; }
		else if (100 <= _fHp && _fHp <= 200) { m_iCurStep = 0; m_fStamina = _fHp - 100.f; }
		else if (200 <= _fHp && _fHp <= 300) { m_iCurStep = 0; m_fStamina = _fHp - 200.f; }

		
	}
	void DecreaseHp(float _fAttack) { m_fHp += _fAttack;  m_fStamina += _fAttack; }

private:
	float m_fHp;
	float m_fFullHp;

	int m_iCurStep;

	int m_iHpSizeX;
	int m_iHpSizeY;

	float m_fStamina;

};

