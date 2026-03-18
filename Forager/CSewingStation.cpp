#include "pch.h"
#include "CSewingStation.h"
#include "CManager.h"
#include "CSoundMgr.h"
CSewingStation::CSewingStation()
{
}

CSewingStation::~CSewingStation()
{
	Release();

}

void CSewingStation::Initialize()
{
    m_tInfo.fCX = 80.f;
    m_tInfo.fCY = 112.f;

    m_eId = SI_I_2;
    m_iRepeatBuildingCnt = 3;
    m_pFrameKey = L"Ani_SI_I_2";
    m_tFrame = { 0, 2, 0, 150, (DWORD)GetTickCount64() };
    Change_Ground();


    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
    CSoundMgr::Get_Instance()->PlaySound(L"Craft_Furnace.wav", SOUND_EFFECT, 0.7f);

}

int CSewingStation::Update()
{
    CBuilding::Move_Frame();

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CSewingStation::Late_Update()
{
}

void CSewingStation::Render(HDC hDC)
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

    View_Interaction(hDC, true);


}

void CSewingStation::Release()
{
}

void CSewingStation::Change_Ground()
{
    int gridX = m_tInfo.fX / TILECX;
    int gridY = (m_tInfo.fY - TILECY) / TILECY;

    int	iIndex = gridY * TILEX + gridX - 1;
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + 1])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY + 1])->Set_Option(3);

}
