#pragma once
#include "CUI.h"
class CConstructTooltip : public CUI
{
public:
    CConstructTooltip();
    ~CConstructTooltip();

public:
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

public:
    const STRUCTURE_ITEM_ID Get_BuildingID() const { return m_eID; }
    const bool Get_Active() const { return m_bActive; }

public:
    void Set_Building(STRUCTURE_ITEM_ID _id);
    void Reset() { m_bActive = false; m_eID = SI_END; }
    void ResetTimer() { m_bActive = false; m_eID = SI_END; m_dwTime = (DWORD)GetTickCount64(); m_bTimer = true; } // 잠깐동안 활성화 못하도록


private:
    //구현 안한 건물들은 건설탭에서 툴팁 안보이게
    bool NoShow();
    //잠깐 안보이게하는 타이머
    void Timer();

private:
    bool m_bActive;          // 툴팁이 활성화되었는지 여부
    bool m_bTimer;
    STRUCTURE_ITEM_ID m_eID; // 현재 선택된 건물 ID

    DWORD m_dwTime;
};

