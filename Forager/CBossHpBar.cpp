#include "pch.h"
#include "CBossHpBar.h"
#include "CManager.h"

CBossHpBar::CBossHpBar() :m_dwTime(0)
{
    m_fHp = 0.f;
    m_fFullHp = 0.f;
    m_iWhiteBar = 0;
}

CBossHpBar::~CBossHpBar()
{
    Release();
}

void CBossHpBar::Initialize()
{
    m_tInfo.fCX = 600.f;
    m_tInfo.fCY = 24.f;
    m_iWhiteBar = 600.f;

    m_tInfo.fX = 525.f;
    m_tInfo.fY = 550.f;
}

int CBossHpBar::Update()
{
    if (m_bDead) return UI_DEAD;

    __super::Update_Rect();
    return UI_NOEVENT;
}

void CBossHpBar::Late_Update()
{
    if ((float)m_iWhiteBar >= (m_tInfo.fCX * (m_fHp / m_fFullHp)) && m_dwTime + 40 < (DWORD)GetTickCount64())
    {
        m_dwTime = (DWORD)GetTickCount64();
        --m_iWhiteBar;
        if (m_iWhiteBar < 0) m_iWhiteBar = 0;
    }

    if (m_fHp <= 0) m_bDead = true;
}

void CBossHpBar::Render(HDC hDC)
{
    HDC	hMemDC = CManager::Bmp()->Find_Img(L"CommonHpBar");
   // int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
    //int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

    //°ËÁ¤ ¹è°æ
    GdiTransparentBlt(hDC,
        m_tRect.left, //+ iScrollX,
        m_tRect.top, //+ iScrollY,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        hMemDC,
        0,
        0,
        56,
        12,
        RGB(255, 0, 255));

    //Èò»ö
    GdiTransparentBlt(hDC,
        m_tRect.left,// + iScrollX,
        m_tRect.top,// + iScrollY ,
        m_iWhiteBar,
        (int)m_tInfo.fCY,
        hMemDC,
        56 * 1,
        0,
        56,
        12,
        RGB(255, 0, 255));

    //»¡°­
    hMemDC = CManager::Bmp()->Find_Img(L"Boss_hpBar");
    GdiTransparentBlt(hDC,
        m_tRect.left,// + iScrollX,
        m_tRect.top,// + iScrollY ,
        (int)(m_tInfo.fCX * (m_fHp / m_fFullHp)),
        (int)m_tInfo.fCY,
        hMemDC,
        0,
        0,
        40,
        10,
        RGB(255, 0, 255));


}

void CBossHpBar::Release()
{
}
