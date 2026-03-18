#include "pch.h"
#include "CUserInfoMgr.h"
#include "CManager.h"

CUserInfoMgr* CUserInfoMgr::m_pInstance = nullptr;

CUserInfoMgr::CUserInfoMgr()
{

	m_iPlayerExp = 0;
	m_iPlayerLevel = 1;
	m_iCoin = 50;
	m_iSkillPoint = 0;

	m_vecIsBuyIsland.reserve(9);
	m_vecIsBuyIsland.push_back(true);
	for (int i = 0; i < 8; ++i) {
		m_vecIsBuyIsland.push_back(false);
	}

	//m_vecIsland.reserve(9);
	m_vecIsland.push_back({ 14,14,26,26 });
	m_vecIsland.push_back({ 27,14,39,26 });
	m_vecIsland.push_back({ 1,14,13,26 });
	m_vecIsland.push_back({ 14,27,26,39 });
	m_vecIsland.push_back({ 14,1,26,13 });
	m_vecIsland.push_back({ 1,1,13,13 });
	m_vecIsland.push_back({ 1,27,13,39 });
	m_vecIsland.push_back({ 27,27,39,39 });
	m_vecIsland.push_back({ 27,1,39,13 });

	for (int i = 0; i < (int)IT_END; ++i)
		m_vecItem.push_back({ static_cast<ITEMID>(i) , 0 });

	for (int i = 0; i < 21; ++i)
		m_iExpSystem[i] = 20 + i * 4;

	m_vecEquip.push_back(EQ_PICKAX1); //기본 장비 저장

	//기본 스킬 초기화
	for (size_t i = 0; i < SK_END; ++i) {
		bool bUnlock = false;
		bool blean = false;
		if (enumToint_Skill(i) == 0) blean = true;
		m_vecSkill.push_back({ static_cast<SKILLID>(i),bUnlock ,blean });
	}

	m_pBuilding = nullptr;
}

CUserInfoMgr::~CUserInfoMgr()
{
	Release();
}

void CUserInfoMgr::Initialilze()
{
	LevelingSystem();

}

void CUserInfoMgr::Release()
{
}

const int CUserInfoMgr::Get_ResourceHp(RESOURCEID _id) const
{
	switch (_id)
	{
	case RE_BERRY:
		return 1;

	case RE_COAL:
		return 5;

	case RE_GOLD:
		return 5;

	case RE_IRON:
		return 5;

	case RE_STONE:
		return 4;

	case RE_TREE:
		return 4;

	default:
		return 0;
	}
}

const bool CUserInfoMgr::Is_Enought_Item(const int* items) const
{
	for (int i = 0; i < 10; ++i) {
		if (items[i] > 0 && items[i] > m_vecItem[static_cast<ITEMID>(i)].second)
			return false;
	}
	return true;

}

void CUserInfoMgr::Set_Item(ITEMID _id, int _i)
{
	auto it = find_if(m_vecItem.begin(), m_vecItem.end(), [_id](const pair<ITEMID, int> elem) {return elem.first == _id; });

	if (it != m_vecItem.end())
		(*it).second += _i;
}

void CUserInfoMgr::Set_LeanSkill(SKILLID _id)
{
	auto it = find_if(m_vecSkill.begin(), m_vecSkill.end(), [_id](const SKILL elem) {return elem.eId == _id; });

	if (it != m_vecSkill.end())
	{
		(*it).bUnlock = true;
		--m_iSkillPoint;
	}
		


	SkillSystem(_id);
}

void CUserInfoMgr::LevelingSystem()
{
	for (int i = 0; i < 21; ++i)
	{
		if (m_iPlayerLevel == i && m_iPlayerExp >= m_iExpSystem[i]) 
		{ 
			m_iPlayerLevel = i+1;
			m_iPlayerExp = m_iPlayerExp - m_iExpSystem[i];
			++m_iSkillPoint;
		}
	}

}

void CUserInfoMgr::SkillSystem(SKILLID _id)
{
	int skill = int(_id);
	int iX = skill % 8;
	int iY = skill / 8;

	int dx[5] = { 0,0,-1,1,0 };
	int dy[5] = { 1,-1,0,0,0 };

	for (int i = 0; i < 5; ++i)
	{
		int nextX = iX + dx[i];
		int nextY = iY + dy[i];

		if (nextX < 0 || 7 < nextX || nextY < 0 || 7 < nextY)continue;

		m_vecSkill[static_cast<SKILLID>(nextX + nextY * 8)].bLearnable = true;
	}


}

