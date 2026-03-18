#include "pch.h"
#include "CFurnaceTrade.h"
#include "CManager.h"
#include "CAbstractFactory.h"
#include "CTradeSlot.h"
#include "CTradeTooltip.h"

CFurnaceTrade::CFurnaceTrade()
{
}

CFurnaceTrade::~CFurnaceTrade()
{
}

void CFurnaceTrade::Initialize()
{
	CTrade::Initialize();

	//Trade °ü·Ã
	m_eTitle = SI_I_0;
	m_iSubCnt = 5;

	//TradeSlot »ý¼º
	m_eID[0] = IT_COAL;
	m_eID[1] = IT_SMELT_GOLD;
	m_eID[2] = IT_SMELT_IRON;
	m_eID[3] = IT_BRICK;
	m_eID[4] = IT_COOK_FISH;

	//½½·Ô
	for (int i = 0; i < 5; ++i)
	{
		CUI* pCUI = CAbstractFactory<CTradeSlot>::CreateUI(220.f, 130.f +50.f* (float)i);
		CManager::UI()->AddObject(UI_TRADE_SLOT,pCUI);
		dynamic_cast<CTradeSlot*>(pCUI)->Set_Item(m_eID[i], i, this);
	}

	//ÅøÆÁ
	CUI* pCUI = CAbstractFactory<CTradeTooltip>::CreateUI();
	CManager::UI()->AddObject(UI_TRADE_FURNACE_TOOLTIP, pCUI); 
	dynamic_cast<CTradeTooltip*>(pCUI)->Set_Parent(this,1);

}


int CFurnaceTrade::Update()
{
	if (!m_bOnOff) return UI_NOEVENT;

	int res = CTrade::Update();



	return res;
}

void CFurnaceTrade::Late_Update()
{
	if (!m_bOnOff) return;

	CTrade::Late_Update();

	if (CManager::Key()->Key_Pressing('Q')) {
		m_bOnOff = false;
		dynamic_cast<CTradeTooltip*>(CManager::UI()->Get_ObjectBack(UI_TRADE_FURNACE_TOOLTIP))->Reset();
	}
		
}

void CFurnaceTrade::Render(HDC hDC)
{
	if (!m_bOnOff) return;

	CTrade::Render(hDC);

}

void CFurnaceTrade::Release()
{
	CTrade::Release();
}
