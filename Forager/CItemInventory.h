#pragma once
#include "CUI.h"
class CItemInventory : public CUI
{
public:
	CItemInventory();
	~CItemInventory();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	//함께 이동 함수  Info 배열로 만들어서 따로 만들었음
	void MoveToSlot(float fSpeed, float fOffsetX, float fOffsetY);
	void Update_Slot_Position();
	void ReturnToOriginalSlotPos(float fSpeed);

public:
	const INFO& Get_Infos(int _iIndex) const { return m_tInfos[_iIndex]; }
	//const ITEMID Get_ItemID(int _iIndex) const { return m_eIDs[_iIndex]; }

public:
	void Set_Extand(int _iSelect) { m_iItemSelect = _iSelect; }
	void Set_ItemSelect(int _i) { m_iItemSelect = _i; }
	//void Set_ItemId(ITEMID _id, int _iIndex) { m_eIDs[_iIndex] = _id; }



private:
	int m_iItemSelect;
	INFO m_tInfos[24];  // 아;;; 왜 이렇게 짰지;;;;;;............. 아............
	//ITEMID m_eIDs[24];  //..........아................

};