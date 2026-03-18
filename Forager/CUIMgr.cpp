#include "pch.h"
#include "CUIMgr.h"
#include <algorithm>
#include "CManager.h"
#include <string>
#include "CCollisionMgr.h"
#include "Data.h"
#include "CItemInventory.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr() :m_bSkillView(false), m_dwSkillWindowTime(0), m_iSkillWindowMotion(0), m_bStructureView(false), m_bIslandFlag(false),
m_bPreviewDelete(false)
{
	for (size_t i = 0; i < UI_END; ++i)
		m_IsUIViewList.push_back(true);

	m_CurSelectMainStructureBtn = { ST_END, false };
	m_CurSelectSubStructureBtn = { SST_END ,false };
	m_dwPressIntervalTime = 0;
}

CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initailize()
{

	CManager::Bmp()->Insert_Bmp(L"../Image/Back.bmp", L"Back");
	CManager::Bmp()->Insert_Bmp(L"../Image/Back.bmp", L"Temp");
	CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile.bmp", L"Tile");

	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Berry.bmp", L"Berry");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Coal.bmp", L"Coal");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Gold_Ore.bmp", L"Gold_Ore");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Iron_Ore.bmp", L"Iron_Ore");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Stone.bmp", L"Stone");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Tree.bmp", L"Tree");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Wood.bmp", L"Wood");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Sand.bmp", L"Sand");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Brick.bmp", L"Brick");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Fish.bmp", L"Fish");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Jelly.bmp", L"Jelly");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Cook_Fish.bmp", L"Cook_Fish");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Smelt_Gold.bmp", L"Smelt_Gold");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Smelt_Iron.bmp", L"Smelt_Iron");

	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Berry_Drop.bmp", L"Berry_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Berry_Fruit.bmp", L"Berry_Fruit");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Coal_Drop.bmp", L"Coal_Drop"); 
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Citrus_Drop.bmp", L"Citrus_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Gold_Drop.bmp", L"Gold_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Iron_Drop.bmp", L"Iron_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Stone_Drop.bmp", L"Stone_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Wood_Drop.bmp", L"Wood_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Sand_Drop.bmp", L"Sand_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Fish_Drop.bmp", L"Fish_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Cook_Fish_Drop.bmp", L"Cook_Fish_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Wood_Drop.bmp", L"Wood_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Smelt_Gold_Drop.bmp", L"Smelt_Gold_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Smelt_Iron_Drop.bmp", L"Smelt_Iron_Drop");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Resources/Brick_Drop.bmp", L"Brick_Drop");

	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/CommonHpBar.bmp", L"CommonHpBar"); 
		CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Boss_hpBar.bmp", L"Boss_hpBar");

	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Player_Hp.bmp", L"Player_Hp");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Player_Stamina.bmp", L"Player_Stamina");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Player_Stamina_Back.bmp", L"Player_Stamina_Back");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Player_Exp.bmp", L"Player_Exp");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Player_Exp_Back.bmp", L"Player_Exp_Back");

	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Word_Exp.bmp", L"Word_Exp");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Font_Slash.bmp", L"Font_Slash");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Coin.bmp", L"Coin");

	//메뉴탭 버튼들
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_active_Construct.bmp", L"MenuTap_active_Construct");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_active_Equip.bmp", L"MenuTap_active_Equip");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_active_Island.bmp", L"MenuTap_active_Island");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_active_Item.bmp", L"MenuTap_active_Item");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_active_Setting.bmp", L"MenuTap_active_Setting");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_Base.bmp", L"MenuTap_Base");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_Inactive_Construct.bmp", L"MenuTap_Inactive_Construct");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_Inactive_Equip.bmp", L"MenuTap_Inactive_Equip");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_Inactive_Island.bmp", L"MenuTap_Inactive_Island");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_Inactive_Item.bmp", L"MenuTap_Inactive_Item");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/MenuTap_Inactive_Setting.bmp", L"MenuTap_Inactive_Setting");

	//아이템창 버튼들?
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Item_Inventory_Slot.bmp", L"Item_Inventory_Slot");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Item_ToolTip.bmp", L"Item_ToolTip");

	//장비창 버튼들
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Weapon_Inven.bmp", L"Weapon_Inven");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Weapon_Slot.bmp", L"Weapon_Slot");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Accessory_Inven.bmp", L"Accessory_Inven"); 
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Skill_Btn.bmp", L"Skill_Btn"); 
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Word_Island_Cnt.bmp", L"Word_Island_Cnt");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Word_Weapon.bmp", L"Word_Weapon");

	//건설 메인 버튼
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Main_Industry.bmp", L"Main_Industry");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Main_Farming.bmp", L"Main_Farming");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Main_Economy.bmp", L"Main_Economy");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Main_Magic.bmp", L"Main_Magic");

	//건설 서브 버튼
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_I_0.bmp", L"Sub_I_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_I_1.bmp", L"Sub_I_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_I_2.bmp", L"Sub_I_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_I_3.bmp", L"Sub_I_3");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_I_4.bmp", L"Sub_I_4");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_I_Empty.bmp", L"Sub_I_Empty");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_F_0.bmp", L"Sub_F_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_F_1.bmp", L"Sub_F_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_F_2.bmp", L"Sub_F_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_F_3.bmp", L"Sub_F_3");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_F_4.bmp", L"Sub_F_4");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_F_Empty.bmp", L"Sub_F_Empty");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_E_0.bmp", L"Sub_E_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_E_1.bmp", L"Sub_E_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_E_2.bmp", L"Sub_E_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_E_3.bmp", L"Sub_E_3");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_E_4.bmp", L"Sub_E_4");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_E_Empty.bmp", L"Sub_E_Empty");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_M_0.bmp", L"Sub_M_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_M_1.bmp", L"Sub_M_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_M_2.bmp", L"Sub_M_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_M_3.bmp", L"Sub_M_3");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_M_4.bmp", L"Sub_M_4");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Structure/Sub_M_Empty.bmp", L"Sub_M_Empty");

	//숫자들
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/0.bmp", L"0"); 
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/1.bmp", L"1");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/2.bmp", L"2");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/3.bmp", L"3");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/4.bmp", L"4");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/5.bmp", L"5");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/6.bmp", L"6");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/7.bmp", L"7");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/8.bmp", L"8");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/9.bmp", L"9"); 
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y0.bmp", L"Y0");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y1.bmp", L"Y1");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y2.bmp", L"Y2");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y3.bmp", L"Y3");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y4.bmp", L"Y4");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y5.bmp", L"Y5");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y6.bmp", L"Y6");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y7.bmp", L"Y7");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y8.bmp", L"Y8");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Y9.bmp", L"Y9");

	//스킬 버튼들
	CManager::Bmp()->Insert_Bmp(L"../Image/Skill/Skill_BackGround.bmp", L"Skill_BackGround");
	CManager::Bmp()->Insert_Bmp(L"../Image/Skill/Skill_E_Active.bmp", L"Skill_E_Active");
	CManager::Bmp()->Insert_Bmp(L"../Image/Skill/Skill_E_Inactive.bmp", L"Skill_E_Inactive");
	CManager::Bmp()->Insert_Bmp(L"../Image/Skill/Skill_H_Active.bmp", L"Skill_H_Active");
	CManager::Bmp()->Insert_Bmp(L"../Image/Skill/Skill_H_Inactive.bmp", L"Skill_H_Inactive");
	CManager::Bmp()->Insert_Bmp(L"../Image/Skill/Skill_I_Inactive.bmp", L"Skill_I_Inactive");
	CManager::Bmp()->Insert_Bmp(L"../Image/Skill/Skill_M_Inactive.bmp", L"Skill_M_Inactive");
	CManager::Bmp()->Insert_Bmp(L"../Image/Skill/Skill_Effect.bmp", L"Skill_Effect"); 

	//건물 아이콘?
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_I_0.bmp", L"SI_I_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_I_1.bmp", L"SI_I_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_I_2.bmp", L"SI_I_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_I_3.bmp", L"SI_I_3");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_I_4.bmp", L"SI_I_4");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_F_0.bmp", L"SI_F_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_F_1.bmp", L"SI_F_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_F_2.bmp", L"SI_F_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_F_3.bmp", L"SI_F_3");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_F_4.bmp", L"SI_F_4");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_E_0.bmp", L"SI_E_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_E_1.bmp", L"SI_E_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_E_2.bmp", L"SI_E_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_E_3.bmp", L"SI_E_3");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_E_4.bmp", L"SI_E_4");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_M_0.bmp", L"SI_M_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_M_1.bmp", L"SI_M_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_M_2.bmp", L"SI_M_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_M_3.bmp", L"SI_M_3");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/SI_M_4.bmp", L"SI_M_4");

	//건물 오브젝트 애니메이션인데 ui상속 안받지만 그냥 여기서 비트맵 부름.
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_E_0.bmp", L"Ani_SI_E_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_E_1.bmp", L"Ani_SI_E_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_E_2.bmp", L"Ani_SI_E_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_E_3.bmp", L"Ani_SI_E_3");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_E_4.bmp", L"Ani_SI_E_4");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_F_0.bmp", L"Ani_SI_F_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_F_1.bmp", L"Ani_SI_F_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_I_0.bmp", L"Ani_SI_I_0");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_I_1.bmp", L"Ani_SI_I_1");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Ani_SI_I_2.bmp", L"Ani_SI_I_2");
	CManager::Bmp()->Insert_Bmp(L"../Image/Object/Buildings/Pruduction_SI_I_0.bmp", L"Pruduction_SI_I_0");

	//기타등등
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Word_Chapture.bmp", L"Word_Chapture"); 
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Interacter.bmp", L"Interacter");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Flag.bmp", L"Flag");
	CManager::Bmp()->Insert_Bmp(L"../Image/NPC/Boss.bmp", L"Boss");
	CManager::Bmp()->Insert_Bmp(L"../Image/NPC/Boss_Jump.bmp", L"Boss_Jump");
	CManager::Bmp()->Insert_Bmp(L"../Image/NPC/Boss_Dead.bmp", L"Boss_Dead");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/USE_Btn.bmp", L"USE_Btn"); 
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Trade_Base.bmp", L"Trade_Base");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Production_Btn.bmp", L"Production_Btn");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Sun.bmp", L"Sun");
	CManager::Bmp()->Insert_Bmp(L"../Image/GUI/Moon.bmp", L"Moon");

	//이펙트
	CManager::Bmp()->Insert_Bmp(L"../Image/Effects/Effect_Furnace_Smoke.bmp", L"Effect_Furnace_Smoke");
	CManager::Bmp()->Insert_Bmp(L"../Image/Effects/Effect_Boss_Jump.bmp", L"Effect_Boss_Jump");
	CManager::Bmp()->Insert_Bmp(L"../Image/Effects/Effect_DigSmoke.bmp", L"Effect_DigSmoke");
	CManager::Bmp()->Insert_Bmp(L"../Image/Effects/Effect_LevelUp.bmp", L"Effect_LevelUp");
	CManager::Bmp()->Insert_Bmp(L"../Image/Effects/Effect_Pick.bmp", L"Effect_Pick");
	CManager::Bmp()->Insert_Bmp(L"../Image/Effects/Effect_Step.bmp", L"Effect_Step");


}

