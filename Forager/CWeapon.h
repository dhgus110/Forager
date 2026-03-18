#pragma once
#include "CObj.h"
class CWeapon : public CObj
{
public:
	enum STATE {IDLE, SWING, END};

public:
	CWeapon();
	~CWeapon();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Set_Swing() { m_eState = SWING; }
	void Set_SwingSpeed(DWORD _dw) { m_dwSwingSpeed = _dw; }  //x
	void Set_TargetResource(CObj* pObj) { pTargetResource = pObj; }
	void Set_TargetMonster(CObj* pObj)
	{
		pTargetMonster = pObj; 
	}

public:
	void Weapon_Change();


private:
	void	Follow_Player();
	void	Swing_One_Frame();
	void	Motion_Change();
	void	Look_Cursor();

private:
	DWORD m_dwSwingSpeed;

	STATE m_eState;
	STATE m_ePreState;

	const TCHAR* m_pFrameKey; 
	FRAME		 m_tFrame;

	CObj* pTargetResource;
	CObj* pTargetMonster;

	float m_fAttackDamage;

};

