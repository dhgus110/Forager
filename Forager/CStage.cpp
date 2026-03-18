#include "pch.h"

#pragma comment(lib, "msimg32.lib")
#include <Windows.h>

#include "CStage.h"
#include "CManager.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CWeapon.h"
#include "CPlayerHpBar.h"
#include "CExpBar.h"
#include "CCoin.h"
#include "CMenuTap.h"
#include "Data.h"
#include "CSubMenuButton.h"
#include "CItemInventory.h"
#include "CItemToolTip.h"
#include "CWeaponInventory.h"
#include "CWeaponSlot.h"
#include "CAccessoryInven.h"
#include "CSkillButton.h"
#include "CWordIsland.h"
#include "CSkillButtons.h"
#include "CSoundMgr.h"
#include "CMainStructure.h"
#include "CSubStructure.h"
#include "CBuildingPreview.h"
#include "CFlag.h"
#include "CTextRender.h"
#include "CFurnace.h"
#include "CFurnaceTrade.h"
#include "CTradeTooltip.h"
#include "CConstructTooltip.h"
#include "CForgeTrade.h"

CStage::CStage() : m_iTest(1), m_dwResourceRespawnTime(0), m_iResourceCnt(0), m_iCurScreen(0),
m_bJoinMenuDarkLight(false), m_dwDayTime((DWORD)GetTickCount64()), m_bDay(false), m_iAlphaValue(0),
m_bNightChange(false), m_iDayCnt(0)
{

}

CStage::~CStage()
{
	Release();
}

