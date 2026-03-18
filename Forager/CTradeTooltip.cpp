#include "pch.h"
#include "CTradeTooltip.h"
#include "CTrade.h"
#include "CManager.h"
#include "CTextRender.h"
#include "Extension.h"

CTradeTooltip::CTradeTooltip()
{
	m_bActive = false;
	m_iType = 0 ; 

	m_eItemID =IT_END;
	m_eEquipID = EQ_END;

	m_pParent = nullptr;
}

CTradeTooltip::~CTradeTooltip()
{
}

void CTradeTooltip::Initialize()
{
	m_tInfo.fX = 430.f;
	m_tInfo.fY = 150.f;
	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 300.f;
}

int CTradeTooltip::Update()
{
	if (!dynamic_cast<CTrade*>(m_pParent)->Get_OnOff()||( m_iType==1 && m_eItemID== IT_END)) return UI_NOEVENT;


	return UI_NOEVENT;
}

void CTradeTooltip::Late_Update()
{
}

void CTradeTooltip::Render(HDC hDC)
{
	if (!dynamic_cast<CTrade*>(m_pParent)->Get_OnOff() || (m_iType == 1 && m_eItemID == IT_END)) return;

	//툴팁 배경
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Trade_Base");
	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX,
		(int)m_tInfo.fY,
		200,
		300,
		hMemDC,
		0,
		0,
		200,
		100,
		RGB(255, 0, 255));


	Render_Item(hDC);
	Render_Equip(hDC);
}

void CTradeTooltip::Release()
{
}

void CTradeTooltip::Render_Item(HDC hDC)
{
	if (m_iType != 1) return;

	//아이콘
	HDC	hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Item(static_cast<int>(m_eItemID)));
	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX + 81,
		(int)m_tInfo.fY + 5,
		38,
		38,
		hMemDC,
		0,
		0,
		56,
		56,
		RGB(255, 0, 255));

	// 아이템 이름 + 설명 영역 설정  
	RECT descRect = { m_tInfo.fX + 20,m_tInfo.fY + 45, m_tInfo.fX + 180, m_tInfo.fY + 145 };
	TEXT_STYLE style(RGB(255, 255, 255), 20, DT_LEFT);
	CTextRender::Render_ItemDescription(hDC, m_eItemID, descRect, style);

	//필요한 물건들 아이콘 + 이름 + 내가 가지고 있는 수량 / 필요한 수량 
	const int* iArr = eunmTointArr_Furnace_ItemCost(static_cast<int>(m_eItemID));
	int iRequestCnt = 0;
	for (size_t i = 0; i < IT_END; ++i)
	{
		if (iArr[i] > 0)
		{
			//필요한 아이템 아이콘
			hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Item(i));
			GdiTransparentBlt(hDC,
				(int)m_tInfo.fX + 5,
				(int)m_tInfo.fY + 150 +40* iRequestCnt,
				30,
				30,
				hMemDC,
				0,
				0,
				56,
				56,
				RGB(255, 0, 255));

			//아이템 이름
			CTextRender::Render_Text(hDC, enumTotchar_Item_Kr(i), (int)m_tInfo.fX + 42, (int)m_tInfo.fY + 160 +40* iRequestCnt);

			//내가 가지고 있는 수량
			float fTemp(0.f);
			int myItemCnt = CManager::User()->Get_Item(i).second;
			CManager::UI()->NumberRender(myItemCnt, 12, 18, (int)m_tInfo.fX + 100.f, (int)m_tInfo.fY + 160 + 40 * iRequestCnt, &fTemp, false, hDC, true);

			//슬래쉬
			hMemDC = CManager::Bmp()->Find_Img(L"Font_Slash");
			GdiTransparentBlt(hDC,
				int(fTemp),
				(int)m_tInfo.fY + 160 + 40 * iRequestCnt,
				14,
				20,
				hMemDC,
				0,
				0,
				14,
				20,
				RGB(255, 0, 255));
			
			//필요한 수량 
			CManager::UI()->NumberRender(iArr[i], 12, 18, fTemp + 14, (int)m_tInfo.fY + 160 + 40 * iRequestCnt, &fTemp, false, hDC, false);

			iRequestCnt++;
		}
		
	}


	// 제작 버튼!!!
	hMemDC = CManager::Bmp()->Find_Img(L"Production_Btn");
	GdiTransparentBlt(hDC,
		(int)m_tInfo.fX + 30,
		(int)m_tInfo.fY + 240,
		140,
		32,
		hMemDC,
		0,
		0,
		140,
		32,
		RGB(255, 0, 255));


}

void CTradeTooltip::Render_Equip(HDC hDC)
{
	if (m_iType != 2) return;

}
