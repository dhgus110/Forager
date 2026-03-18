#pragma once
#include "CUI.h"
class CTradeSlot : public CUI
{
public:
	CTradeSlot();
	~CTradeSlot();

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


public:
	//종류 , 슬롯 순서(위에서 아래순으로 정렬됨), 
	void Set_Item(ITEMID _id, int _order, CUI* pCUI) { m_eItemID = _id;  m_iOrder = _order;  m_iType = 1; m_pParent = pCUI; }
	void Set_Equip(EQUIP _id, int _order, CUI* pCUI) { m_eEquipID = _id; m_iOrder = _order;  m_iType = 2; m_pParent = pCUI;}

private:
	void Render_Item(HDC hDC);
	void Render_Equip(HDC hDC);



private:
	int		m_iType;  // 1: 아이템 슬롯, 2: 장비 슬롯
	int		m_iOrder; // 슬롯 순서
	int		m_iIntervalSize; //슬롯들 간격
	//int		m_iSubCnt; // 하위품목 개수

	ITEMID	m_eItemID;
	EQUIP	m_eEquipID;

	CUI*  m_pParent; // 어디 소속인지

};

