#include "pch.h"
#pragma comment(lib, "msimg32.lib")

#include "CBuildingPreview.h"
#include "CManager.h"
#include "CPlayer.h"
#include "CAbstractFactory.h"
#include "CFurnace.h"
#include "CForge.h"
#include "CSlotMachine.h"
#include "CLighthouse.h"
#include "CVault.h"
#include "CMarket.h"
#include "CBank.h"
#include "CFishTrap.h"
#include "CBridge.h"
#include "CSewingStation.h"

CBuildingPreview::CBuildingPreview() : m_iSizeXRate(0) , m_iSizeYRate(0), m_bBuild(false)
{
    m_bCanBuild = false;
    m_eId  = SI_END;
    m_dwTime = (DWORD)GetTickCount64();
   // ZeroMemory(&m_tScrollPos, sizeof(POINT));
    //ZeroMemory(&m_tbeginScrollPos, sizeof(POINT));


}

CBuildingPreview::~CBuildingPreview()
{
    Release();
}

void CBuildingPreview::Initialize()
{
    m_tInfo.fCX = 56.f;
    m_tInfo.fCY = 56.f;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);
   // m_tbeginScrollPos.x = pt.x;
    //m_tbeginScrollPos.y = pt.y;
}

int CBuildingPreview::Update()
{
    if (m_bDead)
        return UI_DEAD;

    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(g_hWnd, &pt);

    pt.x -= (int)CManager::Scroll()->Get_ScrollX();
    pt.y -= (int)CManager::Scroll()->Get_ScrollY();

    // 타일 그리드에 맞추기
    int gridX = int(pt.x / TILECX);   
    int gridY = int(pt.y / TILECY); 

    m_tInfo.fX = gridX * TILECX;
    m_tInfo.fY = gridY * TILECY;

    Update_Rect();

    // 건설 가능 여부 체크
    m_bCanBuild = CheckBuildable(gridX, gridY);

    return UI_NOEVENT;
}

void CBuildingPreview::Late_Update()
{
    //if (m_bDead)
    //    return;

    Update_Build();
}

void CBuildingPreview::Render(HDC hDC)
{
    if (m_eId == SI_END || m_pFrameKey == nullptr)
        return;

    // 원본 이미지 가져오기
    HDC hMemDC = CManager::Bmp()->Find_Img(m_pFrameKey);

    // 건설 가능 여부에 따라 다른 DC에 그림
    HDC hTempDC = CreateCompatibleDC(hDC);
    HBITMAP hTempBitmap = CreateCompatibleBitmap(hDC, (int)m_tInfo.fCX * m_iSizeXRate, (int)m_tInfo.fCY* m_iSizeYRate);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hTempDC, hTempBitmap);

    // 원본 이미지를 임시 DC에 복사 (마젠타 색상은 투명하게)
    GdiTransparentBlt(
        hTempDC,                // 대상 DC
        0, 0,                   
        (int)m_tInfo.fCX * m_iSizeXRate,      
        (int)m_tInfo.fCY * m_iSizeYRate,
        hMemDC,                 // 원본 DC
        0, 0,                   
        (int)m_tInfo.fCX,      
        (int)m_tInfo.fCY,       
        RGB(255, 0, 255)        
    );

    // 건설 가능 여부에 따라 색조 변경
    HDC hColorDC = CreateCompatibleDC(hDC);
    HBITMAP hColorBitmap = CreateCompatibleBitmap(hDC, (int)m_tInfo.fCX  * m_iSizeXRate, (int)m_tInfo.fCY  * m_iSizeYRate);
    HBITMAP hOldColorBitmap = (HBITMAP)SelectObject(hColorDC, hColorBitmap);

    // 색상 오버레이 준비
    RECT fillRect = { 0, 0, (int)m_tInfo.fCX  * m_iSizeXRate , (int)m_tInfo.fCY * m_iSizeYRate };
    HBRUSH hBrush = CreateSolidBrush(m_bCanBuild ? RGB(0, 255, 70) : RGB(255, 0, 0));
    FillRect(hColorDC, &fillRect, hBrush);
    DeleteObject(hBrush);

    // 최종 결과를 화면에 그리기 (컬러 오버레이 + 알파 블렌딩)
    BLENDFUNCTION bf;
    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.SourceConstantAlpha = 128;  // 50% 투명도
    bf.AlphaFormat = 0;

    // 색상 오버레이를 알파 블렌딩으로 적용
    AlphaBlend(
        hTempDC, 
        0, 0, 
        (int)m_tInfo.fCX * m_iSizeXRate, (int)m_tInfo.fCY * m_iSizeYRate,
        hColorDC,
        0, 0, 
        (int)m_tInfo.fCX * m_iSizeXRate, (int)m_tInfo.fCY * m_iSizeYRate,
        bf
    );


    // 최종 이미지를 화면에 그리기
    BitBlt(
        hDC,
        (int)(m_tInfo.fX + CManager::Scroll()->Get_ScrollX()),
        (int)(m_tInfo.fY + CManager::Scroll()->Get_ScrollY()),
        (int)m_tInfo.fCX * m_iSizeXRate, (int)m_tInfo.fCY * m_iSizeYRate,
        hTempDC, 
        0, 0, 
        SRCCOPY
    );

    // 리소스 정리
    SelectObject(hColorDC, hOldColorBitmap);
    DeleteObject(hColorBitmap);
    DeleteDC(hColorDC);

    SelectObject(hTempDC, hOldBitmap);
    DeleteObject(hTempBitmap);
    DeleteDC(hTempDC);
}

