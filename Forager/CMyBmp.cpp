#include "pch.h"
#include "CMyBmp.h"

CMyBmp::CMyBmp()
{
}

CMyBmp::~CMyBmp()
{
	Release();
}

void CMyBmp::Load_Bmp(const TCHAR* pFilePath)
{
	HDC	hDC = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,		// 프로그램 인스턴스 핸들
		pFilePath,	// 파일의 경로
		IMAGE_BITMAP, // 어떤 타입
		0, 0,		// 가로, 세로 크기(파일로부터 읽어들이기 때문에 따로 사이즈 지정을 하지 않음)
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일에서 이미지 부르기
	// LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형태로 변환

// SelectObject 준비한 DC와  GDI 오브젝트에 불러온 비트맵을 선택하기 위해 사용
//	GDI 오브젝트를 선택하기 전에 기존에 가지고 있던 GDI 오브젝트를 반환

	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CMyBmp::Release()
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
