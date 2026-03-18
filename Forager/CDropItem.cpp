#include "pch.h"
#include "CDropItem.h"
#include "CManager.h"

/*
 아직 스프라이트 만들지 않은 것들
WOOD,
SAND,

SMELT_GOLD,
SMELT_IRON,
SMELT_WOOD,

FISH,
MEAT,
SEAWOOD,


COOK_FISH,
COOK_MEAT,
*/

CDropItem::CDropItem() : m_eId(IT_END), m_pFrameKey1(nullptr),
m_bJump(false), m_fRandomDropX(0.f), m_fJumpTime(0.f), m_fJumpSpeed(0.f), m_iCount(0), m_fRandJumpLimitTime(0.f),
m_bIsLand(false), m_dwTime(0)
{
    ZeroMemory(&m_tFrame, sizeof(FRAME));
}

CDropItem::~CDropItem()
{
    Release();
}

void CDropItem::Initialize()
{
    m_tInfo.fCX = static_cast<float>(BASE_SIZE);
    m_tInfo.fCY = static_cast<float>(BASE_SIZE);
    m_fJumpSpeed = 7.f;

    m_tFrame = { 0,17,0,25,(DWORD)GetTickCount64() };
    m_fRandomDropX = static_cast<float>(Random::GetInt(-20, 20));
    m_fRandJumpLimitTime = float(Random::GetInt(24, 26)) * 0.1f;
    m_dwTime = (DWORD)GetTickCount64();
}

int CDropItem::Update()
{
    if (m_bDead) return OBJ_DEAD;

    One_Jump();
    Move_Frame();

    if (!m_bIsLand && m_dwTime + 1100 < (DWORD)GetTickCount64()) m_bIsLand = true;

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CDropItem::Late_Update()
{
}

void CDropItem::Render(HDC hDC)
{
    HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey1);
    int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
    int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();


    GdiTransparentBlt(hDC,
        m_tRect.left + iScrollX,
        m_tRect.top + iScrollY,
        (int)m_tInfo.fCX - 20,
        (int)m_tInfo.fCY - 20,
        hMemDC,
        (int)m_tInfo.fCX * m_tFrame.iStart,
        (int)m_tInfo.fCY * m_tFrame.iMotion,
        (int)m_tInfo.fCX,
        (int)m_tInfo.fCY,
        RGB(255, 0, 255));
}

void CDropItem::Release()
{
}

void CDropItem::DropResourceItem(RESOURCEID _id, int _iOption)
{
    switch (_id)
    {
    case RE_BERRY:
        m_pFrameKey1 = L"Berry_Drop";
        m_eId = IT_BERRY;
        break;
    case RE_COAL:
        m_pFrameKey1 = L"Coal_Drop";
        m_eId = IT_COAL;
        break;
    case RE_GOLD:
        m_pFrameKey1 = L"Gold_Drop";
        m_eId = IT_GOLD;
        break;
    case RE_IRON:
        m_pFrameKey1 = L"Iron_Drop";
        m_eId = IT_IRON;
        break;
    case RE_STONE:
        m_pFrameKey1 = L"Stone_Drop";
        m_eId = IT_STONE;
        break;
    case RE_TREE:
        if(_iOption ==0){ m_pFrameKey1 = L"Wood_Drop";m_eId = IT_WOOD;}
        else if (_iOption == 1) { m_pFrameKey1 = L"Citrus_Drop";  m_eId = IT_CITRUS;  }
        break;
    }
    m_bJump = true;
   
}

void CDropItem::DropFishTrap()
{
    int iRand = Random::GetInt(0, 1);
    if (iRand == 0)
    {
        m_pFrameKey1 = L"Fish_Drop"; m_eId = IT_FISH;
    }
    else if (iRand == 1) 
    {
        m_pFrameKey1 = L"Sand_Drop"; m_eId = IT_SAND;

    }
    m_bJump = true;
}

void CDropItem::Drop_Furnance(ITEMID _id)
{
    switch (_id)
    {

    case IT_COAL:
        m_pFrameKey1 = L"Coal_Drop";
        m_eId = _id;
        break;
    case IT_SMELT_GOLD:
        m_pFrameKey1 = L"Smelt_Gold_Drop";
        m_eId = _id;
        break;
    case IT_SMELT_IRON:
        m_pFrameKey1 = L"Smelt_Iron_Drop";
        m_eId = _id;
        break;
    case IT_BRICK:
        m_pFrameKey1 = L"Brick_Drop";
        m_eId = _id;
        break;
    case IT_COOK_FISH:
        m_pFrameKey1 = L"Cook_Fish_Drop";
        m_eId = _id;
        break;
    }
    m_bJump = true;

}

void CDropItem::One_Jump()
{
    if (!m_bJump) return;

    if (m_fRandomDropX > 0) {
        if (m_tInfo.fX < m_tInfo.fX + m_fRandomDropX) m_tInfo.fX += 1.f;
    }
    else {
        if (m_tInfo.fX > m_tInfo.fX + m_fRandomDropX) m_tInfo.fX -= 1.f;
    }

    if(m_tInfo.fX )
    m_tInfo.fY -= (7.f * m_fJumpTime - 0.5f * 9.8f * m_fJumpTime * m_fJumpTime);
    m_fJumpTime += 0.15f;

    if (m_fJumpTime >= m_fRandJumpLimitTime)
    {
        m_bJump = false;
    }
}

void CDropItem::Move_Frame()
{
    if (m_tFrame.dwTime + m_tFrame.dwSpeed < (DWORD)GetTickCount64())
    {
        ++m_tFrame.iStart;

        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;

        m_tFrame.dwTime = (DWORD)GetTickCount64();

    }
}
