#include "pch.h"
#include <algorithm>
#include "CObjMgr.h"
#include "CCollisionMgr.h"
#include "Extension.h"
#include "CPlayer.h"
#include "CManager.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;


CObjMgr::CObjMgr()
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update()
{
	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto it = m_pObjList[i].begin(); it != m_pObjList[i].end();) {
			if ((*it)->Update() == OBJ_DEAD)
			{
				SafeDelete<CObj*>(*it);
				it = m_pObjList[i].erase(it);
			}
			else
				++it;
		}
	}
}

void CObjMgr::Late_Update()
{
	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto obj : m_pObjList[i]) {
			obj->Late_Update();
		}
	}

	CCollisionMgr::Collision_Boss(m_pObjList[OBJ_PLAYER], m_pObjList[OBJ_MONSTER], *CManager::UI()->Get_ObjectList(UI_MOUSE));

	CCollisionMgr::Collision_Player_Resource(m_pObjList[OBJ_PLAYER],
		CManager::Spawner()->Get_Resource()[dynamic_cast<CPlayer*>(m_pObjList[OBJ_PLAYER].back())->Get_CurIsland()]);

	CCollisionMgr::Collision_Mouse_Resource(m_pObjList[OBJ_PLAYER], *CManager::UI()->Get_ObjectList(UI_MOUSE),
		CManager::Spawner()->Get_Resource()[dynamic_cast<CPlayer*>(m_pObjList[OBJ_PLAYER].back())->Get_CurIsland()]);

	CCollisionMgr::Collision_DropItem(m_pObjList[OBJ_PLAYER], *CManager::UI()->Get_ObjectList(UI_MOUSE), m_pObjList[OBJ_DROPITEM]);

	CCollisionMgr::Collision_Interaction(m_pObjList[OBJ_PLAYER], m_pObjList[OBJ_STRUCTURE]);

	CCollisionMgr::Collision_Player_Path(m_pObjList[OBJ_PLAYER], CManager::Tile()->Get_VecTile());

}
void CObjMgr::Render(HDC hDC)
{
	for (size_t i = 0; i < OBJ_END; ++i) {
		for (auto obj : m_pObjList[i]) {
			obj->Render(hDC);
		}
	}
}

void CObjMgr::Release()
{
	for (size_t i = 0; i < OBJ_END; ++i)
	{
		for_each(m_pObjList[i].begin(), m_pObjList[i].end(), DeleteObj());
		m_pObjList[i].clear();
	}

}

void CObjMgr::Delete_Object(OBJID eID)
{
	for (auto& pObj : m_pObjList[eID])
		SafeDelete(pObj);

	m_pObjList[eID].clear();
}

void CObjMgr::Add_Object(OBJID eID, CObj* pObj)
{
	if (eID >= OBJ_END || pObj == nullptr) return;

	m_pObjList[eID].push_back(pObj);
}