void CUIMgr::Update()
{

	for (auto it = m_pCommonHpList.begin(); it != m_pCommonHpList.end();) {
		if ((*it).second->Update() == UI_DEAD)
		{
			SafeDelete<CUI*>((*it).second);
			it = m_pCommonHpList.erase(it);
		}
		else
			++it;
	}

	for (size_t i = 0; i < UI_END; ++i) {
		for (auto it = m_pUIList[i].begin(); it != m_pUIList[i].end();) {
			if ((*it)->Update() == UI_DEAD)
			{
				SafeDelete<CUI*>(*it);
				it = m_pUIList[i].erase(it);
			}
			else
				++it;
		}
	}

	if (m_bSkillView) {
		for (size_t i = 0; i < SK_END; ++i) {
			for (auto it = m_pSKillList[i].begin(); it != m_pSKillList[i].end(); ++it) {
				(*it)->Update();
			}
		}
		Move_Frame();
	}

	//todo 건설탭 보일 때만 업데이트
	if (m_bStructureView)
	{
		for (size_t i = 0; i < ST_END; ++i) {
			for (auto it = m_pMainStructure[i].begin(); it != m_pMainStructure[i].end(); ++it) {
				(*it)->Update();
			}

			for (size_t j = 0; j < SST_END; ++j) {
				for (auto it = m_pSubStructure[i][j].begin(); it != m_pSubStructure[i][j].end(); ++it) {
					(*it)->Update();
				}
			}
		}
	}
}

