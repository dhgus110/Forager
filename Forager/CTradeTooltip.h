#pragma once
#include "CUI.h"
class CTradeTooltip : public CUI
{
public:
	CTradeTooltip();
	~CTradeTooltip();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const ITEMID Get_ItemID() const { return m_eItemID; }
	const EQUIP Get_EquipID() const { return m_eEquipID; }
	const CUI* Get_Parent() const { return m_pParent; }
	const bool Get_Active() const { return m_bActive; }

public:
	void Set_Parent(CUI* pCUI, int iType) { m_pParent = pCUI;  m_iType = iType;}
	void Set_Item(ITEMID _id){ m_eItemID = _id; m_bActive = true;} 	//슬롯이 눌렸을 때 호출
	void Set_Equip(EQUIP _id) { m_eEquipID = _id;  m_bActive =true; } //슬롯이 눌렸을 때 호출
	void Reset() { m_bActive = false, m_eItemID = IT_END; m_eEquipID = EQ_END; } //리셋 : 툴팁창 끄고싶을 때 호출

private:
	void Render_Item(HDC hDC);
	void Render_Equip(HDC hDC);


private:
	bool	m_bActive; // 툴팁이 생겼나 안생겻나
	int		m_iType;  // 1: 아이템 슬롯, 2: 장비 슬롯

	ITEMID	m_eItemID;
	EQUIP	m_eEquipID;

	CUI*	m_pParent; // 어디 소속인지
};

