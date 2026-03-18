#include "pch.h"
#include "CTradeSlot.h"
#include "CManager.h"
#include "CTextRender.h"
#include "CTrade.h"

CTradeSlot::CTradeSlot()
{
	m_iType = 0 ; 
	m_iOrder = 0;
	m_iIntervalSize = 0;
	//m_iSubCnt = 0;

	m_eItemID = IT_END;
	m_eEquipID = EQ_END;
}

CTradeSlot::~CTradeSlot()
{
	Release();
}

void CTradeSlot::Initialize()
{
	m_tInfo.fCX = 190.f;
	m_tInfo.fCY = 40.f;
	//m_tInfo.fX = 220.f;
	//m_tInfo.fY = 130 + m_iIntervalSize * m_iOrder;

	m_iIntervalSize = 50.f;
}

int CTradeSlot::Update()
{
	if (!dynamic_cast<CTrade*>(m_pParent)->Get_OnOff()) return UI_NOEVENT;

	__super::Update_Pulse();
	__super::Update_Rect();
	return UI_NOEVENT;
}

void CTradeSlot::Late_Update()
{
}

void CTradeSlot::Render(HDC hDC)
{
	if (!dynamic_cast<CTrade*>(m_pParent)->Get_OnOff()) return;

	//슬롯 배경
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Trade_Base");
	GdiTransparentBlt(hDC,
		220,
		130 + m_iIntervalSize * m_iOrder ,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		0,
		0,
		200,
		100,
		RGB(255, 0, 255));

	// 아이콘 + 아이콘 이름
	Render_Item(hDC);
	Render_Equip(hDC);
}

void CTradeSlot::Release()
{
}

void CTradeSlot::Render_Item(HDC hDC)
{
	if (m_iType != 1) return;
	HDC	hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Item(static_cast<int>(m_eItemID)));
	GdiTransparentBlt(hDC,
		220 + 10,
		130 + m_iIntervalSize * m_iOrder +1 ,
		38,
		38,
		hMemDC,
		0,
		0,
		56,
		56,
		RGB(255, 0, 255));

	//RECT descRect = { 220 + 50 , 130 + m_iIntervalSize * m_iOrder + 4,  220 + 120,  130 + m_iIntervalSize * m_iOrder + 37 };
	//TEXT_STYLE style(RGB(255, 255, 255), 20, DT_LEFT);
	CTextRender::Render_Text(hDC, enumTotchar_Item_Kr(static_cast<int>(m_eItemID)), 220 + 50, 130 + m_iIntervalSize * m_iOrder + 4);

}

void CTradeSlot::Render_Equip(HDC hDC)
{
	if (m_iType != 2) return;

	HDC	hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Equip(static_cast<int>(m_eEquipID)));
	GdiTransparentBlt(hDC,
		220 + 10,
		130 + m_iIntervalSize * m_iOrder + 1,
		38,
		38,
		hMemDC,
		0,
		0,
		56,
		56,
		RGB(255, 0, 255));

	CTextRender::Render_Text(hDC, enumTotchar_Equip_Kr(static_cast<int>(m_eEquipID)), 220 + 50, 130 + m_iIntervalSize * m_iOrder + 4);
}