void CStage::Initailize()
{
	CManager::Obj()->Add_Object(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(1120.f,1120.f));
	CManager::Obj()->Add_Object(OBJ_EQUIP, CAbstractFactory<CWeapon>::Create());

	CManager::UI()->AddObject(UI_PLAYER_HP, CAbstractFactory<CPlayerHpBar>::CreateUI());
	dynamic_cast<CPlayerHpBar*>(CManager::UI()->Get_ObjectBack(UI_PLAYER_HP))->
		Setting_Hp(dynamic_cast<CPlayer*>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER))->Get_Hp());

	CManager::UI()->AddObject(UI_PLAYER_EXP, CAbstractFactory<CExpBar>::CreateUI());
	CManager::UI()->AddObject(UI_PLAYER_COIN, CAbstractFactory<CCoin>::CreateUI());
	CManager::UI()->AddObject(UI_MENU_TAP, CAbstractFactory<CMenuTap>::CreateUI());
	CManager::UI()->AddObject(UI_MENU_TAP_SUB, CAbstractFactory<CSubMenuButton>::CreateUI());
	CManager::UI()->AddObject(UI_MENU_ITEM_SLOT, CAbstractFactory<CItemInventory>::CreateUI());
	dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->MoveToSlot(500.f,0.f,-500.f);

	CManager::UI()->AddObject(UI_MENU_ITEM_TOOLTIP, CAbstractFactory<CItemToolTip>::CreateUI());
	CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_TOOLTIP)->MoveToPosition((float)WINCX+10.f, 100.f, 500.f);

	CManager::UI()->AddObject(UI_MENU_WEAPON_INVEN, CAbstractFactory<CWeaponInventory>::CreateUI(UIPos::WeaponInven.x,UIPos::WeaponInven.y));
	CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_INVEN, false);

	for(int i = 0 ; i< WEAPON_SLOT_CNT ; ++i)
	CManager::UI()->AddObject(UI_MENU_WEAPON_SLOT, CAbstractFactory<CWeaponSlot>::CreateUI(UIPos::Weapon_Slot(i).x, UIPos::Weapon_Slot(i).y));
	CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_SLOT, false);

	//웨폰인벤에 넣어놨음!! 문제 생길 수도
	CManager::UI()->AddObject(UI_MENU_WEAPON_INVEN, CAbstractFactory<CAccessoryInven>::CreateUI(UIPos::AccesoryInven.x, UIPos::AccesoryInven.y));
	CManager::UI()->AddObject(UI_MENU_WEAPON_INVEN, CAbstractFactory<CWordIsland>::CreateUI(UIPos::WordIslandCnt.x, UIPos::WordIslandCnt.y));

	CManager::UI()->AddObject(UI_MENU_Skill_BTN, CAbstractFactory<CSkillButton>::CreateUI(UIPos::SkillBtn.x, UIPos::SkillBtn.y));
	CManager::UI()->Set_IsUIView(UI_MENU_Skill_BTN, false);

	//스킬 버튼들
	for (size_t i = 0; i < SK_END; ++i) {
		CManager::UI()->AddSkill(static_cast<SKILLID>(i), CAbstractFactory<CSkillButtons>::CreateUI(UIPos::SkillPos(i).x, UIPos::SkillPos(i).y));
		dynamic_cast<CSkillButtons*>(CManager::UI()->Get_SkillBack(static_cast<SKILLID>(i)))->Setting(static_cast<SKILLID>(i));
		
	}

	//건설 메인 버튼들
	for (size_t i = 0; i < ST_END; ++i) {
		UIPOS pos = UIPos::Main_Structure_Button(i, static_cast<int>(ST_END));
		CManager::UI()->AddMainStructure(static_cast<MAIN_STRUCTURE_TYPE>(i), CAbstractFactory<CMainStructure>::CreateUI(pos.x, pos.y));
		dynamic_cast<CMainStructure*>(CManager::UI()->Get_MainStructure(static_cast<MAIN_STRUCTURE_TYPE>(i)))->Set_Type(static_cast<MAIN_STRUCTURE_TYPE>(i));
	}

	//건설 서브 버튼들
	for (size_t type = 0; type < ST_END; ++type) {
		for (size_t sub = 0; sub < SST_END; ++sub) {
			MAIN_STRUCTURE_TYPE t = static_cast<MAIN_STRUCTURE_TYPE>(type);
			SUB_STRUCTURE_TYPE s = static_cast<SUB_STRUCTURE_TYPE>(sub);
			UIPOS pos = UIPos::Main_Structure_Button(type, static_cast<int>(ST_END)); //처음 위치값은 메인버튼 뒤에
			CManager::UI()->AddSubStructure(t, s, CAbstractFactory<CSubStructure>::CreateUI(pos.x, pos.y));
			dynamic_cast<CSubStructure*>(CManager::UI()->Get_SubStructure(t, s))->Set_Type(t, s);
		}
	}
	
	//건설 툴팁
	CManager::UI()->AddObject(UI_BUILDING_TOOLTIP, CAbstractFactory<CConstructTooltip>::CreateUI());
	

	//토지 구입 깃발들 초기화 
	int iTemp(0);
	for (const auto& it : CManager::User()->Get_Island())
	{
		// 섬 중간 좌표
		float fX = static_cast<float>(it.iMinX * TILECX + ((it.iMaxX - it.iMinX) / 2) * TILECX);
		float fY = static_cast<float>(it.iMinY * TILECY + ((it.iMaxY - it.iMinY) / 2 - 3 ) * TILECY); // -3은 깃발 좀 더 올릴려고

		//UI매니저 리스트에 추가
		CUI* pCUI = CAbstractFactory<CFlag>::CreateUI(fX, fY);
		CManager::UI()->AddObject(UI_FLAG, pCUI);

		//코스트 지정
		dynamic_cast<CFlag*>(pCUI)->Setting(iTemp);
		++iTemp;
	}

	//거래창들
	CManager::UI()->AddObject(UI_TRADE, CAbstractFactory<CFurnaceTrade>::CreateUI());//용광로 거래창
	CManager::UI()->AddObject(UI_TRADE, CAbstractFactory<CForgeTrade>::CreateUI());//용광로 거래창



	CManager::Tile()->Initialilze();
	CManager::Spawner()->Initialize();
	CManager::UI()->Initailize();
	CManager::User()->Initialilze();
	
	//사운드
	CSoundMgr::Get_Instance()->StopAll();
	CSoundMgr::Get_Instance()->PlayBGM(L"BackGround_Sound.mp3", 1.f);
	
	//밤에서부터 시작
	m_iAlphaValue = 150;

}

void CStage::Update()
{	
	Key_Input();
	//자원 리스폰 (나무 많이 생성하기)
	if (m_dwResourceRespawnTime + 20000<= (DWORD)GetTickCount64())
	{
		if (CManager::Spawner()->Check_ResourceCountLimit())
		{
			++m_iResourceCnt;
			for (int i = 0; i < 9; ++i) {
				if (CManager::User()->Get_IsBuyIsland(i))
					if (m_iResourceCnt % 2 == 0)
						CManager::Spawner()->ResourceSpawn(i);
					else
						CManager::Spawner()->ResourceSpawn(i, RE_TREE);
			}
		}

		m_dwResourceRespawnTime = (DWORD)GetTickCount64();
	}

	//test 섬 생성
	//if (CManager::Key()->Key_Down(VK_SPACE)) {
	//	CManager::User()->Set_IsBuyIsland(m_iTest++);
	//}

	CManager::Tile()->Update();
	CManager::Spawner()->Update();

	CManager::Obj()->Update();
	//CManager::Spawner()->Update();
	CManager::UI()->Update();
}

