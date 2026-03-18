#include "pch.h"
#include "CCollisionMgr.h"
#include "CResources.h"
#include "CManager.h"
#include "CPlayer.h"
#include "CWeapon.h"
#include "CDropItem.h"
#include "CAbstractFactory.h"
#include "CCommonHpBar.h"
#include "Data.h"
#include "CSubMenuButton.h"
#include "CItemInventory.h"
#include "CStage.h"
#include "CSkillButtons.h"
#include "CBuildingPreview.h"
#include "CBuilding.h"
#include "CFishTrap.h"
#include "CFlag.h"
#include "CBoss.h"
#include "CBossHpBar.h"
#include "CItemToolTip.h"
#include "CTrade.h"
#include "CTradeSlot.h"
#include "CTradeTooltip.h"
#include "CFurnace.h"
#include "CConstructTooltip.h"
#include "CSoundMgr.h"


void CCollisionMgr::Collision_Rect(list<CObj*> DstList, list<CObj*> SrcList)
{
	RECT		rc{};

	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				Dst->Set_Dead();
				Src->Set_Dead();
			}
		}
	}

}
void CCollisionMgr::Collision_RectEx(list<CObj*> DstList, list<CObj*> SrcList)
{
	float		fWidth(0.f), fHeight(0.f);

	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				// 상, 하 충돌
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
					{
						Dst->Set_PosY(-fHeight);
					}

					// 하 충돌
					else
					{
						Dst->Set_PosY(fHeight);
					}

				}
				// 좌 우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
					{
						Dst->Set_PosX(-fWidth);
					}

					// 우 충돌
					else
					{
						Dst->Set_PosX(fWidth);
					}
				}
			}
		}
	}
}
bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = abs(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float		fHeight = abs(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float		fRadiusX = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_Info()->fCY + pSrc->Get_Info()->fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}
void CCollisionMgr::Collision_Circle(list<CObj*> DstList, list<CObj*> SrcList)
{
	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (Intersect_Circle(Dst, Src))
			{
				//Dst->Set_Dead();
				//Src->Set_Dead();
			}
		}
	}
}
bool CCollisionMgr::Intersect_Circle(CObj* pDst, CObj* pSrc)
{
	float	fRadius = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;

	float	fWidth = abs(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float	fHeight = abs(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_Boss(list<CObj*> Player, list<CObj*> Boss, list<CUI*> Mouse)
{
	float		fWidth(0.f), fHeight(0.f);

	for (auto& pl : Player)
	{
		for (auto& bo : Boss)
		{
			//플레이와 몬스터 충돌 
			if (Check_Boss_Player(pl, bo, &fWidth, &fHeight))
			{
				if (!dynamic_cast<CBoss*>(CManager::Obj()->Get_ObjectBack(OBJ_MONSTER))->Get_CheckAttack())
				{
					if (!dynamic_cast<CBoss*>(bo)->Get_CheckAttack())
					{
						if (fWidth > fHeight)
						{
							//아래로 내려가게 
							pl->Set_PosY(fHeight);
						}
						else
						{
							// 좌 충돌
							if (pl->Get_Info()->fX < bo->Get_Info()->fX)
							{
								pl->Set_PosX(-fWidth);
							}

							// 우 충돌
							else
							{
								pl->Set_PosX(fWidth);
							}
						}
						//todo 피 깍임, 등등 충돌처리

						dynamic_cast<CPlayer*>(pl)->Set_Damaged(dynamic_cast<CBoss*>(bo)->Get_AttackDamage());
					}
				}

			}

			//플레이어가 몬스터 사정거리에 있음 ->몬스터가 플레이어에게 공격 ㄱdㄱ
			if (Check_Boss_Find_Player(pl, bo))
			{
				dynamic_cast<CBoss*>(bo)->Setting_Attack(pl->Get_Info()->fX,pl->Get_Info()->fY);
			}

			//플레이어가 몬스터를 공격하기
			for (auto& mouse : Mouse)
			{
				if (CManager::Key()->Key_Pressing(VK_LBUTTON) && Check_Player_AttackRange(pl, bo, mouse))
				{
					//체력바 연결
					if (dynamic_cast<CBoss*>(bo)->Get_HpBar() == nullptr)
					{
						//초기화
						CUI* pCUI = CAbstractFactory<CBossHpBar>::CreateUI();
						CManager::UI()->AddObject(UI_BOSS_HP, pCUI);
						dynamic_cast<CBossHpBar*>(pCUI)->Setting_Hp((float)dynamic_cast<CBoss*>(bo)->Get_Hp());
						dynamic_cast<CBoss*>(bo)->Set_HpBar(pCUI);
					}

					//플레이어 공격상태 true, 무기한테 타겟 지정 
					if (!dynamic_cast<CPlayer*>(pl)->Get_IsAttack())
					{
						dynamic_cast<CPlayer*>(pl)->Set_IsAttack(true);
						dynamic_cast<CWeapon*>(CManager::Obj()->Get_ObjectBack(OBJ_EQUIP))->Set_TargetMonster(bo);
					}

				}
			}
			
		}
	}
}

bool CCollisionMgr::Check_Boss_Player(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float	fRadius = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;

	float	fWidth = abs(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float	fHeight = abs(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	if (fRadius >= fDiagonal)
	{
		*pX = fRadius - fWidth;
		*pY = fRadius - fHeight;
		return 1;
	}

	return 0;
}

bool CCollisionMgr::Check_Boss_Find_Player(CObj* pDst, CObj* pSrc)
{

	float		fWidth = abs((pDst->Get_Info()->fX + pDst->Get_Info()->fCX * 0.5f) - (pSrc->Get_Info()->fX + pSrc->Get_Info()->fCX * 0.5f));
	float		fHeight = abs((pDst->Get_Info()->fY+ pDst->Get_Info()->fCY * 0.5f ) - (pSrc->Get_Info()->fY +pSrc->Get_Info()->fCY * 0.5f));
	float		fRadiusX = 350.f;
	float		fRadiusY = 350.f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		return true;
	}
	return false;
}

bool CCollisionMgr::Check_Player_AttackRange(CObj* pPlayer, CObj* pMon, CUI* pMouse)
{
	//플레이어와 몬스터 사이
	float		fWidth1 = abs(pPlayer->Get_Info()->fX - pMon->Get_Info()->fX);
	float		fHeight1 = abs(pPlayer->Get_Info()->fY - pMon->Get_Info()->fY);

	float		fRadiusX1 = (pPlayer->Get_Info()->fCX + pMon->Get_Info()->fCX * 0.5f);
	float		fRadiusY1 = (pPlayer->Get_Info()->fCY + pMon->Get_Info()->fCY * 0.5f);

	if ((fRadiusX1 < fWidth1) || (fRadiusY1 < fHeight1))
		return false;

	//마우스와 몬스터 사이
	float ScrollX = CManager::Scroll()->Get_ScrollX();
	float ScrollY = CManager::Scroll()->Get_ScrollY();

	float		fWidth = abs(pMouse->Get_Info()->fX - ScrollX - pMon->Get_Info()->fX);
	float		fHeight = abs(pMouse->Get_Info()->fY - ScrollY - pMon->Get_Info()->fY);

	float		fRadiusX = (pMouse->Get_Info()->fCX + pMon->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (pMouse->Get_Info()->fCY + pMon->Get_Info()->fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
		return true;
	return false;
}

void CCollisionMgr::Collision_Player_Path(list<CObj*> Player,vector<CObj*> Tile)
{
	float		fWidth(0.f), fHeight(0.f);

	for (auto& pl : Player) {
		int curX = static_cast<int>(pl->Get_Info()->fX / (float)TILECX);
		int curY = static_cast<int>(pl->Get_Info()->fY / (float)TILECY);

		int minX = curX - 2 < 0 ? 0 : curX -2;
		int maxX = curX + 2 > TILEX ? TILEX : curX + 2;
		int minY = curY - 2 < 0 ? 0 : curY - 2;
		int maxY = curY + 2 > TILEY ? TILEY : curY + 2;

		for (int x = minX; x <= maxX; ++x) {
			for (int y = minY; y <= maxY; ++y) {
				if(Check_Player_Path(pl, Tile[y * TILEY + x], &fWidth, &fHeight))
				{
					int tileOption = dynamic_cast<CTile*>(Tile[y * TILEY + x])->Get_Option();
					if(tileOption != 0 )
					if (fWidth > fHeight)
					{
						// 상 충돌
						if (pl->Get_Info()->fY < Tile[y * TILEY + x]->Get_Info()->fY)
						{
							pl->Set_PosY(-fHeight);
						}

						// 하 충돌
						else
						{
							pl->Set_PosY(fHeight);
						}

					}
					else

					{
						// 좌 충돌
						if (pl->Get_Info()->fX < Tile[y * TILEY + x]->Get_Info()->fX)
						{
							pl->Set_PosX(-fWidth);
						}

						// 우 충돌
						else
						{
							pl->Set_PosX(fWidth);
						}
					}
				}
			}
		}

	}


}

bool CCollisionMgr::Check_Player_Path(CObj* pPlayer, CObj* pTile, float* pX, float* pY)
{
	float	fRadius = (pPlayer->Get_Info()->fCX + pTile->Get_Info()->fCX) * 0.5f;

	float	fWidth = abs(pPlayer->Get_Info()->fX - pTile->Get_Info()->fX);
	float	fHeight = abs(pPlayer->Get_Info()->fY - pTile->Get_Info()->fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	if (fRadius >= fDiagonal)
	{
		*pX = fRadius - fWidth;
		*pY = fRadius - fHeight;
		return true;
	}

	return false;

}

//자원 못지나가기
void CCollisionMgr::Collision_Player_Resource(list<CObj*> DstList, vector<pair<int, CObj*>> SrcList)
{
	float		fWidth(0.f), fHeight(0.f);

	for (auto& Dst : DstList)
	{
		for (auto& Src : SrcList)
		{
			if (Check_Player_Resource(Dst, Src.second, &fWidth, &fHeight))
			{
				if (dynamic_cast<CResources*>(Src.second)->Get_ResourceId() == RE_BERRY)  continue;
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (Dst->Get_Info()->fY < Src.second->Get_Info()->fY)
					{
						Dst->Set_PosY(-fHeight);
					}

					// 하 충돌
					else
					{
						Dst->Set_PosY(fHeight);
					}

				}
				else
				{
					// 좌 충돌
					if (Dst->Get_Info()->fX < Src.second->Get_Info()->fX)
					{
						Dst->Set_PosX(-fWidth);
					}

					// 우 충돌
					else
					{
						Dst->Set_PosX(fWidth);
					}
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Player_Resource(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{

	//float		fWidth = abs(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	//float		fHeight = abs(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	//float		fRadiusX = (pDst->Get_Info()->fCX + (float) BASE_SIZE) * 0.5f;
	//float		fRadiusY = (pDst->Get_Info()->fCY + (float) BASE_SIZE) * 0.5f;

	//if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	//{
	//	*pX = fRadiusX - fWidth;
	//	*pY = fRadiusY - fHeight;

	//	return true;
	//}
	float	fRadius = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;

	float	fWidth = abs(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float	fHeight = abs(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	if (fRadius >= fDiagonal)
	{
		*pX = fRadius - fWidth;
		*pY = fRadius - fHeight;
		return true;
	}

	return false;
}

//자원 캐기
void CCollisionMgr::Collision_Mouse_Resource(list<CObj*> player, list<CUI*> DstList, vector<pair<int, CObj*>> SrcList)
{
	for (auto& pla : player) {
		for (auto& Dst : DstList)
		{
			for (auto& Src : SrcList)
			{
				if (Check_Mouse_Resource(pla, Dst, Src.second))
				{
					if (CManager::Key()->Key_Pressing(VK_LBUTTON) && !dynamic_cast<CPlayer*>(pla)->Get_IsAttack()) {
						//체력바 연결
						if (dynamic_cast<CResources*>(Src.second)->Get_HpBar()==nullptr)
						{
							//초기화
							CUI* pCUI = CAbstractFactory<CCommonHpBar>::CreateUI(Src.second->Get_Info()->fX, Src.second->Get_Info()->fY);
							CManager::UI()->AddObject(dynamic_cast<CResources*>(Src.second)->Get_TileIndex(), pCUI);
							dynamic_cast<CCommonHpBar*>(pCUI)->Setting_Hp((float)dynamic_cast<CResources*>(Src.second)->Get_Hp());
							dynamic_cast<CResources*>(Src.second)->Set_HpBar(pCUI);
						}


						// 무기에 자원타겟을 주고 무기 딱 내려치는 부분에서 자원 대미지 입히기
						if(Src.second != nullptr)
							dynamic_cast<CWeapon*>(CManager::Obj()->Get_ObjectBack(OBJ_EQUIP))->Set_TargetResource(Src.second);

						//플레이어 공격 및 피 깍임
						dynamic_cast<CPlayer*>(pla)->Set_IsAttack(true);
						dynamic_cast<CPlayer*>(pla)->Set_Hp(-1.f);
			
							
					}

				}
			}
		}
	}
}

bool CCollisionMgr::Check_Mouse_Resource(CObj* pPlayer,CUI* pDst, CObj* pSrc)
{
	float		fWidth1 = abs(pPlayer->Get_Info()->fX - pSrc->Get_Info()->fX);
	float		fHeight1 = abs(pPlayer->Get_Info()->fY - pSrc->Get_Info()->fY);

	float		fRadiusX1 = (pPlayer->Get_Info()->fCX + (float)BASE_SIZE) ;
	float		fRadiusY1 = (pPlayer->Get_Info()->fCY + (float)BASE_SIZE) ;

	if ((fRadiusX1 < fWidth1) || (fRadiusY1 < fHeight1))
		return false;

	float ScrollX =CManager::Scroll()->Get_ScrollX();
	float ScrollY = CManager::Scroll()->Get_ScrollY();


	float		fWidth = abs(pDst->Get_Info()->fX - ScrollX - pSrc->Get_Info()->fX) ;
	float		fHeight = abs(pDst->Get_Info()->fY - ScrollY - pSrc->Get_Info()->fY) ;

	float		fRadiusX = (pDst->Get_Info()->fCX + (float)BASE_SIZE) * 0.5f;
	float		fRadiusY = (pDst->Get_Info()->fCY + (float)BASE_SIZE) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
		return true;
	return false;
}

//드롭 아이템 먹기
void CCollisionMgr::Collision_DropItem(list<CObj*> player, list<CUI*> DstList, list<CObj*> dropItem)
{
	for (auto& pla : player) {
		for (auto& Dst : DstList)
		{
			for (auto& drop : dropItem)
			{
				if (Check_DropItem(pla, Dst, drop))
				{
					CManager::User()->Set_Item(dynamic_cast<CDropItem*>(drop)->Get_ItemId(), 1);
					drop->Set_Dead();

					CSoundMgr::Get_Instance()->StopSound(SOUND_RESOURCE);
					CSoundMgr::Get_Instance()->PlaySound(L"Coin.wav", SOUND_RESOURCE, 0.7f);

				}
			}
		}
	}
}
bool CCollisionMgr::Check_DropItem(CObj* pPlayer, CUI* pDst, CObj* drop)
{
	//if (drop->Get_Dead()) return false;
	if (!dynamic_cast<CDropItem*>(drop)->Get_IsLand())
		return false;

	float		fWidth1 = abs(pPlayer->Get_Info()->fX - drop->Get_Info()->fX);
	float		fHeight1 = abs(pPlayer->Get_Info()->fY - drop->Get_Info()->fY);

	float		fRadiusX1 = pPlayer->Get_Info()->fCX -10.f;
	float		fRadiusY1 = pPlayer->Get_Info()->fCY -10.f;

	if ((fRadiusX1 > fWidth1) && (fRadiusY1 > fHeight1))
		return true;

	float ScrollX = CManager::Scroll()->Get_ScrollX();
	float ScrollY = CManager::Scroll()->Get_ScrollY();


	float		fWidth = abs(pDst->Get_Info()->fX - ScrollX - drop->Get_Info()->fX);
	float		fHeight = abs(pDst->Get_Info()->fY - ScrollY - drop->Get_Info()->fY);

	float		fRadiusX = (pDst->Get_Info()->fCX + (float)BASE_SIZE) * 0.5f;
	float		fRadiusY = (pDst->Get_Info()->fCY + (float)BASE_SIZE) * 0.5f;
	//float		fRadiusX = pDst->Get_Info()->fCX;
	//float		fRadiusY = pDst->Get_Info()->fCY;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
		return true;
	return false;
}

void CCollisionMgr::Collision_Interaction(list<CObj*> player, list<CObj*> Building)
{
	for (auto& pla : player) {
		for (auto& bui : Building)
		{
			STRUCTURE_ITEM_ID id = dynamic_cast<CBuilding*>(bui)->Get_Id();
			//상호 작용 하는 것만 들어오게
			if (id == SI_I_0 || id == SI_I_1 || id == SI_I_2 || id == SI_F_1 || id == SI_E_1)
			{
				int result = Check_Interaction(pla, bui);

				//상호작용 버튼 나옴
				if (result == 1)
				{
					dynamic_cast<CBuilding*>(bui)->Set_Interaction(true);
					CManager::User()->Set_CurSelectBuilding(bui); // 유저인포에 현재 선택한 건물 정보 넘김

					//통발 낚시가 걸렸을 때
					if (id == SI_F_1 && dynamic_cast<CFishTrap*>(bui)->Get_Fishing())
					{
						if (CManager::Key()->Key_Pressing('E'))
						{
							CObj* pObj = CAbstractFactory<CDropItem>::Create(bui->Get_Info()->fX, bui->Get_Info()->fY);
							CManager::Obj()->Add_Object(OBJ_DROPITEM, pObj);

							dynamic_cast<CDropItem*>(pObj)->DropFishTrap();

							dynamic_cast<CFishTrap*>(bui)->Set_Fishing(false);

							//CSoundMgr::Get_Instance()->StopSound(SOUND_STRUCTURE);
							//CSoundMgr::Get_Instance()->PlaySound(L"Select.wav", SOUND_STRUCTURE, 0.7f);
					

						}
					}
					//용광로
					else if (id == SI_I_0 && CManager::Key()->Key_Pressing('E'))
					{
						for (auto& it : *CManager::UI()->Get_ObjectList(UI_TRADE))
						{
							CTrade* pTrade = dynamic_cast<CTrade*>(it);
							auto a = pTrade->Get_Title();
							if (pTrade->Get_Title() != SI_I_0) continue;

							pTrade->Set_OnOff(true);
						}


					}

					//모루
					else if (id == SI_I_1 && CManager::Key()->Key_Pressing('E'))
					{
						for (auto& it : *CManager::UI()->Get_ObjectList(UI_TRADE))
						{
							CTrade* pTrade = dynamic_cast<CTrade*>(it);
							auto a = pTrade->Get_Title();
							if (pTrade->Get_Title() != SI_I_1) continue;

							pTrade->Set_OnOff(true);
						}


					}
				}

				//상호작용 버튼 숨김
				else if (result == 2)
				{
					dynamic_cast<CBuilding*>(bui)->Set_Interaction(false);
					CManager::User()->Set_CurSelectBuilding(nullptr); //유저정보에 현재 선택한 건물이 없다고 알림
				}
			}
		}
	}

}

int CCollisionMgr::Check_Interaction(CObj* pPlayer, CObj* pBuilding)
{
	float		fWidth = abs(pPlayer->Get_Info()->fX - (pBuilding->Get_Info()->fX));
	float		fHeight = abs(pPlayer->Get_Info()->fY - (pBuilding->Get_Info()->fY));
	float		fRadiusX = 110.f;
	float		fRadiusY = 110.f;

	//진입했을 때
	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
		return 1;
	
	//빠져나왔을 때
	else if (((fRadiusX <= fWidth) && (fWidth < fRadiusX + 10.f )) ||  ((fRadiusY <= fHeight) && (fHeight < fRadiusY + 10.f )))
		return 2;

	//아무것도 아닐 때 
	return 0;
}

void CCollisionMgr::Collision_SubMenuButton(list<CUI*> mouse, list<CUI*> subMenuBtn)
{
	int select(0);
	for (auto& mo : mouse) {
		for (auto& btn : subMenuBtn)
		{
			if (Check_SubMenuButton(mo, btn, &select)) {
				dynamic_cast<CSubMenuButton*>(btn)->Set_Inactive(select);

				if (CManager::Key()->Key_Pressing(VK_LBUTTON))
				{
					dynamic_cast<CSubMenuButton*>(btn)->Set_Active(select);
					btn->Start_Pulse(btn->Get_Info()->fCX, btn->Get_Info()->fCY);

					//장비
					if (select == 0) 
					{
						dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->MoveToSlot(100.f, 0.f, -500.f);
						CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_TOOLTIP)->MoveToPosition((float)WINCX + 10.f, 100.f, 500.f);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_INVEN, true);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_SLOT, true);
						CManager::UI()->Set_IsUIView(UI_MENU_Skill_BTN, true);
						CManager::UI()->Set_StructureView(false);
						CManager::UI()->Init_Structure_Buttons_Position();
						dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Set_MenuDarkLight(true);
						CManager::UI()->Set_Island_Flag(false);
						dynamic_cast<CConstructTooltip*>(CManager::UI()->Get_ObjectBack(UI_BUILDING_TOOLTIP))->Reset();

					}

					//아이템
					else if(select ==1)
					{
						dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->ReturnToOriginalSlotPos(200.f);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_INVEN, false);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_SLOT, false);
						CManager::UI()->Set_IsUIView(UI_MENU_Skill_BTN, false);
						CManager::UI()->Set_StructureView(false);
						CManager::UI()->Init_Structure_Buttons_Position();
						dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Set_MenuDarkLight(true);
						CManager::UI()->Set_Island_Flag(false); dynamic_cast<CConstructTooltip*>(CManager::UI()->Get_ObjectBack(UI_BUILDING_TOOLTIP))->Reset();



					}

					//건설
					else if (select == 2)
					{
						CManager::UI()->Set_StructureView(true);
						dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Set_MenuDarkLight(false);

						dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->MoveToSlot(100.f, 0.f, -500.f);
						CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_TOOLTIP)->MoveToPosition((float)WINCX + 10.f, 100.f, 500.f);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_INVEN, false);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_SLOT, false);
						CManager::UI()->Set_IsUIView(UI_MENU_Skill_BTN, false);
						CManager::UI()->Set_Island_Flag(false);


					}

					//토지 구입
					else if (select == 3)
					{
						CManager::UI()->Set_Island_Flag(true);
						dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Set_MenuDarkLight(false);

						dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->MoveToSlot(100.f, 0.f, -500.f);
						CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_TOOLTIP)->MoveToPosition((float)WINCX + 10.f, 100.f, 500.f);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_INVEN, false);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_SLOT, false);
						CManager::UI()->Set_IsUIView(UI_MENU_Skill_BTN, false);
						CManager::UI()->Set_StructureView(false);
						CManager::UI()->Init_Structure_Buttons_Position();
						dynamic_cast<CConstructTooltip*>(CManager::UI()->Get_ObjectBack(UI_BUILDING_TOOLTIP))->Reset();
					}

					//설정
					else if (select == 4)
					{

						dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->MoveToSlot(100.f, 0.f, -500.f);
						CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_TOOLTIP)->MoveToPosition((float)WINCX + 10.f, 100.f, 500.f);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_INVEN, false);
						CManager::UI()->Set_IsUIView(UI_MENU_WEAPON_SLOT, false);
						CManager::UI()->Set_IsUIView(UI_MENU_Skill_BTN, false);
						CManager::UI()->Set_StructureView(false);
						CManager::UI()->Init_Structure_Buttons_Position();
						dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Set_MenuDarkLight(true);
						CManager::UI()->Set_Island_Flag(false);
						dynamic_cast<CConstructTooltip*>(CManager::UI()->Get_ObjectBack(UI_BUILDING_TOOLTIP))->Reset();


					}
				}

			}
			else
				dynamic_cast<CSubMenuButton*>(btn)->Set_Inactive();

		}
	}
}

bool CCollisionMgr::Check_SubMenuButton(CUI* mouse, CUI* btn ,int* select)
{
	for (int i = 0; i < 5; ++i) 
	{
		UIPOS pos = UIPos::SubMenu(i);

		float		fWidth = abs(mouse->Get_Info()->fX - (UIPos::SubMenu(i).x + btn->Get_Info()->fCX * 0.5f));
		float		fHeight = abs(mouse->Get_Info()->fY  - (UIPos::SubMenu(i).y + btn->Get_Info()->fCY * 0.5f));
		float		fRadiusX = (mouse->Get_Info()->fCX + btn->Get_Info()->fCX) * 0.5f;
		float		fRadiusY = (mouse->Get_Info()->fCY + btn->Get_Info()->fCY) * 0.5f;

		if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
		{
			*select = i;
			return true;
		}

	}
	return false;
}

void CCollisionMgr::Collision_ItemSlot(list<CUI*> mouse, list<CUI*> ItemMenu, CUI* pTooltip)
{
	if (dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Get_CurScreen() != 1 ||
		dynamic_cast<CSubMenuButton*>(CManager::UI()->Get_ObjectBack(UI_MENU_TAP_SUB))->Get_CurMenu() != 1)return;
	int select(0); //몇 번칸에

	for (auto& mo : mouse) 
	{
		for (auto& slot : ItemMenu)
		{

			if (Check_ItemSlot(mo, slot, &select))
			{

				if (CManager::Key()->Key_Pressing(VK_LBUTTON))
				{
					//버튼 누르면 아이템창 이동
					dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->MoveToSlot(5.f, -139.f, 0.f);
					CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_TOOLTIP)->ReturnToOriginalPos();

					//설명창에 아이템 정보 넘겨주기
					size_t itemSize = CManager::User()->Get_Item().size();
					int iRealPosIndex = 0; //아이템 수량이 1 이상일때 위치할 인덱스
					for (size_t i = 0; i < itemSize; ++i)
					{
						if (iRealPosIndex >= Item_SLOT_CNT)
							break;

						int iCnt = CManager::User()->Get_Item()[i].second;
						if (iCnt <= 0)
							continue;
						if (iRealPosIndex == select)
						{
							dynamic_cast<CItemToolTip*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_TOOLTIP))
								->Set_ItemID(CManager::User()->Get_Item()[i].first);
							break;
						}
						++iRealPosIndex;
					}

				}
				//커서가 가리키는 버튼 크기 확장
				dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->Set_Extand(select);
				CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT)->Start_Pulse(72.f, 72.f,1.2f);

			}

			//마우스 설명창보다 위 아래로 이동해서 빠져나가면 다시 원 위치로 (+ 아이템 선택했는데 아이템 수량이 0이하이면)
			if (mo->Get_Info()->fY < 100.f || mo->Get_Info()->fY>500.f)
			{
				CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_TOOLTIP)->MoveToPosition((float)WINCX + 10.f, 100.f, 500.f);
				dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->MoveToSlot(5.f, 0.f, 0.f);
			}
		}

		//설명창 떠 있고 사용하기 버튼 있을 때
		if (dynamic_cast<CItemToolTip*>(pTooltip)->Get_UseBtn())
		{
			//버튼 위치임. 버튼에 마우스 커서가 있고 , 눌렀을 때 (체력 올려주는 아이템)
			if (822.f <= mo->Get_Info()->fX && mo->Get_Info()->fX <= 962.f && 400.f <= mo->Get_Info()->fY && mo->Get_Info()->fY <= 462.f
				&& CManager::Key()->Key_Pressing(VK_LBUTTON)&& !dynamic_cast<CItemToolTip*>(pTooltip)->Get_CheckUseBtn())
			{
				//아이템 수량 -1 , 플레이어 체력 + 
				ITEMID id = dynamic_cast<CItemToolTip*>(pTooltip)->Get_ItemID();
				CManager::User()->Set_Item(id, -1);
				dynamic_cast<CPlayer*>(CManager::Obj()->Get_ObjectBack(OBJ_PLAYER))->Set_Hp(Heal_Item_Power(static_cast<int>(id)));

				//사운드
				CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"Heal.wav", SOUND_EFFECT, 0.7f);

			}
		}
	}
}

