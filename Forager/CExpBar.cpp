#include "pch.h"
#include "CExpBar.h"
#include "CManager.h"

CExpBar::CExpBar()
{
}

CExpBar::~CExpBar()
{
	Release();
}

void CExpBar::Initialize()
{
	m_tInfo.fX = (float)WINCX * 0.5f - 350.f;
	m_tInfo.fY = 10.f;
	SetOriginalPos((float)WINCX * 0.5f - 350.f, 10.f);
}

int CExpBar::Update()
{
	if (m_bDead) UI_DEAD;

	Update_Position();
	__super::Update_Rect();
	return UI_NOEVENT;
}

void CExpBar::Late_Update()
{
}

void CExpBar::Render(HDC hDC)
{
	if (!m_bShowRender) return;

    HDC	hMemDC = CManager::Bmp()->Find_Img(L"Player_Exp_Back");
	GdiTransparentBlt(hDC,
		m_tInfo.fX,
		m_tInfo.fY,
		700,
		30,
		hMemDC,
		0,
		0,
		800,
		30,
		RGB(255, 0, 255));

	hMemDC = CManager::Bmp()->Find_Img(L"Player_Exp");
	GdiTransparentBlt(hDC,
		m_tInfo.fX + 4,
		m_tInfo.fY + 4,
		int(692 * CManager::User()->Get_PlayerExpRate()),
		22,
		hMemDC,
		0,
		0,
		792,
		22,
		RGB(255, 0, 255));

	hMemDC = CManager::Bmp()->Find_Img(L"Word_Exp");
	GdiTransparentBlt(hDC,
		m_tInfo.fX + 244,
		m_tInfo.fY + 5,
		40,
		20,
		hMemDC,
		0,
		0,
		40,
		20,
		RGB(255, 0, 255));

	float fnextX(0.f);
	CManager::UI()->NumberRender(CManager::User()->Get_PlayerLevel(), 15, 26, m_tInfo.fX + 287, m_tInfo.fY + 5, &fnextX, false, hDC, false);

	CManager::UI()->NumberRender(CManager::User()->Get_ExpInfo().first, 15, 19, m_tInfo.fX + 360, m_tInfo.fY +5, &fnextX, false, hDC, false);
	
	hMemDC = CManager::Bmp()->Find_Img(L"Font_Slash");
	GdiTransparentBlt(hDC,
		int(fnextX),
		m_tInfo.fY + 5,
		14,
		20,
		hMemDC,
		0,
		0,
		14,
		20,
		RGB(255, 0, 255));

	CManager::UI()->NumberRender(CManager::User()->Get_ExpInfo().second, 15, 19, fnextX+14, m_tInfo.fY + 5, &fnextX, false, hDC, false);


}

void CExpBar::Release()
{
}
