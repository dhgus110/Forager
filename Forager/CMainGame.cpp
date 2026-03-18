#include "pch.h"
#include "CMainGame.h"
#include "CManager.h"
#include "CAbstractFactory.h"
#include "CMouse.h"
#include "CSoundMgr.h"
CMainGame::CMainGame() :m_iFPS(0), m_dwTime(GetTickCount()), m_DC(nullptr)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS));

}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_DC = GetDC(g_hWnd);

	CSoundMgr::Get_Instance()->Initialize();
	CManager::Scene()->Get_Instance()->Scene_Change(SC_MAINMENU);
	CManager::UI()->AddObject(UI_MOUSE, CAbstractFactory<CMouse>::CreateUI());
	CManager::Text()->Initialize();
}

void CMainGame::Update()
{
	if (CManager::Key()->Key_Down(VK_F10)) CManager::Scene()->Scene_Change(SC_EDIT);

	CManager::Scene()->Update();
}

void CMainGame::Late_Update()
{
	CManager::Scene()->Late_Update();
}

void CMainGame::Render()
{

	CManager::Scene()->Render(m_DC);
	ViewFPS();
}

void CMainGame::Release()
{
	//CManager::Scene()->Release();
	CManager::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_DC);
}

void CMainGame::ViewFPS()
{	
	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount64())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
		SetWindowText(g_hWnd, m_szFPS);
		m_iFPS = 0;
		m_dwTime = (DWORD)GetTickCount64();
	}
}
