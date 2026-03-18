#pragma once
#include "CTrade.h"
class CForgeTrade : public CTrade
{

public:
	CForgeTrade();
	~CForgeTrade();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	int m_iNeedGold;
	int m_iNeedCoin;


};