void CUIMgr::Late_Update()
{
	for (auto obj : m_pCommonHpList) {
		obj.second->Late_Update();
	}

	for (size_t i = 0; i < UI_END; ++i) {
		for (auto obj : m_pUIList[i]) {
			obj->Late_Update();

		}
	}


	CCollisionMgr::Collision_SubMenuButton(m_pUIList[UI_MOUSE], m_pUIList[UI_MENU_TAP_SUB]);
	CCollisionMgr::Collision_ItemSlot(m_pUIList[UI_MOUSE], m_pUIList[UI_MENU_ITEM_SLOT], m_pUIList[UI_MENU_ITEM_TOOLTIP].back());
	CCollisionMgr::Collision_Equip(m_pUIList[UI_MOUSE], m_pUIList[UI_MENU_Skill_BTN]);
	CCollisionMgr::Collision_Equip(m_pUIList[UI_MOUSE], m_pUIList[UI_MENU_WEAPON_SLOT]);
	CCollisionMgr::Collision_Skill(m_pUIList[UI_MOUSE], m_pSKillList);
	CCollisionMgr::Collision_BuyIsland(m_pUIList[UI_MOUSE], m_pUIList[UI_FLAG]);
	CCollisionMgr::Collision_TradeSlot(m_pUIList[UI_MOUSE], m_pUIList[UI_TRADE_SLOT],m_pUIList[UI_TRADE_FURNACE_TOOLTIP].back());

	//프리뷰 먼저 제거 후 콜리젼 돌아가야 위치 액세스 위반 안함 (리스트.back()읽는 부분있어서) (+ 그냥 empty()로 예외처리 해놨음. 그래도 위치 이대로 두자)
	PreviewDelete();
	CCollisionMgr::Collision_Structure(m_pUIList[UI_MOUSE], m_pMainStructure, m_pSubStructure);
}

