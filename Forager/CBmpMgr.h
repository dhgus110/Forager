#pragma once

#include "CMyBmp.h"
#include <map>

class CBmpMgr
{
private:
	CBmpMgr();
	CBmpMgr(const CBmpMgr& rhs) = delete;
	CBmpMgr& operator= (CBmpMgr& rSrc) = delete;
	~CBmpMgr();


public:
	HDC			Find_Img(const TCHAR* pImgKey);

public:
	void		Insert_Bmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	void		Release();


public:
	static CBmpMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CBmpMgr;

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

private:
	static CBmpMgr* m_pInstance;
	map<const TCHAR*, CMyBmp*>		m_mapBit;
};

