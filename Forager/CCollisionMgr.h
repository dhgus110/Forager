#pragma once

#include "CObj.h"
#include "CUI.h"
#include <vector>

class CCollisionMgr
{
public:
	static void	Collision_Rect(list<CObj*> DstList, list <CObj*> SrcList);
	static void	Collision_RectEx(list<CObj*> DstList, list <CObj*> SrcList);
	static bool	Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);
	static void	Collision_Circle(list<CObj*> DstList, list <CObj*> SrcList);
	static bool	Intersect_Circle(CObj* pDst, CObj* pSrc);



	//보스
	static void Collision_Boss(list<CObj*> Player, list<CObj*> Boss, list<CUI*> DstList);
	static bool Check_Boss_Find_Player(CObj* pDst, CObj* pSrc);
	static bool Check_Boss_Player(CObj* pDst, CObj* pSrc, float* pX, float* pY);
	static bool Check_Player_AttackRange(CObj* pPlayer, CObj* pMon, CUI* pMouse);

	//플레이어 바른길만 갈 수 있도록 플레이어 기준 5x5 만 계산함
	static void Collision_Player_Path(list<CObj*> Player, vector<CObj*> Tile);
	static bool Check_Player_Path(CObj* pPlayer, CObj* pTile,float* pX, float* pY);


	//플레이어와 자원 통과 못하게
	static void Collision_Player_Resource(list<CObj*> DstList, vector<pair<int, CObj*>> SrcList);
	static bool Check_Player_Resource(CObj* pDst, CObj* pSrc, float* pX, float* pY);

	//플레이어가 자원 근처에서 마우스 클릭으로 자원캐기
	static void Collision_Mouse_Resource(list<CObj*> player, list<CUI*> DstList, vector<pair<int, CObj*>> SrcList);
	static bool Check_Mouse_Resource(CObj* pPlayer, CUI* pDst, CObj* pSrc);

	//플레이어와 마우스로 아이템 먹기
	static void Collision_DropItem(list<CObj*> player, list<CUI*> DstList, list<CObj*> dropItem);
	static bool Check_DropItem(CObj* pPlayer, CUI* pDst, CObj* pSrc);

	//플레이어와 건물간의 상호 작용
	static void Collision_Interaction(list<CObj*> player, list<CObj*> Building);
	static int Check_Interaction(CObj* pPlayer, CObj* pBuilding);

	//메뉴 탭 선택
	static void Collision_SubMenuButton(list<CUI*> mouse, list<CUI*> subMenuBtn);
	static bool Check_SubMenuButton(CUI* mouse, CUI* btn, int* select);

	//아이템 슬롯 선택
	static void Collision_ItemSlot(list<CUI*> mouse, list<CUI*> ItemMenu, CUI* pTooltip);
	static bool Check_ItemSlot(CUI* mouse, CUI* slot, int* select);


	//장비창 효과들
	static void Collision_Equip(list<CUI*> mouse, list<CUI*> EquipTab);
	static bool Check_Equip(CUI* mouse, CUI* obj, int* iOption);

	//스킬 버튼들
	static void Collision_Skill(list<CUI*> mouse, list<CUI*>* Skills);
	static bool Check_Skill(CUI* mouse, CUI* skill);

	//건설 버튼들
	static void Collision_Structure(list<CUI*> mouse, list<CUI*>* MainStructure, list<CUI*> SubStructure[ST_END][SST_END]);

	//토지 구입 창 깃발 콜리젼
	static void Collision_BuyIsland(list<CUI*> mouse, list<CUI*> flag);
	static bool Check_Island(CUI* mouse, CUI* flag);

	//거래창 슬롯들
	static void Collision_TradeSlot(list<CUI*> mouse, list<CUI*> Slot, CUI* pTooltip);
	static bool Check_TradeSlot(CUI* mouse, CUI* slot);

};

