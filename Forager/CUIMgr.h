#pragma once
#include "Extension.h"
#include "CUI.h"
#include <list>
#include <vector>
#include "Enum.h"
//#include "CManager.h"

class CUIMgr
{
private:
	CUIMgr();
	CUIMgr(const CUIMgr& rhs) = delete;
	CUIMgr& operator=(CUIMgr& rObj) = delete;
	~CUIMgr();

public:
	static CUIMgr* Get_Instance() {
		if (m_pInstance == nullptr) {
			m_pInstance = new CUIMgr;
		}
		return m_pInstance;
	}
	static void		Destroy_Instance() {
		if (m_pInstance != nullptr) {
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

public:
	void			Initailize();
	void			Update();
	void			Late_Update();
	void			Render(HDC hDC);
	void			Release();

public:
	// UI List
	void			AddObject(UIID _id, CUI* _pObj);
	void			Delete_Obj(UIID eID);

	//필드에 있는 자원들의 공용 체력바
	void			AddObject(int _iIndex, CUI* _pCUI);
	void		    Delete_CommonHp(int _iIndex);
	
	//스킬창 버튼들
	void			AddSkill(SKILLID _id, CUI* _pObj);
	void			Delete_Obj(SKILLID _id);

	//건설 탭 버튼들
	void			AddMainStructure(MAIN_STRUCTURE_TYPE _type, CUI* _pObj);
	void			Delete_Obj(MAIN_STRUCTURE_TYPE _type);
	void			AddSubStructure(MAIN_STRUCTURE_TYPE _type,SUB_STRUCTURE_TYPE _sub, CUI* _pObj);
	void			Delete_Obj(MAIN_STRUCTURE_TYPE _type, SUB_STRUCTURE_TYPE _sub);



public:
	CUI* Get_ObjectBack(UIID _id) { return m_pUIList[_id].back(); }		// UI List
	list<CUI*>* Get_ObjectList(UIID _id) { return &m_pUIList[_id]; }		// UI List
	const bool& Get_Empty(UIID _id) const { return m_pUIList[_id].empty(); }		// UI List

	CUI* Get_CommonHp(int _iIndex);		//필드에 있는 자원들의 공용 체력바

	CUI* Get_SkillBack(SKILLID _id) { return m_pSKillList[_id].back(); }	//스킬창 버튼들

	CUI* Get_MainStructure(MAIN_STRUCTURE_TYPE _type) { return m_pMainStructure[_type].back(); } //메인 건설 버튼
	CUI* Get_SubStructure(MAIN_STRUCTURE_TYPE _type,SUB_STRUCTURE_TYPE _sub) { return m_pSubStructure[_type][_sub].back(); } //서브 건설 버튼
	const bool Get_StructureView() const { return m_bStructureView; }

	//현재 선택됐는지 안됐는지 건설창 버튼들
	const pair<MAIN_STRUCTURE_TYPE, bool>& Get_CurSelectMainStructureBtn() const { return m_CurSelectMainStructureBtn; }
	const pair<SUB_STRUCTURE_TYPE, bool>& Get_CurSelectSubStructureBtn() const { return m_CurSelectSubStructureBtn; }
	const DWORD Get_Structure_Time() const { return m_dwPressIntervalTime; }

	// 토지구입창 관련
	const bool Get_IslandFlag() const { return m_bIslandFlag; }

public:
	void Set_IsUIView(UIID _id, bool _bView) { m_IsUIViewList[(int)_id] = _bView; } //UI list중에서 무엇을 랜더링 할지
	void Set_SkillView(bool _b) { m_bSkillView = _b; }		//스킬창 랜더링
	void Set_StructureView(bool _b) { m_bStructureView = _b; }	 
	void Set_CurSelectMainStructureBtn(MAIN_STRUCTURE_TYPE main, bool _b) { m_CurSelectMainStructureBtn = { main, _b }; }
	void Set_CurSelectSubStructureBtn(SUB_STRUCTURE_TYPE sub, bool _b) { m_CurSelectSubStructureBtn = { sub,_b }; }
	void Set_Structure_Time() { m_dwPressIntervalTime = static_cast<DWORD>(GetTickCount64()); }
	void Set_Island_Flag(bool _b);

public:
	//숫자 랜더
	void NumberRender(int _value, int _sizeX, int _sizeY, float _fX, float _fY, float* _fNextX, bool _bScroll, HDC hDC, bool _isYellow);
	void View_Weapon_Slot(HDC hDC);		//무기 슬롯 랜더
	void View_Item_Slot(HDC hDC);		//아이템 슬롯 랜더
	void Init_Structure_Buttons_Position();		//건설 버튼들 위치 초기위치로 변경

	//건물 프리뷰 없애는 함수
	void Set_previewDelete() { m_bPreviewDelete = true; }
	void PreviewDelete() { if (!m_bPreviewDelete)return; m_bPreviewDelete = false; Delete_Obj(UI_BUILDING_PREVIEW); }

private:
	void Move_Frame();

private:	
	static CUIMgr* m_pInstance;

	bool m_bSkillView;
	DWORD m_dwSkillWindowTime;
	int m_iSkillWindowMotion;

	list<CUI*> m_pUIList[UI_END];
	vector<bool> m_IsUIViewList;			// UI list중에서 무엇을 랜더링할지 말지
	list<pair<int,CUI*>> m_pCommonHpList; // 자원의 타일 인덱스, 체력바
	list<CUI*> m_pSKillList[SK_END];		//스킬 버튼들 활성화할지 비활성화할지 아예 랜더링 안할지

	//건설탭 버튼들
	bool m_bStructureView;		//UI매니저에서  업데이트,랜더에 넣을 건설탭버튼들 실행할지 안할지 (건설탭 버튼 누르면 실행)
	list<CUI*> m_pMainStructure[ST_END];			//산업, 농업, 경제 ,마법 버튼
	list<CUI*> m_pSubStructure[ST_END][SST_END];	// 위에 버튼 누르면 나오는 하위버튼들
	pair<MAIN_STRUCTURE_TYPE, bool> m_CurSelectMainStructureBtn;	//건설탭에서 무슨 버튼이 클릭됐는지
	pair< SUB_STRUCTURE_TYPE, bool>m_CurSelectSubStructureBtn;
	DWORD m_dwPressIntervalTime;

	//건물프리뷰 없애는 변수
	bool m_bPreviewDelete;

	//토지구입창 관련
	bool m_bIslandFlag; // 아직 안 산 땅에 깃발 보이게 하는거
};

