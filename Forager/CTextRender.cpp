#include "pch.h"
#include "CTextRender.h"

void CTextRender::Render_Text(HDC hDC, const TCHAR* text, int x, int y, TEXT_STYLE style)
{
    // 폰트 생성
    HFONT hFont = CreateFont(
        style.fontSize,                    // 높이(크기)
        0,                                 // 너비
        0,                                 // 기울기 각도
        0,                                 // 베이스라인 각도
        style.isBold ? FW_BOLD : FW_NORMAL, // 폰트 두께
        style.isItalic,                    // 이탤릭
        style.isUnderline,                 // 밑줄
        FALSE,                             // 취소선
        DEFAULT_CHARSET,                   // 문자셋
        OUT_DEFAULT_PRECIS,                // 출력 정밀도
        CLIP_DEFAULT_PRECIS,               // 클리핑 정밀도
        DEFAULT_QUALITY,                   // 출력 품질
        DEFAULT_PITCH | FF_DONTCARE,       // 피치 및 패밀리
        L"맑은 고딕");                     // 폰트 이름

    // 기존 폰트 저장
    HFONT oldFont = (HFONT)SelectObject(hDC, hFont);

    // 텍스트 색상 설정
    SetTextColor(hDC, style.textColor);

    // 배경 모드 설정 (투명 또는 불투명)
    if (style.isTransparent) {
        SetBkMode(hDC, TRANSPARENT);
    }
    else {
        SetBkMode(hDC, OPAQUE);
        SetBkColor(hDC, style.bgColor);
    }


    // 배경 모드 설정 (투명)
    SetBkMode(hDC, TRANSPARENT);

    // 텍스트 출력
    TextOut(hDC, x, y, text, lstrlen(text));

    // 기존 폰트로 복원
    SelectObject(hDC, oldFont);

    // 생성한 폰트 삭제
    DeleteObject(hFont);

}

void CTextRender::Render_TextInRect(HDC hDC, const TCHAR* text, RECT rect, TEXT_STYLE style)
{
    // 폰트 생성
    HFONT hFont = CreateFont(
        style.fontSize, 0, 0, 0,
        style.isBold ? FW_BOLD : FW_NORMAL,
        style.isItalic, style.isUnderline, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"맑은 고딕");

    HFONT oldFont = (HFONT)SelectObject(hDC, hFont);
    SetTextColor(hDC, style.textColor);
    SetBkMode(hDC, TRANSPARENT);

    // 텍스트 출력 (자동 줄바꿈)
    UINT format = style.align | DT_WORDBREAK;
    DrawText(hDC, text, -1, &rect, format);

    SelectObject(hDC, oldFont);
    DeleteObject(hFont);
}

void CTextRender::Render_ItemDescription(HDC hDC, ITEMID itemID, RECT rect, TEXT_STYLE style)
{
    const TCHAR* text = CTextManager::Get_Instance()->Get_ItemText(itemID);
    Render_TextInRect(hDC, text, rect, style);
}

void CTextRender::Render_ConstructDescription(HDC hDC, STRUCTURE_ITEM_ID structureID, RECT rect, TEXT_STYLE style)
{
    const TCHAR* text = CTextManager::Get_Instance()->Get_ConstructText(structureID);
    Render_TextInRect(hDC, text, rect, style);
}
