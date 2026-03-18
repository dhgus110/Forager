#include "pch.h"
#include "CTrade.h"
#include "CManager.h"

CTrade::CTrade()
{
	m_bOnOff = false;
	m_eTitle = SI_END;
	m_iSubCnt = 0;
}

CTrade::~CTrade()
{
	Release();
}

void CTrade::Initialize()
{
	m_tInfo.fX = 200.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fCX = 230.f;
	m_tInfo.fCY = 400.f;
}

int CTrade::Update()
{

	__super::Update_Rect();
	return UI_NOEVENT;
}

void CTrade::Late_Update()
{

}

void CTrade::Render(HDC hDC)
{

	//거래창 배경
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Trade_Base");
	GdiTransparentBlt(hDC,
		200,
		100,
		230,
		400,
		hMemDC,
		0,
		0,
		200,
		100,
		RGB(255, 0, 255));

	//제목
	int type = static_cast<int>(m_eTitle) / 5;
	int sub = static_cast<int>(m_eTitle) % 5;
	hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Sub_Structure(type,sub));
	GdiTransparentBlt(hDC,
		225,
		75,
		180,
		50,
		hMemDC,
		0,
		0,
		220,
		50,
		RGB(255, 0, 255));
}

void CTrade::Release()
{
}
