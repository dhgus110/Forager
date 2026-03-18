#pragma once
#include "CBuilding.h"
class CFurnace : public CBuilding
{
	enum State{ IDLE,PRODUCTION,END };

public:
	CFurnace();
	~CFurnace();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	void Motion_Change();

	//필요 없을거 같은데
	void Set_Production() { m_eCurProduction = CFurnace::PRODUCTION; }
	void Set_Idle() { m_eCurProduction = CFurnace::IDLE; }

	//제작버튼 누를 때 이거 쓰면 됨
	void Check_Production(ITEMID _id); //소유하고 있는 필요 아이템 확인하고 감소함


private:
	void Change_Ground();
	void Prevent_Time();
	void Production(); //실제 생산

	void Move_Effect_Frame();

private:
	int		m_iProductCnt; //생산량
	ITEMID	m_eProductID;	//생산중인 아이템
	bool	m_bPossibleProduct;
	CFurnace::State m_ePreProduction;
	CFurnace::State m_eCurProduction;

	DWORD m_dwProductTime;		//생산 시간
	DWORD m_dwPreventTime; //여러번 눌려서 생산되는거 방지

	FRAME m_tEffectFrame;
};

