#include "pch.h"
#include "CSpawner.h"
#include "CAbstractFactory.h"
#include "CTile.h"
#include "CManager.h"
#include "Extension.h"
#include "CDropItem.h"
#include "CCommonHpBar.h"

CSpawner* CSpawner::m_pInstance = nullptr;
CSpawner::CSpawner() : m_iResourceCount(0)
{
}

CSpawner::~CSpawner()
{
	Release();
}

void CSpawner::Initialize()
{
	m_vecCopyIsland = CManager::User()->Get_Island();

	//보스 섬은 초기 자원 없음 
	for (int i = 0 ; i< m_vecCopyIsland.size() - 1; ++i)
	{
		int iRandSpawnCnt = Random::GetInt(4, 7);
		if (i == 0)iRandSpawnCnt = 14;
			for (int j = 0; j < iRandSpawnCnt; ++j)
				ResourceSpawn(i);
	}

}

void CSpawner::Update()
{
	for (int i = 0; i < m_vecCopyIsland.size(); ++i) {
		if (CManager::User()->Get_IsBuyIsland(i)) {
			for (auto res = m_vecResource[i].begin(); res != m_vecResource[i].end();)
			{
				//자원을 다 캘 때
				if ( (*res).second->Update() == OBJ_DEAD )
				{
					//아이템 드롭을 위한 위치 및 자원 종류를 저장
					float fX = (*res).second->Get_Info()->fX;
					float fY = (*res).second->Get_Info()->fY;
					RESOURCEID id = dynamic_cast<CResources*>((*res).second)->Get_ResourceId();

					//베터에 드롭된 아이템 삭제
					SafeDelete<CObj*>((*res).second);
					res = m_vecResource[i].erase(res);

					//아이템 드롭
					int iRandCnt = Random::GetInt(1, 4);
					for(int i = 0 ; i <iRandCnt ; ++i)
					{
						CObj* pObj = CAbstractFactory<CDropItem>::Create(fX, fY);
						CManager::Obj()->Add_Object(OBJ_DROPITEM, pObj);
						dynamic_cast<CDropItem*>(pObj)->DropResourceItem(id, 0);
					}
					CObj* pObj = CAbstractFactory<CDropItem>::Create(fX, fY);
					CManager::Obj()->Add_Object(OBJ_DROPITEM, pObj);
					dynamic_cast<CDropItem*>(pObj)->DropResourceItem(id, 1);

					//플레이어 경험치 업
					CManager::User()->Set_Exp();

				}
				else 
				{
					++res;
				}
			}
		}
	}


}

void CSpawner::Late_Update()
{

	for (int i = 0; i < m_vecCopyIsland.size(); ++i) {
		if (CManager::User()->Get_IsBuyIsland(i)) {
			for (auto res : m_vecResource[i])
				dynamic_cast<CResources*>(res.second)->Late_Update();
		}
	}

}

void CSpawner::Render(HDC hDC)
{

	for (int i = 0; i < m_vecCopyIsland.size(); ++i) {
		if (CManager::User()->Get_IsBuyIsland(i)) {
			for (auto res : m_vecResource[i])
				dynamic_cast<CResources*>(res.second)->Render(hDC);
		}
	}

}

void CSpawner::Release()
{
	for(int i = 0 ; i<9 ;++i)
	{
		for (auto& pair : m_vecResource[i])
			SafeDelete(pair.second);
		m_vecResource[i].clear();
	}

}

const bool CSpawner::Find_Resource(int iIndex, int iIsland)
{
	auto it = find_if(m_vecResource[iIsland].begin(), m_vecResource[iIsland].end(),
		[iIndex](const  pair<int, CObj*> elem) {return elem.first == iIndex; });

	if (it != m_vecResource[iIsland].end()) return true;
	return false;
}

void CSpawner::ResourceSpawn(int _iIsLand)
{
	while (true) {

		//좌표 , 인덱스
		int iRandX = Random::GetInt(m_vecCopyIsland[_iIsLand].iMinX + 1, m_vecCopyIsland[_iIsLand].iMaxX - 1);
		int iRandY = Random::GetInt(m_vecCopyIsland[_iIsLand].iMinY + 1, m_vecCopyIsland[_iIsLand].iMaxY);
		int iIndex = iRandY * TILEX + iRandX;

		// 자원 종류
		int iRandResource = Random::GetInt(0, (int)RE_END - 1);

		//같은 좌표에 뭐가 있는지 체크
		auto it = find_if(m_vecResource[_iIsLand].begin(), m_vecResource[_iIsLand].end(),
			[iIndex](const pair<int, CObj*> elem) {return elem.first == iIndex; });

		//같은 좌표가 있거나 건설 불가능 지역이면 
		if (it != m_vecResource[_iIsLand].end() || dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Get_Option() != 0)
			continue;
	
		CObj* pObj = CAbstractFactory<CResources>::Create(float(iRandX * TILECX + int(TILECX * 0.5f)), float(iRandY * TILECY + int(TILECY * 0.5f)));
		dynamic_cast<CResources*>(pObj)->Set_ResourceId(RESOURCEID(iRandResource), iIndex);
		m_vecResource[_iIsLand].push_back({ iIndex,pObj });

		++m_iResourceCount;

		break;
	}
}

void CSpawner::ResourceSpawn(int _iIsLand, RESOURCEID _id)
{
	while (true) {
		int iRandX = Random::GetInt(m_vecCopyIsland[_iIsLand].iMinX + 1, m_vecCopyIsland[_iIsLand].iMaxX - 1);
		int iRandY = Random::GetInt(m_vecCopyIsland[_iIsLand].iMinY + 1, m_vecCopyIsland[_iIsLand].iMaxY);
		int iIndex = iRandY * TILEX + iRandX;

		auto it = find_if(m_vecResource[_iIsLand].begin(), m_vecResource[_iIsLand].end(),
			[iIndex](const pair<int, CObj*> elem) {return elem.first == iIndex; });

		if (it != m_vecResource[_iIsLand].end() || dynamic_cast<CTile*>(CManager::Tile()->Get_VecTile()[iIndex])->Get_Option() != 0)
			continue;
	
		CObj* pObj = CAbstractFactory<CResources>::Create(float(iRandX * TILECX + int(TILECX * 0.5f)), float(iRandY * TILECY + int(TILECY * 0.5f)));
		dynamic_cast<CResources*>(pObj)->Set_ResourceId(_id, iIndex);
		m_vecResource[_iIsLand].push_back({ iIndex,pObj });
		++m_iResourceCount;
		break;
	}
}
