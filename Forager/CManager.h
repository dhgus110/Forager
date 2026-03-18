#pragma once
#include "Extension.h"

#include "CObjMgr.h"
#include "CKeyMgr.h"
#include "CUIMgr.h" 
#include "CScrollMgr.h"
#include "CSceneMgr.h"
#include "CBmpMgr.h"
#include "CTileMgr.h"
#include "CUserInfoMgr.h"
#include "CSpawner.h"
#include "CTextManager.h"

class CManager
{
private:
	CManager();
	CManager(const CManager& rhs) = delete;
	CManager& operator=(CManager& rKey) = delete;
	~CManager();

public:
	static CManager* Get_Instance()
	{
		if (m_pInstance == nullptr)
			m_pInstance = new CManager();
		return m_pInstance;
	}
	static void Destroy_Instance() {
		if (m_pInstance != nullptr) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	static CObjMgr* Obj() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pObjMgr == nullptr)
			instance->m_pObjMgr = CObjMgr::Get_Instance();
		return instance->m_pObjMgr;
	}

	static CKeyMgr* Key() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pKeyMgr == nullptr)
			instance->m_pKeyMgr = CKeyMgr::Get_Instance();
		return instance->m_pKeyMgr;
	}

	static CUIMgr* UI() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pUIMgr == nullptr)
			instance->m_pUIMgr = CUIMgr::Get_Instance();
		return instance->m_pUIMgr;
	}

	static CScrollMgr* Scroll() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pScrollMgr == nullptr)
			instance->m_pScrollMgr = CScrollMgr::Get_Instance();
		return instance->m_pScrollMgr;
	}

	static CSceneMgr* Scene() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pSceneMgr == nullptr)
			instance->m_pSceneMgr = CSceneMgr::Get_Instance();
		return instance->m_pSceneMgr;
	}

	static CBmpMgr* Bmp() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pBmpMgr == nullptr)
			instance->m_pBmpMgr = CBmpMgr::Get_Instance();
		return instance->m_pBmpMgr;
	}

	static CTileMgr* Tile() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pTileMgr == nullptr)
			instance->m_pTileMgr = CTileMgr::Get_Instance();
		return instance->m_pTileMgr;
	}

	static CUserInfoMgr* User() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pUserInfoMgr == nullptr)
			instance->m_pUserInfoMgr = CUserInfoMgr::Get_Instance();
		return instance->m_pUserInfoMgr;
	}

	static CSpawner* Spawner() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pSpawner == nullptr)
			instance->m_pSpawner = CSpawner::Get_Instance();
		return instance->m_pSpawner;
	}

	static CTextManager* Text() {
		CManager* instance = CManager::Get_Instance();
		if (instance->m_pText == nullptr)
			instance->m_pText = CTextManager::Get_Instance();
		return instance->m_pText;
	}

private:
	void Release();


private:
	static CManager*	m_pInstance;

	CObjMgr*			m_pObjMgr;
	CKeyMgr*			m_pKeyMgr;
	CUIMgr*				m_pUIMgr;
	CScrollMgr*			m_pScrollMgr;
	CSceneMgr*			m_pSceneMgr;
	CBmpMgr*			m_pBmpMgr;
	CTileMgr*			m_pTileMgr;
	CUserInfoMgr*		m_pUserInfoMgr;
	CSpawner*			m_pSpawner;
	CTextManager*		m_pText;
};

