#include "pch.h"
#include "CFishTrap.h"
#include "CManager.h"
#include "CSoundMgr.h"

CFishTrap::CFishTrap() :m_dwTime(0), m_dwIntervalTime(0), m_bfishing(false)
{
}

CFishTrap::~CFishTrap()
{
    Release();
}

void CFishTrap::Initialize()
{
    m_tInfo.fCX = 56.f;
    m_tInfo.fCY = 56.f;

    m_eId = SI_F_1;
 
    m_pFrameKey = L"Ani_SI_F_1";
    m_tFrame = { 0, 2, 0,200, (DWORD)GetTickCount64() };

    m_dwTime = (DWORD)GetTickCount64()+2000;
    m_dwIntervalTime = 30000;

    Change_Ground();


    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
    CSoundMgr::Get_Instance()->PlaySound(L"Craft_Accept.wav", SOUND_EFFECT, 0.7f);

}

int CFishTrap::Update()
{
    Fishing();

    CBuilding::Move_Frame();

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CFishTrap::Late_Update()
{
}

void CFishTrap::Render(HDC hDC)
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

	if (m_bfishing)
	{
		hMemDC = CManager::Bmp()->Find_Img(L"Word_Chapture");

		GdiTransparentBlt(hDC,
			m_tRect.left + iScrollX - 6,
			m_tRect.top + iScrollY - 35,
			70,
			35,
			hMemDC,
			50 * m_tFrame.iStart,
			25 * m_tFrame.iMotion,
			50,
			25,
			RGB(255, 0, 255));
	}

    View_Interaction(hDC, true);

}

void CFishTrap::Release()
{
}

void CFishTrap::Fishing()
{
    if (m_bfishing)return;

    if (m_dwTime + m_dwIntervalTime < (DWORD)GetTickCount64())
    {
        m_bfishing = true;
    }
}

void CFishTrap::Change_Ground()
{
    int gridX = m_tInfo.fX / TILECX;
    int gridY = m_tInfo.fY / TILECY;

    int	iIndex = gridY * TILEY + gridX;
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Set_Option(3);
}