void CUIMgr::Render(HDC hDC)
{
	// 오브젝트 체력바
	for (auto obj : m_pCommonHpList) {
		obj.second->Render(hDC);
	}

	//스킬창 보여주기
	if (m_bSkillView) {
		HDC	hMemDC = CManager::Bmp()->Find_Img(L"Skill_BackGround");
		GdiTransparentBlt(hDC,
			0,
			0,
			WINCX,
			WINCY,
			hMemDC,
			WINCX * m_iSkillWindowMotion,
			0,
			WINCX,
			WINCY,
			RGB(255, 0, 255));
		float fTemp(0.f);
		NumberRender(CManager::User()->Get_SkillPoint(), 10, 30, 585.f, 15.f, &fTemp, false, hDC, false);
		for (size_t i = 0; i < SK_END; ++i) {
			auto val = CManager::User()->Get_Skill(static_cast<SKILLID>(i));
			// 해금했으면 다른 이미지로 교체 
			// if(val.first)
			// 배웠거나 배울 수 있는 상태이면 랜더링
			if (val.second) {
				for (auto it = m_pSKillList[i].begin(); it != m_pSKillList[i].end(); ++it) {
					(*it)->Render(hDC);
				}
			}
		}
	}

	//건설 탭
	if (m_bStructureView)
	{
		for (size_t i = 0; i < ST_END; ++i) {
			//서브 버튼 먼저 랜더링
			for (size_t j = 0; j < SST_END; ++j) {
				for (auto it = m_pSubStructure[i][j].begin(); it != m_pSubStructure[i][j].end(); ++it) {
					(*it)->Render(hDC);
				}
			}

			for (auto it = m_pMainStructure[i].begin(); it != m_pMainStructure[i].end(); ++it) {
				(*it)->Render(hDC);
			}

		}
	}


	//나머지 UI들
	for (size_t i = 0; i < UI_END; ++i) {
		if (m_IsUIViewList[i]) {
			for (auto obj : m_pUIList[i]) {
				//스킬창이 떳을 때 마우스만
				if(m_bSkillView&& i == UI_MOUSE)
					obj->Render(hDC);

				//스킬창이 안떳을 때
				if (!m_bSkillView) {
					obj->Render(hDC);

					if (i == UI_MENU_WEAPON_SLOT)
					{
						View_Weapon_Slot(hDC);
					}
					if (i == UI_MENU_ITEM_SLOT)
					{
						View_Item_Slot(hDC);
					}
				}

			}
		}
	}

}

