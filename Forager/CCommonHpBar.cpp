#include "pch.h"
#include "CCommonHpBar.h"
#include "CManager.h"

CCommonHpBar::CCommonHpBar() :m_dwTime(0)
{
	m_fHp= 0.f;
	m_fFullHp= 0.f;
    m_iWhiteBar = 0;
}

CCommonHpBar::~CCommonHpBar()
{
    Release();
}

void CCommonHpBar::Initialize()
{
	m_tInfo.fCX = 56.f;
	m_tInfo.fCY = 12.f;
    m_iWhiteBar = 56.f;

}

int CCommonHpBar::Update()
{
	if (m_bDead) return UI_DEAD;

    if (m_pTarget)
    {
        m_tInfo.fX = m_pTarget->fX;
        m_tInfo.fY = m_pTarget->fY;

    }

	__super::Update_Rect();
	return UI_NOEVENT;
}

void CCommonHpBar::Late_Update()
{
    if ((float)m_iWhiteBar >= (m_tInfo.fCX * (m_fHp / m_fFullHp)) && m_dwTime + 40 < (DWORD)GetTickCount64())
    {
        m_dwTime = (DWORD)GetTickCount64();
        --m_iWhiteBar;
        if (m_iWhiteBar <= 0) {
            m_iWhiteBar = 0;
             m_bDead = true;
        }
    }

   // if (m_fHp <= 0) m_bDead = true;
}

void CCommonHpBar::Render(HDC hDC)
{
    HDC	hMemDC = CManager::Bmp()->Find_Img(L"CommonHpBar");
    int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
    int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

    //°ËÁ¤ ¹è°æ
    GdiTransparentBlt(hDC,
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY + 40,
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
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY + 40,
        m_iWhiteBar,
        (int)m_tInfo.fCY,
        hMemDC,
        56 * 1,
        0,
        56,
       12,
        RGB(255, 0, 255));

    //»¡°­
    GdiTransparentBlt(hDC,
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY + 40,
        (int)(m_tInfo.fCX  * (m_fHp / m_fFullHp)),
        (int)m_tInfo.fCY,
        hMemDC,
        56 * 2,
        0,
        56,
        12,
        RGB(255, 0, 255));


}

void CCommonHpBar::Release()
{
}
