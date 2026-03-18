#pragma once
#include "CUI.h"
#include "Enum.h"
class CSkillButtons : public CUI
{
public:
	CSkillButtons();
	~CSkillButtons();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const SKILLID& Get_ID()const { return m_eID; }

public:
	void Setting(SKILLID _id);
	void Start_Effect() { m_bEffect = true; }

private:
	void Move_Frame();

private:
	SKILLID m_eID;
	const TCHAR* m_pFramekey;
	DWORD m_dwTime;
	int m_iMotion;
	int m_iEffectMotion;
	int m_iEffectTime;
	bool m_bEffect;
};

