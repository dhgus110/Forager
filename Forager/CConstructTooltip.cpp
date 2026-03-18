#include "pch.h"
#include "CConstructTooltip.h"
#include "CManager.h"
#include "CTextRender.h"



CConstructTooltip::CConstructTooltip()
{
    m_bTimer = false;
    m_bActive = false;
    m_eID = SI_END;
    m_dwTime = 0;
}

CConstructTooltip::~CConstructTooltip()
{
    Release();
}

void CConstructTooltip::Initialize()
{
    m_tInfo.fX = 500.f;
    m_tInfo.fY = 120.f;
    m_tInfo.fCX = 250.f;
    m_tInfo.fCY = 300.f;
}

int CConstructTooltip::Update()
{
    if (!m_bActive || NoShow())
        return UI_NOEVENT;

    __super::Update_Rect();
    return UI_NOEVENT;
}

void CConstructTooltip::Late_Update()
{
    Timer();
}

void CConstructTooltip::Render(HDC hDC)
{
    if (!m_bActive ||NoShow() )
        return;

    // 툴팁 배경
    HDC hMemDC = CManager::Bmp()->Find_Img(L"Trade_Base");
    GdiTransparentBlt(hDC,
        (int)m_tInfo.fX,
        (int)m_tInfo.fY,
        250,
        300,
        hMemDC,
        0,
        0,
        200,
        100,
        RGB(255, 0, 255));


    // 필요 자재 타이틀
    TEXT_STYLE titleStyle(RGB(255, 255, 255), 25, DT_LEFT);
    CTextRender::Render_Text(hDC, L"필요 자재", (int)m_tInfo.fX + 10, (int)m_tInfo.fY + 10, titleStyle);

    // 필요한 자재 목록 표시
    const int* iArr = eunmTointArr_BuildingCost(static_cast<int>(m_eID));
    int iRequestCnt = 0;
    for (size_t i = 0; i < IT_END; ++i)
    {
        if (iArr[i] > 0)
        {
            // 필요한 아이템 아이콘
            hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Item(i));
            GdiTransparentBlt(hDC,
                (int)m_tInfo.fX + 10,
                (int)m_tInfo.fY + 40 + 45 * iRequestCnt,
                40,
                40,
                hMemDC,
                0,
                0,
                56,
                56,
                RGB(255, 0, 255));

            // 아이템 이름
            TEXT_STYLE itemStyle(RGB(255, 255, 255), 26, DT_LEFT);
            CTextRender::Render_Text(hDC, enumTotchar_Item_Kr(i),
                (int)m_tInfo.fX + 50, (int)m_tInfo.fY + 40 + 45 * iRequestCnt, itemStyle);

            // 내가 가지고 있는 수량
            float fTemp(0.f);
            int myItemCnt = CManager::User()->Get_Item(static_cast<ITEMID>(i)).second;

            // 수량이 부족하면 흰색, 충분하면 노란색으로 표시
            bool isEnough = (myItemCnt >= iArr[i]);
            CManager::UI()->NumberRender(
                myItemCnt,
                14, 24,
                (int)m_tInfo.fX + 130, (int)m_tInfo.fY + 40 + 45 * iRequestCnt,
                &fTemp, false,
                hDC, isEnough
            );

            // 슬래시 표시
            hMemDC = CManager::Bmp()->Find_Img(L"Font_Slash");
            GdiTransparentBlt(hDC,
                int(fTemp),
                (int)m_tInfo.fY + 40 + 45 * iRequestCnt,
                14,
                24,
                hMemDC,
                0, 0,
                14,  20,
                RGB(255, 0, 255));

            // 필요한 수량
            CManager::UI()->NumberRender(
                iArr[i],
                14, 24,
                fTemp + 16, (int)m_tInfo.fY + 40 + 45 * iRequestCnt,
                &fTemp, false,
                hDC, false
            );

            iRequestCnt++;
        }
    }

    //설명 글 추가
    RECT descRect = { m_tInfo.fX + 20,m_tInfo.fY + 200, m_tInfo.fX + 230, m_tInfo.fY + 290 };
    TEXT_STYLE style(RGB(255, 255, 255), 20, DT_LEFT);
    CTextRender::Render_ConstructDescription(hDC, m_eID, descRect, style);
}

void CConstructTooltip::Release()
{
}

void CConstructTooltip::Set_Building(STRUCTURE_ITEM_ID _id)
{
    if (m_bTimer) return;
	m_eID = _id;
	m_bActive = true;
}

bool CConstructTooltip::NoShow()
{
    if (m_eID == SI_I_3 || m_eID == SI_I_4 ||
        m_eID == SI_F_2 || m_eID == SI_F_3 || m_eID == SI_F_4 ||
        m_eID >= SI_M_0)
        return true;
    return false;
}

void CConstructTooltip::Timer()
{
    if (!m_bTimer)return;
    if (m_dwTime + 1000 < (DWORD)GetTickCount64())
    {
        m_bTimer = false;
   }
}
