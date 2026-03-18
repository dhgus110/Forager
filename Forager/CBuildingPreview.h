#pragma once
#include "CUI.h"
#include "Enum.h"
class CBuildingPreview : public CUI
{
public:
	CBuildingPreview();
	~CBuildingPreview();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	const bool Get_CanBuild() const { return m_bCanBuild; }
	const STRUCTURE_ITEM_ID Get_ID() const { return m_eId; }

public:
	void Set_CanBuild(bool _b) { m_bCanBuild = _b; }
	void Setting(STRUCTURE_ITEM_ID _id, int _iSizeX = 2, int _iSizeY =2);

private:
	bool CheckBuildable(int _x, int _y);
	void Update_Build();



private:
	bool m_bCanBuild; //건설할 수 있는 땅이면 true
	bool m_bBuild; //건설 했으면 true
	int m_iSizeXRate;
	int m_iSizeYRate;
	//POINT m_tScrollPos;
	//POINT m_tbeginScrollPos;

	DWORD m_dwTime;

	
	STRUCTURE_ITEM_ID m_eId;


};

