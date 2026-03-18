#pragma once
#include "CTrade.h"
class CFurnaceTrade : public CTrade
{
public:
	CFurnaceTrade();
	~CFurnaceTrade();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	ITEMID m_eID[5];
};

