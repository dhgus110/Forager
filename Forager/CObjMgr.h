#pragma once

#include "Define.h"

#include "CObj.h"
#include "Enum.h"

class CObjMgr
{
private:
	CObjMgr();
	CObjMgr(const CObjMgr& rhs) = delete;
	CObjMgr& operator=(CObjMgr& rObj) = delete;
	~CObjMgr();

public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:

	void	Update();
	void	Late_Update();
	void	Render(HDC hDC);
	void	Release();


public:
	CObj*		 Get_ObjectBack(OBJID _id) { return m_pObjList[_id].back(); }
	list<CObj*>* Get_ObjectList(OBJID _id) { return &m_pObjList[_id]; }
	const bool&  Check_ObjectEmpty(OBJID _id) const { return m_pObjList[_id].empty(); }

public:
	void	Delete_Object(OBJID eID);
	void	Add_Object(OBJID eID, CObj* pObj);



private:
	static CObjMgr* m_pInstance;
	list<CObj*>		m_pObjList[OBJ_END];
};

