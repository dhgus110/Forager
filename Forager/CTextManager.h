#pragma once
#include "pch.h"
#include <map>
#include <string>
#include <vector>
#include "Enum.h"

enum TEXT_ID {
    // 아이템 설명
    TID_ITEM_BERRY = 0,
    TID_ITEM_COAL,
    TID_ITEM_GOLD,
    TID_ITEM_IRON,
    TID_ITEM_STONE,
    TID_ITEM_WOOD,
    TID_ITEM_SAND,
    TID_ITEM_SMELT_GOLD,
    TID_ITEM_SMELT_IRON,
    TID_ITEM_BRICK,
    TID_ITEM_CITRUS,
    TID_ITEM_FISH,
    TID_ITEM_COOK_FISH,

    // 스킬 설명
    TID_SKILL_START = 1000,
    // ... 스킬 ID 추가

    //건설 메뉴
    TID_SI_START = 2000,
    TID_SI_I_0,
    TID_SI_I_1,
    TID_SI_I_2,
    TID_SI_I_3,
    TID_SI_I_4,    
    TID_SI_F_0,
    TID_SI_F_1,
    TID_SI_F_2,
    TID_SI_F_3,
    TID_SI_F_4,
    TID_SI_E_0,
    TID_SI_E_1,
    TID_SI_E_2,
    TID_SI_E_3,
    TID_SI_E_4,
    TID_SI_M_0,
    TID_SI_M_1,
    TID_SI_M_2,
    TID_SI_M_3,
    TID_SI_M_4,

    // UI 텍스트
    TID_UI_START = 3000,
    TID_UI_WELCOME,
    TID_UI_HELP,
    // ... UI 텍스트 추가


};

// 텍스트 스타일 구조체
struct TEXT_STYLE {
    COLORREF textColor;     // 텍스트 색상
    COLORREF bgColor;       // 배경 색상 
    int fontSize;           // 폰트 크기
    bool isBold;            // 굵게
    bool isItalic;          // 기울임
    bool isUnderline;       // 밑줄
    UINT align;             // 정렬 (DT_LEFT, DT_CENTER, DT_RIGHT)
    bool isTransparent;     // 배경 투명 여부

    TEXT_STYLE() :
        textColor(RGB(255, 255, 255)),
        bgColor(RGB(0, 0, 0)),
        fontSize(16),
        isBold(false),
        isItalic(false),
        isUnderline(false),
        align(DT_LEFT) ,
        isTransparent(true) {}

    TEXT_STYLE(COLORREF _textColor, int _fontSize = 16, UINT _align = DT_LEFT) :
        textColor(_textColor),
        bgColor(RGB(0, 0, 0)),
        fontSize(_fontSize),
        isBold(false),
        isItalic(false),
        isUnderline(false),
        align(_align),
        isTransparent(true) {}
};

class CTextManager
{
private:
    CTextManager();
    CTextManager(const CTextManager& rhs) = delete;
    CTextManager& operator=(const CTextManager& rObj) = delete;
    ~CTextManager();

public:
    static CTextManager* Get_Instance() {
        if (!m_pInstance)
            m_pInstance = new CTextManager;
        return m_pInstance;
    }

    static void Destroy_Instance() {
        if (m_pInstance) {
            delete m_pInstance;
            m_pInstance = nullptr;
        }
    }

public:
    void Initialize();
    void Release();

    // 텍스트 관련 함수
    const TCHAR* Get_Text(TEXT_ID textID);
    const TCHAR* Get_ItemText(ITEMID itemID);
    const TCHAR* Get_ConstructText(STRUCTURE_ITEM_ID structureID);

    // 텍스트 추가 및 수정
    void Set_Text(TEXT_ID textID, const TCHAR* text);

private:
    void Register_ItemTexts();
    void Register_ConstructTexts();
    void Register_UITexts();


private:
    static CTextManager* m_pInstance;
    map<TEXT_ID, wstring> m_TextMap; //텍스트 저장
};