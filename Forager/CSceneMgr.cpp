#include "pch.h"
#include "CSceneMgr.h"
#include "Extension.h"
//#include "CLogo.h"
#include "CMainMenu.h"
#include "CStage.h"
#include "CEdit.h"
#include "CManager.h"


CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() :m_pScene(nullptr), m_eSceneState(SC_END)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Scene_Change(SCENEID eScene)
{
	if (m_eSceneState != eScene) {
		SafeDelete(m_pScene);

		switch (eScene)
		{
		case SC_LOGO:
			//m_pScene = new CLogo;
			//m_pScene->Initailize();
			break;

		case SC_MAINMENU:
			m_pScene = new CMainMenu;
			m_pScene->Initailize();
			break;

		case SC_STAGE:
			m_pScene = new CStage;
			m_pScene->Initailize();
			break;

		case SC_EDIT:
			m_pScene = new CEdit;
			m_pScene->Initailize();

		}
		m_eSceneState = eScene;

	}
}

void CSceneMgr::Update()
{
	m_pScene->Update();
}

void CSceneMgr::Late_Update()
{
	CManager::Key()->Late_Update();
	m_pScene->Late_Update();

}

void CSceneMgr::Render(HDC hDC)
{
	m_pScene->Render(hDC);

}

void CSceneMgr::Release()
{
	SafeDelete<CScene*>(m_pScene);

}
