#pragma once
#include "CUI.h"
#include "CSoundMgr.h"
class CItemToolTip : public CUI
{
public:
	CItemToolTip();
	~CItemToolTip();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:	
	//콜리전 한 곳에만 부르고 있어서 일단 여기로 Set_IntervalUseBtn 이것을 통합함
	const ITEMID Get_ItemID() { m_bIntervalUseBtn = true, m_dwTime = (DWORD)GetTickCount64(); return m_eSelect; }
	const bool Get_UseBtn() const { return m_bUseBtn; }
	const bool Get_CheckUseBtn() const { return m_bIntervalUseBtn; } //한번만 눌릴려고

public:

	void Set_ItemID(ITEMID _id) {
		if (m_eSelect != _id)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_MENU);
			CSoundMgr::Get_Instance()->PlaySound(L"item_Pick.wav", SOUND_MENU, 0.5f);
		}
		m_eSelect = _id;
	}
	//void Set_IntervalUseBtn() { m_bIntervalUseBtn = true, m_dwTime = (DWORD)GetTickCount64(); }

private:
	void CheckUseBtn();
	void Update_UseBtnInterval();

private:
	ITEMID m_eSelect;
	bool m_bUseBtn;
	bool m_bIntervalUseBtn;
	DWORD m_dwTime;
};

