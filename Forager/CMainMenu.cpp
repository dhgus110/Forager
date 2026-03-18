#include "pch.h"
#include "CMainMenu.h"
#include "CManager.h"

CMainMenu::CMainMenu()
{
}

CMainMenu::~CMainMenu()
{
}

void CMainMenu::Initailize()
{
    CManager::Bmp()->Insert_Bmp(L"../Image/Logo.bmp", L"Logo");
}

void CMainMenu::Update()
{
	if (CManager::Key()->Key_Pressing(VK_SPACE))
	{
		CManager::Scene()->Scene_Change(SC_STAGE);
	}
}

void CMainMenu::Late_Update()
{
}

void CMainMenu::Render(HDC hDC)
{
    HDC	hMemDC = CManager::Bmp()->Find_Img(L"Logo");

    GdiTransparentBlt(hDC,
		0,
		0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		WINCX,
		WINCY,
		RGB(255, 0, 255));

}

void CMainMenu::Release()
{
}