void CStage::Late_Update()
{
	CManager::Tile()->Late_Update();
	CManager::Spawner()->Late_Update();

	CManager::Obj()->Late_Update();
	//CManager::Spawner()->Late_Update();
	CManager::UI()->Late_Update();
	CManager::Scroll()->Late_Update();
	AllDayCycle();

}

void CStage::Render(HDC hDC)
{
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Temp");

	BitBlt(hBackDC,		// 복사 받을 화면 dc
		0,	// 복사 받을 위치 좌표
		0,
		WINCX,		// 복사 받을 이미지 가로, 세로 사이즈
		WINCY,
		hGroundDC,		// 복사할 이미지 dc
		0, 0,		// 비트맵 출력 자표
		SRCCOPY);


	CManager::Tile()->Render(hBackDC);

	CManager::Spawner()->Render(hBackDC);
	CManager::Obj()->Render(hBackDC);
	

	if(!m_bDay)
		RenderLighting(hBackDC,true); 
	if(m_bJoinMenuDarkLight) //메뉴 들어갈 때 
		RenderLighting(hBackDC, false);

	//해와 달
	HDC	hMemDC;
	if (m_bDay) hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Sun");
	else hMemDC = CBmpMgr::Get_Instance()->Find_Img(L"Moon");
	GdiTransparentBlt(hBackDC,
		105,
		50,
		56, 56,
		hMemDC,
		0,
		0,
		56,
		56,
		RGB(255, 0, 255));

	CManager::UI()->Render(hBackDC);


	BitBlt(hDC,		// 복사 받을 화면 dc
		0,	// 복사 받을 위치 좌표
		0,
		WINCX,		// 복사 받을 이미지 가로, 세로 사이즈
		WINCY,
		hBackDC,		// 복사할 이미지 dc
		0, 0,		// 비트맵 출력 자표
		SRCCOPY);	// 그대로 출력


}

void CStage::Release()
{
	CManager::Tile()->Release();
	CManager::Obj()->Release();
	CManager::Spawner()->Release();
	CManager::UI()->Release();

}

void CStage::Key_Input()
{
	if (CManager::Key()->Key_Down(VK_ESCAPE))
	{
		//게임 화면 -> 메뉴탭으로 이동
		if (m_iCurScreen == 0)
		{
			CManager::UI()->Get_ObjectBack(UI_MENU_TAP)->MoveToPosition(UIPos::MenuTapIn.x, UIPos::MenuTapIn.y);
			CManager::UI()->Get_ObjectBack(UI_PLAYER_EXP)->MoveToPosition(UIPos::ExpBarOut.x, UIPos::ExpBarOut.y);
			m_bJoinMenuDarkLight = true; //알파블랜딩

			dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->ReturnToOriginalSlotPos(200.f);

			m_iCurScreen = 1;

			CSoundMgr::Get_Instance()->StopSound(SOUND_MENU);
			CSoundMgr::Get_Instance()->PlaySound(L"Menu_Open.wav", SOUND_MENU, 0.7f);

		}
		// 메뉴 탭 -> 게임화면으로 이동
		else if(m_iCurScreen == 1)
		{
			CManager::UI()->Get_ObjectBack(UI_MENU_TAP)->ReturnToOriginalPos();
			CManager::UI()->Get_ObjectBack(UI_PLAYER_EXP)->ReturnToOriginalPos();
			dynamic_cast<CSubMenuButton*>(CManager::UI()->Get_ObjectBack(UI_MENU_TAP_SUB))->Reset();
			dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->MoveToSlot(100.f,0.f, -500.f);
			CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_TOOLTIP)->MoveToPosition((float)WINCX + 10.f, 100.f, 500.f);
			CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_INVEN, false);
			CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_SLOT, false);
			CManager::UI()->Set_IsUIView(UI_MENU_Skill_BTN, false);
			CManager::UI()->Set_StructureView(false);
			CManager::UI()->Init_Structure_Buttons_Position();
			CManager::UI()->Set_Island_Flag(false);
			dynamic_cast<CConstructTooltip*>(CManager::UI()->Get_ObjectBack(UI_BUILDING_TOOLTIP))->Reset();

			CSoundMgr::Get_Instance()->StopSound(SOUND_MENU);
			CSoundMgr::Get_Instance()->PlaySound(L"Menu_Close.wav", SOUND_MENU, 0.7f);


			m_bJoinMenuDarkLight = false;
			m_iCurScreen = 0;
		}
		//스킬 창 -> 메뉴 탭
		else if (m_iCurScreen == 2)
		{
			CSoundMgr::Get_Instance()->StopSound(SOUND_MENU);
			CSoundMgr::Get_Instance()->PlaySound(L"Menu_Open.wav", SOUND_MENU, 0.7f);

			CManager::UI()->Set_SkillView(false);
			m_iCurScreen = 1;
		}
	}
}

