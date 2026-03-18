#include "pch.h"
#include "CWordIsland.h"
#include "CManager.h"

CWordIsland::CWordIsland()
{
}

CWordIsland::~CWordIsland()
{
}

void CWordIsland::Initialize()
{
    m_tInfo.fCX = 150.f;
    m_tInfo.fCY = 50.f;
}

int CWordIsland::Update()
{
    return 0;
}

void CWordIsland::Late_Update()
{
}

void CWordIsland::Render(HDC hDC)
{

    HDC	hMemDC = CManager::Bmp()->Find_Img(L"Word_Island_Cnt");

    GdiTransparentBlt(hDC,
        static_cast<int>(m_tInfo.fX),
        static_cast<int>(m_tInfo.fY),
        static_cast<int>(m_tInfo.fCX),
        static_cast<int>(m_tInfo.fCY),
        hMemDC,
        0,
        0,
        80,
        20,
        RGB(255, 0, 255));

    float fTemp(0.f);
    CManager::UI()->NumberRender(CManager::User()->Get_OwnIslandCnt(), 20, 19, m_tInfo.fX + m_tInfo.fCX, m_tInfo.fY+20 , &fTemp, false, hDC, false);

    hMemDC = CManager::Bmp()->Find_Img(L"Font_Slash");
    GdiTransparentBlt(hDC,
        int(fTemp),
        static_cast<int>(m_tInfo.fY)+20,
        14,
        20,
        hMemDC,
        0,
        0,
        14,
        20,
        RGB(255, 0, 255));

    CManager::UI()->NumberRender(9, 20, 19, fTemp + 20.f, m_tInfo.fY + 20, &fTemp, false, hDC, false);

}

void CWordIsland::Release()
{
}
