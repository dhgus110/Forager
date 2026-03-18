#pragma once
#include <vector>
#include "BaseStruct.h"
#include "Enum.h"
#include "CObj.h"

class CUserInfoMgr
{
private:
	CUserInfoMgr();
	CUserInfoMgr(const CUserInfoMgr& rhs) = delete;
	CUserInfoMgr& operator= (CUserInfoMgr& rSrc) = delete;
	~CUserInfoMgr();

public:
	static CUserInfoMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CUserInfoMgr;

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Initialilze();
	void Release();

public:
	const bool& Get_IsBuyIsland(int _i) const { return m_vecIsBuyIsland[_i]; }
	const int Get_OwnIslandCnt()const { int i = 0; for (auto b : m_vecIsBuyIsland)if (b)++i; return i; }
	const vector<ISLAND>& Get_Island() const { return m_vecIsland; }
	const int Get_ResourceHp(RESOURCEID _id) const;
	const vector<pair<ITEMID, int>>& Get_Item() const { return m_vecItem; }
	const pair<ITEMID, int>& Get_Item(int _iIndex) const { return m_vecItem[_iIndex]; }
	const bool Is_Enought_Item(const int* items) const;

	const int Get_PlayerLevel() const { return m_iPlayerLevel ; }
	const float Get_PlayerExpRate() const { return float(m_iPlayerExp) / (float)m_iExpSystem[m_iPlayerLevel];}
	const pair<int, int>& Get_ExpInfo() const { return {m_iPlayerExp , m_iExpSystem[m_iPlayerLevel] }; }
	const int Get_Coin() const { return m_iCoin; }
	const vector<EQUIP>& Get_Equip() const { return m_vecEquip; }
	const pair<bool, bool>& Get_Skill(SKILLID _id) const { return { m_vecSkill[_id].bUnlock, m_vecSkill[_id].bLearnable }; }
	const int Get_SkillPoint() const { return m_iSkillPoint; }
	CObj* Get_CurSelectBuilding() const { return m_pBuilding; }
	
public:
	void Set_IsBuyIsland(int _i) { m_vecIsBuyIsland[_i] = true; } //섬 사기 
	void Set_Item(ITEMID _id, int _i);
	void Set_Exp(int i = 5) { m_iPlayerExp += i; LevelingSystem(); }
	void Set_Coin(int _i) { m_iCoin += _i; }
	void Set_Equip(EQUIP _eq) { m_vecEquip.push_back(_eq); }
	void Set_LeanSkill(SKILLID _id); //스킬 배우기
	void Set_SKillPoint(int _i) { m_iSkillPoint += _i; }
	void Set_CurSelectBuilding(CObj* pObj) { m_pBuilding = pObj; }


private:
	void LevelingSystem();
	void SkillSystem(SKILLID _id); //배운 스킬 동서남북 배울 수 있는 상태로 만들기

private:
	static CUserInfoMgr* m_pInstance;

	vector<bool> m_vecIsBuyIsland;	// 0~8번 째 섬들 개방했는지 안했는지
	vector<ISLAND>	m_vecIsland;	//섬 양끝 좌표들 
	vector <pair<ITEMID, int>> m_vecItem; //소지중인 아이템 정보 <아이템 종류 , 수량>
	vector<EQUIP> m_vecEquip; // 소지중인 장비 저장
	vector<SKILL> m_vecSkill; // 스킬 정보 <스킬 종류, 해금했는지? , 배울 수 있는지 >

	//현재 무슨 건물과 상호작용하고 있는지
	CObj* m_pBuilding;

	//플레이어
	int m_iPlayerLevel;
	int m_iPlayerExp;
	int m_iExpSystem[21];
	int m_iCoin;
	int m_iSkillPoint;
	

	



};

