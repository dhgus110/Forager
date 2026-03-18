#include "pch.h"
#include "CFurnace.h"
#include "CManager.h"
#include "CAbstractFactory.h"
#include "CDropItem.h"
#include "CSoundMgr.h"
#include "CSoundMgr.h"
CFurnace::CFurnace() :m_ePreProduction(CFurnace::END), m_eCurProduction(CFurnace::END), m_dwProductTime(0)
{
    m_iProductCnt = 0;
    m_eProductID = IT_END;
    m_dwPreventTime = 0;
    m_bPossibleProduct = true;
    ZeroMemory(&m_tEffectFrame, sizeof(FRAME));
}

CFurnace::~CFurnace()
{
	Release();

}

void CFurnace::Initialize()
{
    m_tInfo.fCX = 112.f;
    m_tInfo.fCY = 112.f;

    m_eId = SI_I_0;
    m_iRepeatBuildingCnt = 3;
    m_pFrameKey = L"Ani_SI_I_0";
    m_tFrame = { 0, 2, 0, 150, (DWORD)GetTickCount64() };

    m_tEffectFrame = { 0,39,0,200,(DWORD)GetTickCount64() };

    Change_Ground();


    CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
    CSoundMgr::Get_Instance()->PlaySound(L"Craft_Furnace.wav", SOUND_EFFECT, 0.7f);

}

int CFurnace::Update()
{
    CBuilding::Move_Frame();
    Prevent_Time();
    Production();

    __super::Update_Rect();
    return OBJ_NOEVENT;
}

void CFurnace::Late_Update()
{
    Motion_Change();
    Move_Effect_Frame();

}

void CFurnace::Render(HDC hDC)
{
    int	iScrollX = (int)CManager::Scroll()->Get_ScrollX();
    int	iScrollY = (int)CManager::Scroll()->Get_ScrollY();

    HDC	hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);

	GdiTransparentBlt(hDC,
        (int)m_tRect.left + iScrollX,
        (int)m_tRect.top + iScrollY,
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMemDC,
		56 * m_tFrame.iStart,
		56 * m_tFrame.iMotion,
		56,
		56,
		RGB(255, 0, 255));

    if (m_eCurProduction == CFurnace::PRODUCTION)
    {

        hMemDC = CManager::Bmp()->Find_Img(L"Effect_Furnace_Smoke");

        GdiTransparentBlt(hDC,
            (int)m_tRect.left + iScrollX + 40,
            (int)m_tRect.top + iScrollY - 224,
            116,
            224,
            hMemDC,
            116 * m_tEffectFrame.iStart,
            224 * m_tEffectFrame.iMotion,
            116,
            224,
            RGB(255, 0, 255));


    }
    View_Interaction(hDC, true);
}

void CFurnace::Release()
{
}

void CFurnace::Motion_Change()
{
    if (m_iRepeatBuildingCnt == 0 && m_ePreProduction == CFurnace::END && m_eCurProduction == CFurnace::END)
    {
        m_eCurProduction = CFurnace::IDLE;
    }

    if (m_eCurProduction != m_ePreProduction) {
        switch (m_eCurProduction)
        {
        case CFurnace::IDLE:
            m_pFrameKey = L"SI_I_0";
            m_tFrame = { 0, 0, 0, 1'000'000'000 , (DWORD)GetTickCount64() };
            break;
        case CFurnace::PRODUCTION:
            m_pFrameKey = L"Pruduction_SI_I_0";
            m_tFrame = { 0, 12, 0, 150, (DWORD)GetTickCount64() };
            break;
        }

        m_ePreProduction = m_eCurProduction;
    }
}

void CFurnace::Check_Production(ITEMID _id)
{
    //처음제작 또는 같은거 제작중이거나
    if (m_bPossibleProduct &&(m_eProductID == IT_END || m_eProductID == _id))
    {
        //여러번 눌리는거 방지
        m_dwPreventTime = (DWORD)GetTickCount64();
        m_bPossibleProduct = false;


        //아이템 수량 다 가지고 있나 확인 및 수량 충분한지 검사하는 변수
        const int* iArr = eunmTointArr_Furnace_ItemCost(static_cast<int>(_id));
        bool bCheck = false; 

        //수량 부족하면 return
        for (size_t i = 0; i < IT_END; ++i)
        {
            if (iArr[i] > 0)
            {
                if (CManager::User()->Get_Item(i).second < iArr[i])
                    return;
            }

        }

        //충분하면 아이템 뺴주기
        for (size_t i = 0; i < IT_END; ++i)
        {
            if (iArr[i] > 0)
            {
                CManager::User()->Set_Item(static_cast<ITEMID>(i), -iArr[i]);
            }

        }

 

        //처음 만들 떄만 현재 시간 주기. 수량 여러개 일땐 다른곳에서 관리할거임
        if (m_iProductCnt == 0)
            m_dwProductTime = (DWORD)GetTickCount64();

        m_eProductID = _id;
        ++m_iProductCnt;
        m_eCurProduction = CFurnace::PRODUCTION;       //제작 ㄱㄱ


    }

}

void CFurnace::Change_Ground()
{
    int gridX = m_tInfo.fX  / TILECX;
    int gridY = (m_tInfo.fY - TILECY)/ TILECY;

    int	iIndex = gridY * TILEX + gridX - 1;
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + 1])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY])->Set_Option(3);
    dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY + 1])->Set_Option(3);

}

void CFurnace::Prevent_Time()
{
    if (m_bPossibleProduct) return;

    if (m_dwPreventTime + 300 < (DWORD)GetTickCount64())
    {
        m_bPossibleProduct = true;
    }
}

void CFurnace::Production()
{
    if (m_eCurProduction != CFurnace::PRODUCTION) return;

    if (m_dwProductTime + 7000 < (DWORD)GetTickCount64())
    {
        --m_iProductCnt;
        
        //드롭아이템 만들기
        CObj* pObj = CAbstractFactory<CDropItem>::Create(m_tInfo.fX, m_tInfo.fY);
        CManager::Obj()->Add_Object(OBJ_DROPITEM, pObj);
        dynamic_cast<CDropItem*>(pObj)->Drop_Furnance(m_eProductID);


        //끝
        if (m_iProductCnt == 0)
        {
            m_bPossibleProduct = true;
            m_eCurProduction = CFurnace::IDLE;
            m_eProductID = IT_END;
        }

        //아직 더 남아 있음 
        else
        {
            m_dwProductTime = (DWORD)GetTickCount64();
        }
    }
        
}


void CFurnace::Move_Effect_Frame()
{
    if (m_tEffectFrame.dwTime + m_tEffectFrame.dwSpeed < (DWORD)GetTickCount64())
    {
        ++m_tEffectFrame.iStart;

        if (m_tEffectFrame.iStart > m_tEffectFrame.iEnd)
        {
            m_tEffectFrame.iStart = 0;
        }

        m_tEffectFrame.dwTime = (DWORD)GetTickCount64();

    }
}
