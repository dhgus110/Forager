#pragma once
#include "CUI.h"
#include "Enum.h"

class CSubStructure : public CUI
{
public:
	CSubStructure();
	~CSubStructure();
	
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const SUB_STRUCTURE_TYPE Get_Type() const { return m_eId; }

public:
	void Set_Type(MAIN_STRUCTURE_TYPE _type, SUB_STRUCTURE_TYPE  _id) { m_eId = _id; Setting(_type, _id); }

private:
	void Setting(MAIN_STRUCTURE_TYPE _type, SUB_STRUCTURE_TYPE  _id);

private:
	SUB_STRUCTURE_TYPE m_eId;
};

