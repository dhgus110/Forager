#include "pch.h"
#include "CMenuTap.h"
#include "CManager.h"
#include "CAbstractFactory.h"
#include "CSubMenuButton.h"

CMenuTap::CMenuTap()
{
}

CMenuTap::~CMenuTap()
{
	Release();
}

void CMenuTap::Initialize()
{
	m_tInfo.fX = (WINCX * 0.5f) - 187.f;
	m_tInfo.fY = -85.f;
	SetOriginalPos((WINCX * 0.5f) - 187.f, -85.f);

}

int CMenuTap::Update()
{

	Update_Position();
	__super::Update_Rect();

	return UI_NOEVENT;
}

void CMenuTap::Late_Update()
{
}

void CMenuTap::Render(HDC hDC)
{
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"MenuTap_Base");
	GdiTransparentBlt(hDC,
		m_tInfo.fX,
		m_tInfo.fY,
		374,
		83,
		hMemDC,
		0,
		0,
		468,
		104,
		RGB(255, 0, 255));
}

void CMenuTap::Release()
{
}


