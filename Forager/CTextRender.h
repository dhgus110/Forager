#pragma once
#include "pch.h"
#include "CTextManager.h"

class CTextRender
{
public:

    // 기본 텍스트 출력
    static void Render_Text(HDC hDC, const TCHAR* text, int x, int y, TEXT_STYLE style = TEXT_STYLE());

    // 지정된 영역 내에 텍스트 출력 (자동 줄바꿈)
    static void Render_TextInRect(HDC hDC, const TCHAR* text, RECT rect, TEXT_STYLE style = TEXT_STYLE());

    // 아이템 설명 출력
    static void Render_ItemDescription(HDC hDC, ITEMID itemID, RECT rect, TEXT_STYLE style = TEXT_STYLE());

    // 스킬 설명 출력
    static void Render_ConstructDescription(HDC hDC, STRUCTURE_ITEM_ID structureID, RECT rect,  TEXT_STYLE style = TEXT_STYLE());



    // 단락 텍스트 출력 (여러 줄)
    //static void Render_Paragraph(HDC hDC, const vector<wstring>& lines, int x, int y, int lineHeight, TEXT_STYLE style = TEXT_STYLE());
};