void CStage::RenderLighting(HDC hDC , bool bPlayer)
{
	// 1. 빈 비트맵 생성 (화면 크기)
	HDC lightDC = CreateCompatibleDC(hDC);  // 광원에 사용할 dc 생성
	HBITMAP lightBitmap = CreateCompatibleBitmap(hDC, WINCX, WINCY);  //실제 비트맵 객체 (전체크기의 비트맵)
	SelectObject(lightDC, lightBitmap); //비트맨과 dc 연결

	// 2. 비트맵을 어둡게 채우기
	HBRUSH darkBrush = CreateSolidBrush(RGB(0, 0, 0));  //검정 붓
	RECT screenRect = { 0, 0, WINCX, WINCY };  //화면을 덮을 직사각형
	FillRect(lightDC, &screenRect, darkBrush); //위에 정의한거 검정으로 채움
	DeleteObject(darkBrush);	//붓 제거

	// 3.플레이어 위치는 조명 영역을 밝게
	if (bPlayer)
	{
		int iScrollX = static_cast<int>(CManager::Scroll()->Get_ScrollX());
		int iScrollY = static_cast<int>(CManager::Scroll()->Get_ScrollY());

		int lightX = static_cast<int>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER)->Get_Info()->fX) + iScrollX;
		int lightY = static_cast<int>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER)->Get_Info()->fY) + iScrollY;

		int lightRadius = 200;  // 조명 반경

		SelectObject(lightDC, GetStockObject(NULL_PEN));  //원 그리기 전 외곽선 삭제 옵션임 

		// 4. 플레이어 중심 그라데이션 조명 효과
		for (int i = lightRadius; i > lightRadius - 100; i -= 5) {
			int alpha = 255 - (i * 255 / lightRadius); //그라데이션줄려고
			HBRUSH gradientionBrush = CreateSolidBrush(RGB(alpha, alpha, alpha));
			SelectObject(lightDC, gradientionBrush);
			Ellipse(lightDC, lightX - i, lightY - i, lightX + i, lightY + i);
			DeleteObject(gradientionBrush);
		}
	}

		// 블렌딩 모드 설정
	BLENDFUNCTION blend = { AC_SRC_OVER, 0, m_iAlphaValue, 0 };

	if (m_bJoinMenuDarkLight)//메뉴탭 누르면
		blend = { AC_SRC_OVER, 0, 150, 0 }; // 150은 투명도 (0-255)


	// 5. 화면에 적용
	AlphaBlend(hDC, 0, 0, WINCX, WINCY, lightDC, 0, 0, WINCX, WINCY, blend);

	// 6. 리소스 정리
	DeleteObject(lightBitmap);
	DeleteDC(lightDC);
}

void CStage::AllDayCycle()
{
	//500으로 세팅하면 적당할 듯 
	if (m_dwDayTime + 500 < (DWORD)GetTickCount64())
	{
		m_dwDayTime = (DWORD)GetTickCount64();
		if (!m_bDay)
		{
			if (m_bNightChange)
			{
				++m_iAlphaValue;
				if (m_iAlphaValue == 150) m_bNightChange = false;
			}
			else
			{
				--m_iAlphaValue;
				if (m_iAlphaValue == 30) //아침이 다가오는 ..
				{
					m_bNightChange = true;
					m_bDay = true;
					bCheckFPS = false;
				}
			}
		}
		else
		{
			++m_iDayCnt;
			if (m_iDayCnt == 150)
			{
				m_iDayCnt = 0;
				m_bDay = false;
				bCheckFPS = true;
			}
		}
	}
}
