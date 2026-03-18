#include "pch.h"
#include "CMarket.h"
#include "CManager.h"
#include "CSoundMgr.h"
#include "CSoundMgr.h"
CMarket::CMarket()
{
    m_bIncome = false;
    m_iIncome =0;
    m_fRaise =0.f;
    m_dwIncomeTime = (DWORD)GetTickCount64();
    m_dwCoinRenderLifeTime=0;
}

CMarket::~CMarket()
{
    Release();
}

void CMarket::Initialize()
{
    m_tInfo.fCX = 80.f;
    m_tInfo.fCY = 112.f;

    m_fRaise = 1.0f;

    m_eId = SI_E_1;
    m_iRepeatBuildingCnt = 3;
    m_pFrameKey = L"Ani_SI_E_1";
    m_tFrame = { 0, 2, 0, 150, (DWORD)GetTickCount64() };
    Change_Ground();


    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
    CSoundMgr::Get_Instance()->PlaySound(L"Craft_Building.wav", SOUND_EFFECT, 0.7f);


}

int CMarket::Update()
{
    CBuilding::Move_Frame();

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CMarket::Late_Update()
{
    Income();
    Coin_LifeCycle();
}

void CMarket::Render(HDC hDC)
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
   // View_Interaction(hDC, true);
    Render_Coin(hDC);
}

void CMarket::Release()
{
}

void CMarket::Change_Ground()
{
    int gridX = m_tInfo.fX / TILECX;
    int gridY = (m_tInfo.fY - TILECY) / TILECY;

    int	iIndex = gridY * TILEX + gridX - 1;
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + 1])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILECY])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILECY + 1])->Set_Option(3);

}

void CMarket::Income()
{
    if (m_dwIncomeTime + 10'000 < (DWORD)GetTickCount64()) {
        m_dwIncomeTime = (DWORD)GetTickCount64();
        m_iIncome = Random::GetInt(1000, 2000);

        CManager::User()->Set_Coin(m_iIncome);
        m_dwCoinRenderLifeTime = (DWORD)GetTickCount64();
        m_bIncome = true;
        m_fRaise = 1.f;
    }
}

void CMarket::Render_Coin(HDC hDC)
{
    if (!m_bIncome) return;

    float fTemp(0.f);
    m_fRaise *= 1.035f;
    CManager::UI()->NumberRender(m_iIncome, 20, 40, m_tInfo.fX - 30.f, m_tInfo.fY - 80.f - m_fRaise, &fTemp, true, hDC, true);
}

void CMarket::Coin_LifeCycle()
{
    if (!m_bIncome) return;
    if (m_dwCoinRenderLifeTime + 2000 < (DWORD)GetTickCount64())
    {
        m_bIncome = false;
    }
}