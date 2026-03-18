#include "pch.h"
#include "CPlayerHpBar.h"
#include "CManager.h"

CPlayerHpBar::CPlayerHpBar() : m_fHp(0.f), m_fFullHp(0.f), m_iCurStep(0), m_fStamina(0.f)
{
    m_iHpSizeX = 0;
    m_iHpSizeY = 0;
}

CPlayerHpBar::~CPlayerHpBar()
{
    Release();
}

void CPlayerHpBar::Initialize()
{
    m_tFrame = { 0, 3, 0, 200, (DWORD)GetTickCount64() };

    m_iHpSizeX = 126; 
    m_iHpSizeY = 38;

}

int CPlayerHpBar::Update()
{
   if(m_bDead) return UI_DEAD;


    return UI_NOEVENT;
}

void CPlayerHpBar::Late_Update()
{
    Move_Frame();
    Motion_Change();

}

void CPlayerHpBar::Render(HDC hDC)
{
    HDC	hMemDC = CManager::Bmp()->Find_Img(L"Player_Hp");

    GdiTransparentBlt(hDC,
        20 ,
        10 ,
        m_iHpSizeX,
        m_iHpSizeY,
        hMemDC,
        m_iHpSizeX * m_tFrame.iStart,
        m_iHpSizeY * m_tFrame.iMotion,
        m_iHpSizeX,
        m_iHpSizeY,
        RGB(255, 0, 255));

    hMemDC = CManager::Bmp()->Find_Img(L"Player_Stamina_Back");

    GdiTransparentBlt(hDC,
        20 ,
        55 ,
        84,
        26,
        hMemDC,
        0 ,
        0 ,
        74,
        26,
        RGB(255, 0, 255));

    hMemDC = CManager::Bmp()->Find_Img(L"Player_Stamina");

    GdiTransparentBlt(hDC,
        21 ,
        56 ,
        int(82.f * (m_fStamina * 0.01f)),
        24,
        hMemDC,
        0,
        0,
        63,
        16,
        RGB(255, 0, 255));

}

void CPlayerHpBar::Release()
{
}


void CPlayerHpBar::Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < (DWORD)GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = (DWORD)GetTickCount64();

    }
}

void CPlayerHpBar::Motion_Change()
{
    int iTemp = 0;
    if (0 <= m_fHp && m_fHp <= 100) iTemp = 0;
    else if (100 <= m_fHp && m_fHp <= 200) iTemp = 1;
    else if (200 <= m_fHp && m_fHp <= 300) iTemp = 2;

    if (m_iCurStep != iTemp) {
        if (iTemp == 0) m_tFrame.iMotion = 2;
        if (iTemp == 1) m_tFrame.iMotion = 1;
        if (iTemp == 2) m_tFrame.iMotion = 0;

        m_fStamina = m_fHp - float(iTemp * 100);

        m_iCurStep = iTemp;
    }
}