bool CCollisionMgr::Check_ItemSlot(CUI* mouse, CUI* slot, int* select)
{
	for (int y = 0; y < 3; ++y)
	{
		for (int x = 0; x < 8; ++x)
		{
			int iIndex = x + y * 8;

			INFO pos = dynamic_cast<CItemInventory*>(CManager::UI()->Get_ObjectBack(UI_MENU_ITEM_SLOT))->Get_Infos(iIndex);
			float		fWidth = abs(mouse->Get_Info()->fX - (pos.fX + slot->Get_Info()->fCX * 0.5f));
			float		fHeight = abs(mouse->Get_Info()->fY - (pos.fY + slot->Get_Info()->fCY * 0.5f));
			float		fRadiusX = (mouse->Get_Info()->fCX + slot->Get_Info()->fCX) * 0.5f;
			float		fRadiusY = (mouse->Get_Info()->fCY + slot->Get_Info()->fCY) * 0.5f;

			if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
			{
				*select = iIndex;
				return true;
			}

		}
	}
	return false;
}

void CCollisionMgr::Collision_Equip(list<CUI*> mouse, list<CUI*> EquipTab)
{
	if (dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Get_CurScreen() != 1 ||
		dynamic_cast<CSubMenuButton*>(CManager::UI()->Get_ObjectBack(UI_MENU_TAP_SUB))->Get_CurMenu() != 0) return;
	int iOption(0);

	for (auto& mo : mouse)
	{
		for (auto& eq : EquipTab)
		{
			if (Check_Equip(mo, eq , &iOption))
			{
				if(!eq->Get_IsPulse())
				eq->Start_Pulse(eq->Get_Info()->fCX, eq->Get_Info()->fCY,1.1f,1.0f,0.1f);

				if (CManager::Key()->Key_Pressing(VK_LBUTTON) && iOption == 1) {
					CManager::UI()->Set_SkillView(true);
					dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Set_CurScreen(2);
				}
			}

		}
	}
}

