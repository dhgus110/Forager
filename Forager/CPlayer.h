#pragma once
#include "pch.h"
#include "CObj.h"
#include "Enum.h"
#include "CPlayerHpBar.h"
#include "CManager.h"

class CPlayer : public CObj
{
public:
	CPlayer();
	~CPlayer();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const PLAYER_STATE& Get_State() const { return m_eState; }
	const int Get_CurIsland() const
	{
		return m_iCurIsland;
	}
	const bool Get_IsAttack() const { return m_bIsAttack; }
	const float Get_AttackDamage() const { return m_fAttackDamage; }
	const float Get_Hp() const { return m_fHp; }

public:
	void Set_IsAttack(bool _b) { m_bIsAttack = _b; }
	void Set_Hp(float _f) {
		//체력 300 이상 넘어가는거 방지
		if (m_fHp + _f > 300.f)
		{
			dynamic_cast<CPlayerHpBar*>(CManager::UI()->Get_ObjectBack(UI_PLAYER_HP))->DecreaseHp(300.f - m_fHp);
			m_fHp = 300.f;
		}
		else {
			m_fHp += _f; 
			dynamic_cast<CPlayerHpBar*>(CManager::UI()->Get_ObjectBack(UI_PLAYER_HP))->DecreaseHp(_f);
		}

	}
	
	void Set_Damaged(float _f) {
		if (m_eState == PL_DAMAGED || m_bInvincible) return;

		m_bInvincible = true;
		m_dwInvincibleTime = (DWORD)GetTickCount64();

		m_fHp -= _f;
		dynamic_cast<CPlayerHpBar*>(CManager::UI()->Get_ObjectBack(UI_PLAYER_HP))->DecreaseHp(-_f);
		m_eState = PL_DAMAGED;
	}
	void Set_AttackDamage(float _f) { m_fAttackDamage = _f; }

private:
	void Look_Cursor();
	void Key_Input();
	void Update_Controller();
	void Update_Move();
	void Update_Attack();
	void Update_Damaged();
	void Update_Mine();
	void Update_Death();
	void Update_Invincible();

private:
	void	Move_Frame();
	void	Motion_Change();
	void	Offset();

private:
	bool m_bIsAttack;
	int m_iCurIsland; //몇 번째 섬에 있는지? 

	PLAYER_STATE m_eState;
	PLAYER_STATE m_ePreState;

	DIR	m_eDir;

	float m_fMoveSpeed;
	float m_fHp;
	float m_fSwingSpeed;  
	float m_fAttackDamage;

	const TCHAR* m_pFrameKey;
	FRAME		 m_tFrame;

	FRAME		m_tEffectFrame[5];
	UIPOS		m_tEffectsPos[5];// 해당 자리에 먼지 이펙트나옴

	DWORD m_dwInvincibleTime;
	bool m_bInvincible;
	DWORD m_dwStepSoundTime;

};

