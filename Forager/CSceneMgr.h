#pragma once
#include "CScene.h"
#include "Enum.h"

class CSceneMgr
{
private:
	CSceneMgr();
	CSceneMgr(const CSceneMgr& rhs) = delete;
	CSceneMgr& operator= (CSceneMgr& rSrc) = delete;
	~CSceneMgr();


public:
	static CSceneMgr* Get_Instance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new CSceneMgr();
		}
		return m_pInstance;
	}

	static void Destroy_Instance() {
		if (m_pInstance != nullptr) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	 CScene* Get_Scene()const { return m_pScene; }

public:
	void		Scene_Change(SCENEID eScene);
	void		Update();
	void		Late_Update();
	void		Render(HDC hDC);
	void		Release();



private:
	static CSceneMgr* m_pInstance;
	CScene* m_pScene;

	SCENEID m_eSceneState;
};