bool CCollisionMgr::Check_Equip(CUI* mouse, CUI* obj, int* iOption)
{
	float		fWidth = abs(mouse->Get_Info()->fX - (obj->Get_Info()->fX + obj->Get_Info()->fCX * 0.5f));
	float		fHeight = abs(mouse->Get_Info()->fY - (obj->Get_Info()->fY + obj->Get_Info()->fCY * 0.5f));
	float		fRadiusX = (mouse->Get_Info()->fCX + obj->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (mouse->Get_Info()->fCY + obj->Get_Info()->fCY) * 0.5f;

	//스킬 버튼이면
	if (UIPos::SkillBtn.x == obj->Get_Info()->fX && UIPos::SkillBtn.y == obj->Get_Info()->fY)
		*iOption = 1;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		return true;
	}
	return false;
}

void CCollisionMgr::Collision_Skill(list<CUI*> mouse, list<CUI*>* Skills)
{
	if (dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Get_CurScreen() != 2 ) return;


	for (auto& mo : mouse)
	{
		for (size_t i = 0; i < SK_END; ++i)
		{
			for (auto& skill : Skills[i])
			{
				if (Check_Skill(mo, skill))
				{
					if (!skill->Get_IsPulse())
						skill->Start_Pulse(skill->Get_Info()->fCX, skill->Get_Info()->fCY,1.1f,1.0f,0.2f,false );
					SKILLID id = dynamic_cast<CSkillButtons*>(skill)->Get_ID();
					if (CManager::User()->Get_Skill(id).second &&
						CManager::Key()->Key_Pressing(VK_LBUTTON) &&
						CManager::User()->Get_SkillPoint() > 0)
					{
						CManager::User()->Set_LeanSkill(id);
						dynamic_cast<CSkillButtons*>(skill)->Start_Effect();
					}
				}

			}
		}
	}
}

