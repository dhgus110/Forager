#pragma once
#include "CObj.h"
#include "Enum.h"
#include "CUI.h"
//#include "CManager.h"

class CResources : public CObj
{
public:
	enum STATE { IDLE, HIT, END};
public:
	CResources();
	~CResources();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const RESOURCEID& Get_ResourceId() const { return m_eId; }

public:
	const int Get_Hp() const { return m_iHp; }

	const int Get_TileIndex() const { return m_iTileIndex; }
	CUI* Get_HpBar() const { return m_pHpBar; }

public:
	void Set_ResourceId(RESOURCEID _id ,int _iIndex );
	void Set_Hit() { m_eCurState = CResources::HIT; m_bEffect = true; }
	void Set_HpBar(CUI* pHpBar) { m_pHpBar = pHpBar; }
	

private:
	void Move_Frame();
	void Move_EffectFrame();
	void Motion_Change();



private:
	int m_iHp; 
	int m_iRandomDir;

	int m_iTileIndex;

	CResources::STATE m_eCurState;
	CResources::STATE m_ePreState;

	RESOURCEID m_eId;

	const TCHAR* m_pFrameKey;
	FRAME		 m_tFrame;

	FRAME		 m_tEffectFrame;
	bool		m_bEffect;



	CUI* m_pHpBar;

};