void CUIMgr::Release()
{
	for (size_t i = 0; i < UI_END; ++i)
	{
		for_each(m_pUIList[i].begin(), m_pUIList[i].end(), DeleteObj());
		m_pUIList[i].clear();
	}

	for (auto res : m_pCommonHpList)
	{
		if (res.second)
		{
			delete res.second;
			res.second = nullptr;
		}
	}

	for (size_t i = 0; i < SK_END; ++i)
	{
		for_each(m_pSKillList[i].begin(), m_pSKillList[i].end(), DeleteObj());
		m_pSKillList[i].clear();
	}

	for (size_t i = 0; i < ST_END; ++i)
	{
		for_each(m_pMainStructure[i].begin(), m_pMainStructure[i].end(), DeleteObj());
		m_pMainStructure[i].clear();
		for (size_t j = 0; j < SST_END; ++j) {
			for_each(m_pSubStructure[i][j].begin(), m_pSubStructure[i][j].end(), DeleteObj());
			m_pSubStructure[i][j].clear();
		}
	}
}

void CUIMgr::AddObject(UIID _id, CUI* _pObj)
{
	if (_id >= UI_END || _pObj == nullptr) return;

	m_pUIList[_id].push_back(_pObj);
}

void CUIMgr::AddObject(int _iIndex, CUI* _pCUI)
{
	if (_pCUI == nullptr) return;
	m_pCommonHpList.push_back({ _iIndex, _pCUI });

}

void CUIMgr::Delete_Obj(UIID eID)
{
	//for (auto it : m_pCommonHpList) {
	//	SafeDelete(it.second);
	//}
	//m_pCommonHpList.clear();

	for (auto& pObj : m_pUIList[eID])
	{
		SafeDelete(pObj);
	}

	m_pUIList[eID].clear();
}

void CUIMgr::Delete_CommonHp(int _iIndex)
{
	auto it = find_if(m_pCommonHpList.begin(), m_pCommonHpList.end(),
		[_iIndex](pair<int, CUI*> elem) {return elem.first == _iIndex; });

	if (it != m_pCommonHpList.end())
	{
		SafeDelete((*it).second);
		m_pCommonHpList.erase(it);
	}
}

void CUIMgr::AddSkill(SKILLID _id, CUI* _pObj)
{
	m_pSKillList[_id].push_back(_pObj);
}

void CUIMgr::Delete_Obj(SKILLID _id)
{
	for (auto& pObj : m_pSKillList[_id])
		SafeDelete(pObj);

	m_pUIList[_id].clear();
}

void CUIMgr::AddMainStructure(MAIN_STRUCTURE_TYPE _type, CUI* _pObj)
{
	m_pMainStructure[_type].push_back(_pObj);
}

void CUIMgr::Delete_Obj(MAIN_STRUCTURE_TYPE _type)
{
	for (auto& pObj : m_pMainStructure[_type])
		SafeDelete(pObj);

	m_pMainStructure[_type].clear();
}

void CUIMgr::AddSubStructure(MAIN_STRUCTURE_TYPE _type, SUB_STRUCTURE_TYPE _sub, CUI* _pObj)
{
	m_pSubStructure[_type][_sub].push_back(_pObj);
}

void CUIMgr::Delete_Obj(MAIN_STRUCTURE_TYPE _type, SUB_STRUCTURE_TYPE _sub)
{
	for (auto& pObj : m_pSubStructure[_type][_sub])
		SafeDelete(pObj);
	
	m_pSubStructure[_type][_sub].clear();
}

CUI* CUIMgr::Get_CommonHp(int _iIndex)
{
	auto it = find_if(m_pCommonHpList.begin(), m_pCommonHpList.end(), [_iIndex](pair<int, CUI*> elem) {return elem.first == _iIndex; });
	if (it != m_pCommonHpList.end())
		return (*it).second;
	return nullptr;
}

void CUIMgr::Set_Island_Flag(bool _b)
{
	m_bIslandFlag = _b;
	CManager::Scroll()->Set_OriginalScroll();
}