bool CCollisionMgr::Check_Skill(CUI* mouse, CUI* skill)
{
	float		fWidth = abs(mouse->Get_Info()->fX - (skill->Get_Info()->fX + skill->Get_Info()->fCX * 0.5f));
	float		fHeight = abs(mouse->Get_Info()->fY - (skill->Get_Info()->fY + skill->Get_Info()->fCY * 0.5f));
	float		fRadiusX = (mouse->Get_Info()->fCX + skill->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (skill->Get_Info()->fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		return true;
	}
	return false;
}

void CCollisionMgr::Collision_Structure(list<CUI*> mouse, list<CUI*>* MainStructure, list<CUI*> SubStructure[ST_END][SST_END])
{
	if (dynamic_cast<CStage*>(CManager::Scene()->Get_Scene())->Get_CurScreen() != 1 ||
		!CManager::UI()->Get_StructureView()) return;

	for (auto& mo : mouse) {
		for (size_t i = 0; i < ST_END; ++i) {
			//메인 버튼 눌렸을 때 (Check_Skill은 어차피 안에 똑같이 쓰느깐 이거 썻음...)
			if (Check_Skill(mo, MainStructure[i].back())) {

				MainStructure[i].back()->Start_Pulse(
					MainStructure[i].back()->Get_Info()->fCX,
					MainStructure[i].back()->Get_Info()->fCY,
					1.1f);

				if (CManager::Key()->Key_Pressing(VK_LBUTTON))
				{
					if (CManager::UI()->Get_Structure_Time() + 400 < (DWORD)GetTickCount64())
					{

						//다른 버튼들 누르면 툴팁 사라지게
						dynamic_cast<CConstructTooltip*>(CManager::UI()->Get_ObjectBack(UI_BUILDING_TOOLTIP))->Reset();

						CManager::UI()->Set_Structure_Time();
						//같은 버튼을 눌렀다면 버튼들 원래위치로
						if (CManager::UI()->Get_CurSelectMainStructureBtn().first == static_cast<MAIN_STRUCTURE_TYPE>(i)) {
							CManager::UI()->Init_Structure_Buttons_Position();

						}

						//이미 누른적 있고 다른 버튼을 눌렀다면 
						else
						{
							CManager::UI()->Init_Structure_Buttons_Position(); //일단 버튼 초기화 후

							//버튼 위치 조정
							for (size_t main = 0; main < ST_END; ++main) {
								MainStructure[main].back()->Set_Pos(UIPos::Main_Structure_Button(main, i).x, UIPos::Main_Structure_Button(main, i).y);
								for (size_t sub = 0; sub < SST_END; ++sub) {
									if (i == main) {
										SubStructure[main][sub].back()->Set_Pos(UIPos::Sub_Structure_Button(main, sub).x, UIPos::Sub_Structure_Button(main, sub).y);
									}
									else
									{
										SubStructure[main][sub].back()->Set_Pos(UIPos::Main_Structure_Button(main, i).x, UIPos::Main_Structure_Button(main, i).y);

									}
								}
							}
							//버튼 뭐 눌렀는지 저장
							CManager::UI()->Set_CurSelectMainStructureBtn(static_cast<MAIN_STRUCTURE_TYPE>(i), true);
						}
					}

				}
			}

			// 메인 버튼 클릭 처리 후... 서브 버튼 충돌 처리
			// 메인 버튼이 눌렸다면
			if (CManager::UI()->Get_CurSelectMainStructureBtn().second)
			{
				MAIN_STRUCTURE_TYPE mainType = CManager::UI()->Get_CurSelectMainStructureBtn().first;
				for (size_t sub = 0; sub < SST_END; ++sub) {

					//서브 버튼, 마우스와 충돌 지점 
					if (Check_Skill(mo, SubStructure[mainType][sub].back())) {
						// 서브 버튼에 대한 처리 (하이라이트, 펄스 효과 등)
						SubStructure[mainType][sub].back()->Start_Pulse(
							SubStructure[mainType][sub].back()->Get_Info()->fCX,
							SubStructure[mainType][sub].back()->Get_Info()->fCY,
							1.1f);

						//툴팁 Show
						STRUCTURE_ITEM_ID curID = (STRUCTURE_ITEM_ID)(mainType * 5 + sub);
						CConstructTooltip* pTip = dynamic_cast<CConstructTooltip*>(CManager::UI()->Get_ObjectBack(UI_BUILDING_TOOLTIP));
						if (pTip->Get_BuildingID() != curID)
							pTip->Set_Building(curID);

						if (CManager::Key()->Key_Pressing(VK_LBUTTON)) {
							//서브 버튼 누르면 툴팁 사라지게
							pTip->ResetTimer();

							int a = CManager::UI()->Get_ObjectList(UI_BUILDING_PREVIEW)->size();

							if (CManager::UI()->Get_Structure_Time() + 400 < (DWORD)GetTickCount64())
							{
								if (CManager::UI()->Get_CurSelectSubStructureBtn().second)
								{
									if (!CManager::UI()->Get_Empty(UI_BUILDING_PREVIEW))
										CManager::UI()->Get_ObjectBack(UI_BUILDING_PREVIEW)->Set_Dead();
									CManager::UI()->Set_CurSelectSubStructureBtn(SST_END, false);
								}

								CManager::UI()->Set_Structure_Time();
								// 서브 버튼 클릭 시 건물 사이즈를 주기 위함
								int iSizeX(2), iSizeY(2);

								// 다리랑 통발
								if (mainType == (int)ST_FARMING)
								{
									iSizeX = 1;
									iSizeY = 1;
								}
								//등대
								if (mainType == (int)ST_ECONOMY && sub == SST_3)
									iSizeY = 3;

								//프리뷰 건물 UI 생성, (-100.f위치가 없으면 0,0에 잠깐 생겼다가 마우스로 이동하니깐 넣어줌)
								CManager::UI()->AddObject(UI_BUILDING_PREVIEW, CAbstractFactory<CBuildingPreview>::CreateUI(-100.f, -100.f));
								dynamic_cast<CBuildingPreview*>(CManager::UI()->Get_ObjectBack(UI_BUILDING_PREVIEW))->Setting(curID, iSizeX, iSizeY);

								//서브 버튼 선택 됐다고 저장하기
								CManager::UI()->Set_CurSelectSubStructureBtn(static_cast<SUB_STRUCTURE_TYPE>(sub), true);
							}
						}
					}
					else
					{
						//CConstructTooltip* pTip = dynamic_cast<CConstructTooltip*>(CManager::UI()->Get_ObjectBack(UI_BUILDING_TOOLTIP));
						//if (pTip->Get_BuildingID() != SI_END)
						//	pTip->Reset();

					}
				}
			}
		}
	}

}

void CCollisionMgr::Collision_BuyIsland(list<CUI*> mouse, list<CUI*> flag)
{
	if (!CManager::UI()->Get_IslandFlag()) return;

	for (auto& mo : mouse)
	{
			for (auto& fl : flag)
			{
				//마우스가 깃발에 닿기만 하면 되니깐 체크스킬과 동일
				if (Check_Island(mo, fl))
				{
					int id = dynamic_cast<CFlag*>(fl)->Get_IslandId();
					int cost = eunmToint_IslandsCost(id);
					if (CManager::Key()->Key_Pressing(VK_LBUTTON))
					{
						if (!CManager::User()->Get_IsBuyIsland(id) && CManager::User()->Get_Coin() >= cost)
						{
							CManager::User()->Set_Coin(-cost);
							CManager::User()->Set_IsBuyIsland(id);

							//보스 생성
							if (id == 8)
							{
								auto res = CManager::User()->Get_Island()[8];
								float fX = static_cast<float>(res.iMinX * TILECX + ((res.iMaxX - res.iMinX) / 2) * TILECX);
								float fY = static_cast<float>(res.iMinY * TILECY + ((res.iMaxY - res.iMinY) / 2 - 3) * TILECY);

								CManager::Obj()->Add_Object(OBJ_MONSTER, CAbstractFactory<CBoss>::Create(fX, fY));

							}

							CSoundMgr::Get_Instance()->StopSound(SOUND_EFFECT);
							CSoundMgr::Get_Instance()->PlaySound(L"Buy_Land.wav", SOUND_EFFECT, 0.7f);

						}

					}
				}

			}
	
	}

}

bool CCollisionMgr::Check_Island(CUI* mouse, CUI* flag)
{
	float fScrollX = static_cast<float>(CManager::Scroll()->Get_ScrollX());
	float fScrollY = static_cast<float>(CManager::Scroll()->Get_ScrollY());


	float		fWidth = abs((mouse->Get_Info()->fX - fScrollX) - (flag->Get_Info()->fX + flag->Get_Info()->fCX * 0.5f));
	float		fHeight = abs((mouse->Get_Info()->fY - fScrollY) - (flag->Get_Info()->fY + flag->Get_Info()->fCY * 0.5f));
	float		fRadiusX = (mouse->Get_Info()->fCX + flag->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (flag->Get_Info()->fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		return true;
	}
	return false;
}

void CCollisionMgr::Collision_TradeSlot(list<CUI*> mouse, list<CUI*> Slot, CUI* pTooltip)
{
	for (auto& mo : mouse)
	{
		for (auto& sl : Slot)
		{
			if (Check_TradeSlot(mo, sl))
			{
				//슬롯 바운스
				sl->Start_Pulse(sl->Get_Info()->fCX, sl->Get_Info()->fCY,1.1f);

				//툴팁 생김
				if (CManager::Key()->Key_Pressing(VK_LBUTTON))
				{
					//무슨 아이템인지 정보 넘겨주기
					ITEMID id =  dynamic_cast<CTradeSlot*>(sl)->Get_ItemID();
					CTradeTooltip* pTip = dynamic_cast<CTradeTooltip*>(CManager::UI()->Get_ObjectBack(UI_TRADE_FURNACE_TOOLTIP));
					pTip->Set_Item(id);
				}
			}

			// 툴팁이 생겼다면
			if (dynamic_cast<CTradeTooltip*>(pTooltip)->Get_Active())
			{
				//제작 버튼 위치임. 버튼에 마우스 커서가 있고 누르면
				if (460.f <= mo->Get_Info()->fX && mo->Get_Info()->fX <= 600.f && 390.f <= mo->Get_Info()->fY && mo->Get_Info()->fY <= 422.f
					&& CManager::Key()->Key_Pressing(VK_LBUTTON))
				{
					//무슨 건물과 상호작용하고 있는지 
					CObj* pBuilding = CManager::User()->Get_CurSelectBuilding();

					// 상호작용 건물이 없다면 넘김 
					if (pBuilding == nullptr) continue;

					STRUCTURE_ITEM_ID curID = dynamic_cast<CBuilding*>(pBuilding)->Get_Id();

					//일단 용광로만 만듦
					if (curID == SI_I_0)
					{
						//용광로 건물에서 만들 수 있나 체크후 만듦 
						dynamic_cast<CFurnace*>(pBuilding)->Check_Production(dynamic_cast<CTradeTooltip*>(pTooltip)->Get_ItemID());
					}


				}

			}


		}
	}
}

bool CCollisionMgr::Check_TradeSlot(CUI* mouse, CUI* slot)
{
	float		fWidth = abs(mouse->Get_Info()->fX - (slot->Get_Info()->fX + slot->Get_Info()->fCX * 0.5f));
	float		fHeight = abs(mouse->Get_Info()->fY - (slot->Get_Info()->fY + slot->Get_Info()->fCY * 0.5f));
	float		fRadiusX = (mouse->Get_Info()->fCX + slot->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (mouse->Get_Info()->fCY + slot->Get_Info()->fCY) * 0.5f;

	if ((fRadiusX > fWidth) && (fRadiusY > fHeight))
	{
		return true;
	}
	return false;
}


