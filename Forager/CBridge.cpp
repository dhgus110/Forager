#include "pch.h"
#include "CBridge.h"
#include "CManager.h"
#include "CSoundMgr.h"

CBridge::CBridge()
{
}

CBridge::~CBridge()
{
    Release();
}

void CBridge::Initialize()
{
    m_tInfo.fCX = 56.f;
    m_tInfo.fCY = 56.f;

    m_eId = SI_F_0;
    m_iRepeatBuildingCnt = 3;
    m_pFrameKey = L"Ani_SI_F_0";
    m_tFrame = { 0, 3, 0,200, (DWORD)GetTickCount64() };

    Change_Ground();


    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
    CSoundMgr::Get_Instance()->PlaySound(L"Craft_Accept.wav", SOUND_EFFECT, 0.7f);

}

int CBridge::Update()
{
    CBuilding::Move_Frame();

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CBridge::Late_Update()
{
}

void CBridge::Render(HDC hDC)
{
    int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
    int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

    HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);

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

void CBridge::Release()
{
}

void CBridge::Change_Ground()
{
    int gridX = m_tInfo.fX / TILECX;
    int gridY = m_tInfo.fY / TILECY;

    int	iIndex = gridY * TILEY + gridX;
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Set_Option(0);

}
