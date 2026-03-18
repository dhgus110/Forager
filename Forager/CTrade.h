#pragma once
#include "CUI.h"
class CTrade : public CUI
{
public:
	CTrade();
	~CTrade();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const STRUCTURE_ITEM_ID Get_Title() const { return m_eTitle; }

public:
	//void Setting(STRUCTURE_ITEM_ID _id, int _cnt) { m_eTitle = _id; m_iSubCnt = _cnt; }
	//void Set_Title(STRUCTURE_ITEM_ID _id) { m_eTitle = _id; }

public:
	const bool  Get_OnOff() const { return m_bOnOff; }

public:
	void Set_OnOff(bool _b) { m_bOnOff = _b; }

protected:
	bool				m_bOnOff;

	STRUCTURE_ITEM_ID	m_eTitle; //力格
	int					m_iSubCnt; // 窍困前格 俺荐

};

