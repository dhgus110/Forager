#include "pch.h"
#include "CCoin.h"
#include "CManager.h"

CCoin::CCoin()
{
}

CCoin::~CCoin()
{
	Release();
}

void CCoin::Initialize()
{
	Release();

}

int CCoin::Update()
{
	if (m_bDead) UI_DEAD;

	//__super::Update_Rect();
	return UI_NOEVENT;
}

void CCoin::Late_Update()
{
}

void CCoin::Render(HDC hDC)
{

	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Coin");
	GdiTransparentBlt(hDC,
		20,
		WINCY - 38,
		36,
		36,
		hMemDC,
		0,
		0,
		36,
		36,
		RGB(255, 0, 255));

	float fnextX(0.f);
	CManager::UI()->NumberRender(CManager::User()->Get_Coin(),20,20, 58, WINCY - 31, &fnextX, false, hDC, false);

}

void CCoin::Release()
{
}
