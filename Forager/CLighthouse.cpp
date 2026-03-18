#include "pch.h"
#include "CLighthouse.h"
#include "CTile.h"
#include "CManager.h"

CLighthouse::CLighthouse() :m_dwIncomeTime((DWORD)GetTickCount64()), m_iIncome(0), m_bIncome(false), m_dwCoinRenderLifeTime(0), m_fRaise(0.f)
{
}

CLighthouse::~CLighthouse()
{
    Release();

}

void CLighthouse::Initialize()
{
    m_tInfo.fCX = 160.f;
    m_tInfo.fCY = 190.f;

    m_iIncome = 2000;
    m_fRaise = 1.0f;

    m_eId = SI_E_3;
    m_iRepeatBuildingCnt = 3;
    m_pFrameKey = L"Ani_SI_E_3";
    m_tFrame = { 0, 2, 0, 150, (DWORD)GetTickCount64() };
    Change_Ground();

    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
    CSoundMgr::Get_Instance()->PlaySound(L"Craft_Building.wav", SOUND_EFFECT, 0.7f);

}

int CLighthouse::Update()
{
    CBuilding::Move_Frame();

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CLighthouse::Late_Update()
{
    Income();
    Coin_LifeCycle();
}

void CLighthouse::Render(HDC hDC)
{
    int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
    int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

    HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);

    // 건설 애니메이션
    if (m_iRepeatBuildingCnt > 0) {
        GdiTransparentBlt(hDC,
            m_tRect.left + iScrollX,
            m_tRect.top + iScrollY,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            hMemDC,
            56 * m_tFrame.iStart,
            56 * m_tFrame.iMotion,
            56,
            56,
            RGB(255, 0, 255));
    }
    // 모습 유지
    else if (m_iRepeatBuildingCnt == 0) {
        GdiTransparentBlt(hDC,
            m_tRect.left + iScrollX,
            m_tRect.top + iScrollY,
            (int)m_tInfo.fCX,
            (int)m_tInfo.fCY,
            hMemDC,
            112,
            0,
            56,
            56,
            RGB(255, 0, 255));
    }

    Render_Coin(hDC);

}

void CLighthouse::Release()
{
}

void CLighthouse::Change_Ground()
{
    int gridX = m_tInfo.fX / TILECX;
    int gridY = m_tInfo.fY  / TILECY;

    int	iIndex = gridY * TILEX + gridX - 1;

    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + 1])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY + 1])->Set_Option(3);

}



void CLighthouse::Income()
{
    if (m_dwIncomeTime + 10'000 < (DWORD)GetTickCount64()) {
        m_dwIncomeTime = (DWORD)GetTickCount64();

        CManager::User()->Set_Coin(m_iIncome);
        m_dwCoinRenderLifeTime = (DWORD)GetTickCount64();
        m_bIncome = true;
        m_fRaise = 1.f;
    }
}

void CLighthouse::Render_Coin(HDC hDC)
{
    if (!m_bIncome) return;

    float fTemp(0.f);
    m_fRaise *= 1.035f;
    CManager::UI()->NumberRender(m_iIncome, 20, 40, m_tInfo.fX - 30.f, m_tInfo.fY - 80.f - m_fRaise, &fTemp, true, hDC, true);
}

void CLighthouse::Coin_LifeCycle()
{
    if (!m_bIncome) return;
    if (m_dwCoinRenderLifeTime + 2000 < (DWORD)GetTickCount64())
    {
        m_bIncome = false;
    }
}