void CBuildingPreview::Release()
{
}

void CBuildingPreview::Setting(STRUCTURE_ITEM_ID _id, int _iSizeX, int _iSizeY)
{
    m_eId = _id; 
    m_iSizeXRate = _iSizeX;
    m_iSizeYRate = _iSizeY;

    m_pFrameKey = enumTotchar_BuildingIcon(static_cast<int>(_id));
    int aa = 0;
}

// 1.현재 타일에 건설이 가능한지 ? 매니저에서 타일 정보 들고와서 옵션값이 0 이면 가능 
//   건물 사이즈 2X2라면 그 위치도 비교하기
// 2. 타일 위에 리소스가 없는지 검사하기
bool CBuildingPreview::CheckBuildable(int _x, int _y)
{
    if ( _x < 0 || TILEX <= _x || _y < 0 || TILEY < _y) return false;
    int iIndex = _y * TILEY + _x;

    //맵 범위 벗어나면
    if (iIndex < 0 || TILEY * TILEX <= iIndex) return false;
    if (m_iSizeXRate == 2) {
        if (iIndex + 1 < 0 || TILEY * TILEX <= iIndex + 1) return false;
        if (iIndex + TILEY < 0 || TILEY * TILEX <= iIndex + TILEY) return false;
        if (iIndex + TILEY + 1 < 0 || TILEY * TILEX <= iIndex + TILEY + 1) return false;
    }

    


    //타일 충돌 여부 (물에 지을 수 있는 건물은 옵션이 1과 2 일 때 트루 and 3 일 때 false / 땅에 짓는 건물은 0 일때 트루 )
    // 1 x 1 칸 비교
	if (m_eId == SI_F_0 || m_eId == SI_F_1 || m_eId == SI_E_3) {
		if (dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Get_Option() == 0 ||
            dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Get_Option() == 3)
            return false;
	}
	else if (dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Get_Option() != 0) return false;
	// 등대 2 x 2 비교
	if (m_eId == SI_E_3)
	{
        if (dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + 1])->Get_Option() == 0||
            dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + 1])->Get_Option() == 3) return false;
        if (dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY])->Get_Option() == 0 ||
            dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY])->Get_Option() == 3) return false;
        if (dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY + 1])->Get_Option() == 0 ||
            dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY + 1])->Get_Option() == 3) return false;
	}
	// 나머지 2 x 2 칸 비교
	else if (m_iSizeXRate == 2) {
		if (dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + 1])->Get_Option() != 0) return false;
		if (dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY])->Get_Option() != 0) return false;
		if (dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex + TILEY + 1])->Get_Option() != 0) return false;
	}

    //리소스 충돌 여부
    int curIsland = dynamic_cast<CPlayer*>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER))->Get_CurIsland();
    // 1 x 1칸 비교
    if(CManager::Spawner()->Find_Resource(iIndex, curIsland)) return false;
    // 2 x 2칸 비교
    if (m_iSizeXRate == 2) {
        if (CManager::Spawner()->Find_Resource(iIndex + 1, curIsland)) return false;
        if (CManager::Spawner()->Find_Resource(iIndex + TILEY, curIsland)) return false;
        if (CManager::Spawner()->Find_Resource(iIndex + TILEY + 1, curIsland)) return false;
    }


    return true;
}

