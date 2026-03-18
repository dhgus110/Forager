#pragma once
#include <vector>
#include <algorithm>
//#include "CManager.h"
#include "CResources.h"

class CSpawner
{
private:
	CSpawner();
	CSpawner(const CSpawner& rhs) = delete;
	CSpawner& operator= (CSpawner& rSrc) = delete;
	~CSpawner();

public:
	static CSpawner* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSpawner;

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
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

public:
	const vector<pair<int, CObj*>>(&Get_Resource() const)[9]{return m_vecResource; }
	const bool Find_Resource(int iIndex, int iIsland);
	const int  Get_ResourceCount() const { return m_iResourceCount; }

public:
	void Set_ResourceCount(int _i) { m_iResourceCount += _i; }

public:
	void ResourceSpawn(int _iIsLand);
	void ResourceSpawn(int _iIsLand, RESOURCEID _id);

	bool Check_ResourceCountLimit() { return m_iResourceCount < 170; }


private:
	static CSpawner* m_pInstance;
	vector<pair<int, CObj*>> m_vecResource[9];  // <자원 위치 인덱스 , 자원클래스> [섬 번호]
	vector<ISLAND> m_vecCopyIsland;
	int m_iResourceCount;  // 맵 전체의 자원 수

	
};

