#pragma once
#include "CUI.h"
#include "Extension.h"


//UI매니저에서 8개 미리 만들어 놓기 어차피 설정창에서만 보이니깐 상관없음
// 매니저 안에서 개방안한 깃발 보이기, <- 개방했으면 깃발 제거
//콜리젼에서 마우스가 해당 깃발을 가서 누르면 땅이 사지도록

class CFlag : public CUI
{
public:
	CFlag();
	~CFlag();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const int Get_IslandId() const { return m_iIslandId; }


public:
	void Setting(int _i) { m_iIslandId = _i; m_iCost = eunmToint_IslandsCost(_i);  }

private:
	int m_iCost;
	int m_iIslandId;
};

