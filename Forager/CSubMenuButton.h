#pragma once
#include "CUI.h"
#include "CSoundMgr.h"
class CSubMenuButton :  public CUI
{
public:
	CSubMenuButton();
	~CSubMenuButton();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const int Get_CurMenu() const { return m_iCurMenu; }

public:
	void Set_Inactive(int _i) { m_bInactive = true; m_iCursor = _i; }
	void Set_Inactive() { m_bInactive = false; }
	void Set_Active(int _i) {
		if (m_iCurMenu != _i)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_MENU);
			CSoundMgr::Get_Instance()->PlaySound(L"Menu_Open.wav", SOUND_MENU, 0.7f);
		}

		m_iCurMenu = _i; }


public:
	void Inactive_Render(HDC hDC);
	void Reset() { m_bInactive = false; m_iCurMenu = 1; }

private:
	bool m_bInactive;

	//0: 장비
	//1: 아이템
	//2: 건설
	//3: 섬 구입
	//4: 설정
	int m_iCurMenu;
	int m_iCursor;

	const TCHAR* m_pFrameKey2;
};

