#pragma once
#include "CUI.h"
#include "Enum.h"
class CMainStructure : public CUI
{
public:
	CMainStructure();
	~CMainStructure();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const MAIN_STRUCTURE_TYPE Get_Type() const { return m_eId; }

public:
	void Set_Type(MAIN_STRUCTURE_TYPE _id) { m_eId = _id;  Setting(_id); }

private:
	void Setting(MAIN_STRUCTURE_TYPE _id);

private:
	MAIN_STRUCTURE_TYPE m_eId;
};