void CUIMgr::NumberRender(int _value, int _sizeX, int _sizeY, float _fX, float _fY, float* _fNextX,bool _bScroll, HDC hDC, bool _isYellow)
{
	string str = to_string(_value);

	for (size_t i = 0; i < str.size(); ++i) {

		HDC	hMemDC;
		if(!_isYellow)
			hMemDC = CManager::Bmp()->Find_Img(NumToTchar(str[i] - '0'));
		else
			hMemDC = CManager::Bmp()->Find_Img(NumToTchar2(str[i] - '0'));

		if(!_bScroll)
			GdiTransparentBlt(hDC,
				static_cast<int>(_fX) + _sizeX * i ,
				static_cast<int>(_fY),
				_sizeX,
				_sizeY,
				hMemDC,
				0, 0,
				15, 19,
				RGB(255, 0, 255));
		else
		{
			int iScrollX = static_cast<int>(CManager::Scroll()->Get_ScrollX());
			int iScrollY = static_cast<int>(CManager::Scroll()->Get_ScrollY());
			GdiTransparentBlt(hDC,
				static_cast<int>(_fX) + _sizeX * i + iScrollX,
				static_cast<int>(_fY) + iScrollY,
				_sizeX,
				_sizeY,
				hMemDC,
				0, 0,
				15, 19,
				RGB(255, 0, 255));
		}

	}

	*_fNextX = _fX + _sizeX * str.size() + str.size();
}

void CUIMgr::View_Weapon_Slot(HDC hDC)
{
	size_t equipSize = CManager::User()->Get_Equip().size();
	for (size_t i = 0; i < equipSize; ++i)
	{
		if (i >= WEAPON_SLOT_CNT) break;

		HDC	hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Equip(CManager::User()->Get_Equip()[i]));

		GdiTransparentBlt(hDC,
			static_cast<int>(UIPos::Weapon_Slot(i).x) + 5,
			static_cast<int>(UIPos::Weapon_Slot(i).y) + 5,
			56,
			56,
			hMemDC,
			0, 0,
			56, 56,
			RGB(255, 0, 255));
	}
}

void CUIMgr::View_Item_Slot(HDC hDC)
{
	size_t itemSize = CManager::User()->Get_Item().size();
	int iRealPosIndex = 0; //아이템 수량이 1 이상일때 위치할 인덱스
	for (size_t i = 0; i < itemSize; ++i)
	{
		if (iRealPosIndex >= Item_SLOT_CNT)
			break;

		int iItemCnt = CManager::User()->Get_Item()[i].second;
		if (iItemCnt <= 0)
			continue;

		HDC	hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Item(CManager::User()->Get_Item()[i].first));
		float posX = dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->Get_Infos(iRealPosIndex).fX;
		float posY = dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->Get_Infos(iRealPosIndex).fY;

		GdiTransparentBlt(hDC,
			static_cast<int>(posX) + 7,
			static_cast<int>(posY) + 5,
			52,
			52,
			hMemDC,
			0, 0,
			56, 56,
			RGB(255, 0, 255));

		float fTemp(0.f);
		NumberRender(iItemCnt, 15, 20, posX + 50.f, posY + 30.f, &fTemp, false, hDC, false);

		++iRealPosIndex;
	}
}

void CUIMgr::Init_Structure_Buttons_Position()
{
	m_CurSelectMainStructureBtn = { ST_END,false };
	m_CurSelectSubStructureBtn = { SST_END,false };

	for (size_t main = 0; main < ST_END; ++main) {
		UIPOS mainPos = UIPos::Main_Structure_Button(main, static_cast<int>(ST_END));
		m_pMainStructure[main].back()->Set_Pos(mainPos.x, mainPos.y);

		for (size_t sub = 0; sub < SST_END; ++sub) {
			 //초기값은 서브 버튼이 메인버튼뒤에 숨어있게 <-nono 그냥 화면 밖으로
			m_pSubStructure[main][sub].back()->Set_Pos(mainPos.x +1000.f, mainPos.y);
		}
	}

	if (!m_pUIList[UI_BUILDING_PREVIEW].empty())
	{
		Delete_Obj(UI_BUILDING_PREVIEW);
	}
}







void CUIMgr::Move_Frame()
{
	if (m_dwSkillWindowTime + 100 < (DWORD)GetTickCount64())
	{
		++m_iSkillWindowMotion;

		if (m_iSkillWindowMotion > 9)
			m_iSkillWindowMotion = 0;

		m_dwSkillWindowTime = (DWORD)GetTickCount64();

	}
}