void CBuildingPreview::Update_Build()
{
    //생성되자마자 마우스 프레싱 눌리는거 방지..... 이렇게하면 안되는데....
    if(m_dwTime + 400 < (DWORD)GetTickCount64())

	//마우스를 누르면
	if (CManager::Key()->Key_Pressing(VK_LBUTTON)) {

		//건설 가능한 부지인지?
		if (m_bCanBuild && !m_bBuild) {

	        //건물에 소모되는 자원 들고오기
            const int* cost = eunmTointArr_BuildingCost(static_cast<int>(m_eId));

		    //아이템 종류랑 수량 충분히 있는지?
            if (CManager::User()->Is_Enought_Item(cost)) 
                m_bBuild = true;

            //건설하기
            if (m_bBuild) {
                switch (m_eId)
                {
                case SI_I_0:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CFurnace>::Create(m_tInfo.fX + TILECX , m_tInfo.fY + TILECY ));
                    break;
                case SI_I_1:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CForge>::Create(m_tInfo.fX + TILECX , m_tInfo.fY + TILECY ));

                    break;
                case SI_I_2:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CSewingStation>::Create(m_tInfo.fX + TILECX , m_tInfo.fY + TILECY ));

                    break;
                case SI_F_0:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CBridge>::Create(m_tInfo.fX+ TILECX*0.5, m_tInfo.fY+ TILECY * 0.5));

                    break;
                case SI_F_1:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CFishTrap>::Create(m_tInfo.fX+ TILECX * 0.5, m_tInfo.fY+ TILECY * 0.5));

                    break;
                case SI_E_0:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CBank>::Create(m_tInfo.fX + TILECX , m_tInfo.fY + TILECY ));

                    break;
                case SI_E_1:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CMarket>::Create(m_tInfo.fX + TILECX , m_tInfo.fY + TILECY ));

                    break;
                case SI_E_2:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CVault>::Create(m_tInfo.fX + TILECX , m_tInfo.fY + TILECY ));

                    break;
                case SI_E_3:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CLighthouse>::Create(m_tInfo.fX + TILECX , m_tInfo.fY + TILECY ));

                    break;
                case SI_E_4:
                    CManager::Obj()->Add_Object(OBJ_STRUCTURE, CAbstractFactory<CSlotMachine>::Create(m_tInfo.fX + TILECX , m_tInfo.fY + TILECY ));

					break;
				}

                //건물 짓고 자원은 소모시키기
                for (int i = 0; i < 10; ++i)
                {
                    if (cost[i] > 0)
                        CManager::User()->Set_Item(static_cast<ITEMID>(i), -cost[i]);
                }

			}
		}

		//건물을 짓든 말든 마우스 클릭시 삭제
        CManager::UI()->Set_previewDelete();
	}
}
