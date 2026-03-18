#pragma once
#include "CObj.h"
#include "CUI.h"

class CBoss : public CObj
{
public:
	CBoss();
	~CBoss();

public:
	void Initialize() override;
	int  Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const bool Get_CheckAttack() const { return m_bAttack; }
	const int Get_AttackDamage() const { return m_iAttackDamage; }
	const CUI* Get_HpBar() const { return m_pHpBar; }
	const float Get_Hp() const { return m_fHp; }

public:
	void Set_Damaged(float _fDamage, float _fPlayerX);
	void Set_HpBar(CUI* pCUI) { m_pHpBar = pCUI; }

public:
	void Setting_Attack( float _fPlayerX, float _fPlayerY);


private:
	void	Move_Frame();
	void	Effect_Frame();
	void	Damaged_Frame();
	void	Motion_Change();

	void	Update_State();
	void	Update_Idle();
	void	Update_Attack_Jump();


private:
	bool m_bCheckDamagedAnimation; //
	bool m_bDeadAnimation;
	bool m_bAttackEffect;
	bool  m_bAttack;
	bool  m_bEnableAttack;
	DWORD m_dwTime;
	DWORD m_dwCheckAttackTime;

	float m_fTargetPosX;
	float m_fTargetPosY;

	int m_iImageSizeY;
	int m_iDamagedDir; //

	MONSTER_STATE m_eState;
	MONSTER_STATE m_ePreState;

	float m_fMoveSpeed;
	float m_fHp;
	float m_fAttackSpeed;
	int m_iAttackDamage;

	float m_fJumpTime;
	float m_fJumpSpeed;

	const TCHAR* m_pFrameKey;
	FRAME		 m_tFrame;
	FRAME		 m_tEffectFrame;
	FRAME		 m_tDamagedFrame; //


	CUI* m_pHpBar;

};
