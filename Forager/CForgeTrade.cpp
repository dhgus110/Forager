#include "pch.h"
#include "CForgeTrade.h"
#include "CManager.h"
#include "CTextRender.h"
#include <cmath>
#include "CWeapon.h"

CForgeTrade::CForgeTrade()
{
	m_iNeedGold = 0;
	m_iNeedCoin = 0;
}

CForgeTrade::~CForgeTrade()
{
	Release();
}

void CForgeTrade::Initialize()
{
	m_tInfo.fX = 375.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 400.f;
	m_iNeedGold = 5;
	m_iNeedCoin = 500'000;
	
	m_eTitle = SI_I_1;
}

int CForgeTrade::Update()
{
	if (!m_bOnOff) return UI_NOEVENT;

	if (CManager::Key()->Key_Pressing('Q')) {
		m_bOnOff = false;
	}
	if (CManager::Key()->Key_Pressing('I')) {
		int myGold = CManager::User()->Get_Item(static_cast<int>(IT_SMELT_GOLD)).second;
		int myCoin = CManager::User()->Get_Coin();
		if (myGold >= m_iNeedGold && myCoin >= m_iNeedCoin)
		{
			CManager::User()->Set_Coin(-m_iNeedCoin);
			CManager::User()->Set_Item(IT_SMELT_GOLD,-m_iNeedGold);
			dynamic_cast<CWeapon*>(CManager::Obj()->Get_ObjectBack(OBJ_EQUIP))->Weapon_Change();
		}
		//임시
		dynamic_cast<CWeapon*>(CManager::Obj()->Get_ObjectBack(OBJ_EQUIP))->Weapon_Change();

	}


	int res = CTrade::Update();
	return res;
}

void CForgeTrade::Late_Update()
{

}

void CForgeTrade::Render(HDC hDC)
{
	if (!m_bOnOff) return;

	//베이스
	HDC	hMemDC = CManager::Bmp()->Find_Img(L"Trade_Base");
	GdiTransparentBlt(hDC,
		static_cast<int>(m_tInfo.fX),
		static_cast<int>(m_tInfo.fY),
		300,
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
	hMemDC = CManager::Bmp()->Find_Img(enumTotchar_Sub_Structure(type, sub));
	GdiTransparentBlt(hDC,
		static_cast<int>(m_tInfo.fX) +50,
		static_cast<int>(m_tInfo.fY) -20,
		200,
		50,
		hMemDC,
		0,
		0,
		220,
		50,
		RGB(255, 0, 255));

	//무기 아이콘
	hMemDC = CManager::Bmp()->Find_Img(L"Pickax2");
	GdiTransparentBlt(hDC,
		static_cast<int>(m_tInfo.fX) + 94,
		static_cast<int>(m_tInfo.fY) + 40,
		112,
		112,
		hMemDC,
		0,
		0,
		56,
		56,
		RGB(255, 0, 255));

	//무기 이름
	TEXT_STYLE style(RGB(255, 191, 0), 30, DT_LEFT);
	CTextRender::Render_Text(hDC, L"황금 곡괭이", static_cast<int>(m_tInfo.fX) + 90, (int)m_tInfo.fY + 160, style);

	//무기 설명
	CTextRender::Render_Text(hDC, L"치명적으로 강력크하다..", (int)m_tInfo.fX + 30, (int)m_tInfo.fY + 200 );

	//필요 재료 (금괴, 코인)
	int myGold = CManager::User()->Get_Item(static_cast<int>(IT_SMELT_GOLD)).second;
	int myCoin = CManager::User()->Get_Coin();

	//금괴
	hMemDC = CManager::Bmp()->Find_Img(L"Smelt_Gold");
	GdiTransparentBlt(hDC,
		static_cast<int>(m_tInfo.fX) + 5,
		static_cast<int>(m_tInfo.fY) + 220,
		50,
		50,
		hMemDC,
		0,
		0,
		56,
		56,
		RGB(255, 0, 255));

	//내 금괴 수량
	float fTemp;
	bool isGoldEnough = (myGold >= m_iNeedGold);
	CManager::UI()->NumberRender(
		myGold,
		14, 24,
		(int)m_tInfo.fX + 230, (int)m_tInfo.fY+233,
		&fTemp, false,
		hDC, isGoldEnough
	);

	// 슬래시 표시
	hMemDC = CManager::Bmp()->Find_Img(L"Font_Slash");
	GdiTransparentBlt(hDC,
		int(fTemp),
		(int)m_tInfo.fY +233,
		14,
		24,
		hMemDC,
		0, 0,
		14, 20,
		RGB(255, 0, 255));

	// 필요한 수량
	CManager::UI()->NumberRender(
		m_iNeedGold,
		14, 24,
		fTemp + 16, (int)m_tInfo.fY + 233,
		&fTemp, false,
		hDC, false
	);

	//코인
	hMemDC = CManager::Bmp()->Find_Img(L"Coin");
	GdiTransparentBlt(hDC,
		static_cast<int>(m_tInfo.fX) + 5,
		static_cast<int>(m_tInfo.fY) + 280,
		50,
		50,
		hMemDC,
		0,
		0,
		36,
		36,
		RGB(255, 0, 255));

	//내 코인 수량
	int iSeat = myCoin > 0 ? (int)log10(myCoin) + 1 : 1; //자리수
	bool isCoinEnough = (myCoin >= m_iNeedCoin);
	CManager::UI()->NumberRender(
		myCoin,
		12, 21,
		(int)m_tInfo.fX +180 - 12 * iSeat, (int)m_tInfo.fY + 293,
		&fTemp, false,
		hDC, isCoinEnough
	);

	// 슬래시 표시
	hMemDC = CManager::Bmp()->Find_Img(L"Font_Slash");
	GdiTransparentBlt(hDC,
		int(fTemp),
		(int)m_tInfo.fY + 293,
		12,
		21,
		hMemDC,
		0, 0,
		14, 20,
		RGB(255, 0, 255));

	// 필요한 수량
	CManager::UI()->NumberRender(
		m_iNeedCoin,
		12, 21,
		fTemp + 9, (int)m_tInfo.fY + 293,
		&fTemp, false,
		hDC, false
	);


	//제작 버튼
	hMemDC = CManager::Bmp()->Find_Img(L"Production_Btn");
	GdiTransparentBlt(hDC,
		static_cast<int>(m_tInfo.fX) + 80,
		static_cast<int>(m_tInfo.fY) + 350,
		140,
		40,
		hMemDC,
		0, 0,
		140, 32,
		RGB(255, 0, 255));
}

void CForgeTrade::Release()
{
}
