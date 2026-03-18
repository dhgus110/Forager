#include "pch.h"
#include "CItemToolTip.h"
#include "CManager.h"
#include "CTextRender.h"

CItemToolTip::CItemToolTip():m_eSelect(IT_END), m_bUseBtn(false), m_bIntervalUseBtn(0),m_dwTime(0)
{
}

CItemToolTip::~CItemToolTip()
{	
	Release();
}


void CItemToolTip::Initialize()
{
	m_tInfo.fX = 752.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fCX = 230.f;
	m_tInfo.fCY = 400.f;
	SetOriginalPos(752.f, 100.f);
}

int CItemToolTip::Update()
{
	CheckUseBtn();
	Update_UseBtnInterval();
	Update_Position();
	__super::Update_Rect();
	return UI_NOEVENT;
}

void CItemToolTip::Late_Update()
{
}

void CItemToolTip::Render(HDC hDC)
{
	//아이템 창 테두리
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Item_ToolTip");
	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX,
		(int)m_tInfo.fY,
		(int)m_tInfo.fCX + 40,
		(int)m_tInfo.fCY,
		hMemDC,
		0,
		0,
		(int)m_tInfo.fCX,
		350,
		RGB(255, 0, 255));

	//아이템 아이콘 
	hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Item(static_cast<int>(m_eSelect)));
	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX +110,
		(int)m_tInfo.fY +80,
		56,
		56,
		hMemDC,
		0,
		0,
		56,
		56,
		RGB(255, 0, 255));


	// 아이템 설명 영역 설정
	RECT descRect = { m_tInfo.fX + 30,m_tInfo.fY + 150, m_tInfo.fX + 240, m_tInfo.fY +300 };
	TEXT_STYLE style(RGB(255, 255, 255), 23, DT_LEFT);
	CTextRender::Render_ItemDescription(hDC, m_eSelect, descRect, style);

	//사용 버튼
	if (m_bUseBtn)
	{
		hMemDC = CManager::Bmp()->Find_Img(L"USE_Btn");
		GdiTransparentBlt(hDC,
			(int)m_tInfo.fX + 70,
			(int)m_tInfo.fY + 300,
			140,
			62,
			hMemDC,
			0,
			0,
			140,
			62,
			RGB(255, 0, 255));
	}

}

void CItemToolTip::Release()
{
}

void CItemToolTip::CheckUseBtn()
{
	if (m_eSelect == IT_BERRY || m_eSelect == IT_CITRUS || m_eSelect == IT_FISH || m_eSelect == IT_COOK_FISH)
	{
		m_bUseBtn = true;
	}
	else
		m_bUseBtn = false;
}

void CItemToolTip::Update_UseBtnInterval()
{
	if (!m_bIntervalUseBtn) return;

	if (m_dwTime + 500 < (DWORD)GetTickCount64())
	{
		m_bIntervalUseBtn = false;
	}

}
