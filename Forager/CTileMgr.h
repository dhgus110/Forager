#pragma once

#include "CTile.h"
#include "BaseStruct.h"
#include <vector>


class CTileMgr
{
private:
	CTileMgr();
	CTileMgr(const CTileMgr& rhs) = delete;
	CTileMgr& operator= (CTileMgr& rSrc) = delete;
	~CTileMgr();

public:
	static CTileMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CTileMgr;

		return m_pInstance;
	}

	static void		Destroy_Instance()
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void Initialilze();
	int Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

public:
	const vector<CObj*>& Get_VecTile() const { return m_vecTile; }
	const CObj* Get_Tile(int iIndex) const { return m_vecTile[iIndex]; }

public:
	void		Save_Tile();
	void		Load_Tile();
	void		Picking_Tile(POINT ptMouse, int iDrawID, int iOption);
	


private:
	static CTileMgr* m_pInstance;
	vector<CObj*>	m_vecTile;	//타일 클래스가 들어가 있음
	vector<ISLAND> m_vecCopyIsland;

	
};

