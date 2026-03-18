#include "pch.h"
#include "CManager.h"

CManager* CManager::m_pInstance = nullptr;

CManager::CManager()
{
	m_pObjMgr = nullptr;
	m_pKeyMgr = nullptr;
	m_pUIMgr = nullptr;
	m_pScrollMgr = nullptr;
	m_pSceneMgr = nullptr;
	m_pBmpMgr = nullptr;
	m_pTileMgr = nullptr;
	m_pUserInfoMgr = nullptr;
	m_pSpawner = nullptr;
	m_pText = nullptr;

	Random::InitRandom();
}

CManager::~CManager()
{
	Release();
}

void CManager::Release()
{	
	m_pObjMgr->Destroy_Instance();
	m_pKeyMgr->Destroy_Instance();
	m_pUIMgr->Destroy_Instance();
	m_pScrollMgr->Destroy_Instance();
	m_pSceneMgr->Destroy_Instance();
	m_pBmpMgr->Destroy_Instance();
	m_pTileMgr->Destroy_Instance();
	m_pUserInfoMgr->Destroy_Instance();
	m_pSpawner->Destroy_Instance();
	m_pText->Destroy_Instance();
}
