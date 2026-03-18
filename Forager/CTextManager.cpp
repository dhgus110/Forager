#include "pch.h"
#include "CTextManager.h"

CTextManager* CTextManager::m_pInstance = nullptr;

CTextManager::CTextManager()
{
}

CTextManager::~CTextManager()
{
    Release();
}

void CTextManager::Initialize()
{
    Register_ItemTexts();
    Register_ConstructTexts();
    Register_UITexts();
}

void CTextManager::Release()
{
    m_TextMap.clear();
}

void CTextManager::Register_ItemTexts()
{
    // 아이템 설명 등록
    m_TextMap[TID_ITEM_BERRY] = L"베리: 먹으면 배고픔을 조금 회복합니다. 숲에서 자라는 야생 열매입니다.";
    m_TextMap[TID_ITEM_COAL] = L"석탄: 제련소에서 사용되는 연료입니다. 요리하거나 광석을 만듭니다.";
    m_TextMap[TID_ITEM_GOLD] = L"금광석: 귀중한 광물입니다. 제련소에서 금괴로 가공할 수 있습니다.";
    m_TextMap[TID_ITEM_IRON] = L"철광석: 다양한 장비 제작에 필요한 기본 재료입니다. 광산에서 채취할 수 있습니다.";
    m_TextMap[TID_ITEM_STONE] = L"돌: 건물이나 구조물을 만드는 데 사용되는 기본 재료입니다.";
    m_TextMap[TID_ITEM_WOOD] = L"나무: 여러 가지 건물이나 도구를 만드는 데 사용되는 기본 재료입니다.";
    m_TextMap[TID_ITEM_SAND] = L"모래: 유리나 벽돌을 만드는 데 사용됩니다. 해변에서 채취할 수 있습니다.";
    m_TextMap[TID_ITEM_SMELT_GOLD] = L"금괴: 제련된 순수한 금입니다. 고급 장비나 건물 제작에 사용됩니다.";
    m_TextMap[TID_ITEM_SMELT_IRON] = L"철: 제련된 순수한 철입니다. 다양한 장비 제작에 사용됩니다.";
    m_TextMap[TID_ITEM_BRICK] = L"벽돌: 견고한 건물을 만드는 데 사용됩니다. 모래와 돌을 조합하여 만들 수 있습니다.";
    m_TextMap[TID_ITEM_CITRUS] = L"감귤: 건강에 좋은 과일입니다. 에너지를 많이 회복시켜 줍니다.";
    m_TextMap[TID_ITEM_FISH] = L"생선: 바다에서 잡을 수 있는 음식입니다. 조리하면 더 많은 에너지를 회복할 수 있습니다.";
    m_TextMap[TID_ITEM_COOK_FISH] = L"구운 생선: 조리된 생선입니다. 에너지를 많이 회복시켜 줍니다.";
}



void CTextManager::Register_ConstructTexts()
{
    m_TextMap[TID_SI_I_0] = L"견고한 재료들을 녹일 정도로 강력한 불을 만들어냅니다.";
    m_TextMap[TID_SI_I_1] = L"강력한 무기를 제작합니다.";
    m_TextMap[TID_SI_I_2] = L"모든 모험가에게 유용한 장신구나 의상을 제작합니다.";

    m_TextMap[TID_SI_F_0] = L"지나갈 수 있는 나무 바닥을 만듭니다!";
    m_TextMap[TID_SI_F_1] = L"자동으로 물고기를 수집합니다.";

    m_TextMap[TID_SI_E_0] = L"자동으로 무료 동전을 만들어냅니다.";
    m_TextMap[TID_SI_E_1] = L"자동으로 세금을 걷습니다";
    m_TextMap[TID_SI_E_2] = L"자동으로 이자를 만들어냅니다.";
    m_TextMap[TID_SI_E_3] = L"자동으로 바다에서 보물을 찾습니다.";
    m_TextMap[TID_SI_E_4] = L"가끔 많은 돈이 나옵니다.";

}

void CTextManager::Register_UITexts()
{
    m_TextMap[TID_UI_WELCOME] = L"포레이저에 오신 것을 환영합니다!";
    m_TextMap[TID_UI_HELP] = L"WASD로 이동, 마우스 좌클릭으로 상호작용할 수 있습니다.";

}

const TCHAR* CTextManager::Get_Text(TEXT_ID textID)
{
    auto it = m_TextMap.find(textID);
    if (it != m_TextMap.end())
        return it->second.c_str();

    return L"텍스트를 찾을 수 없습니다.";
}

const TCHAR* CTextManager::Get_ItemText(ITEMID itemID)
{
    // 아이템 ID를 텍스트 ID로 변환
    TEXT_ID textID = static_cast<TEXT_ID>(TID_ITEM_BERRY + itemID);
    return Get_Text(textID);
}

const TCHAR* CTextManager::Get_ConstructText(STRUCTURE_ITEM_ID structureID)
{
    TEXT_ID textID = static_cast<TEXT_ID>(TID_SI_I_0 + structureID);

    return Get_Text(textID);
}

void CTextManager::Set_Text(TEXT_ID textID, const TCHAR* text)
{
    m_TextMap[textID] = text;
}