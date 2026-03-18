#include "pch.h"
#include "CUI.h"

CUI::CUI() :m_bDead(false),  m_pFrameKey(nullptr), m_pTarget(nullptr), m_bShowRender(true), m_bFollowTarget(false),
m_bIsMoving(false), m_fGoalX(0.0f), m_fGoalY(0.0f), m_fMoveSpeed(0.0f), m_fOriginalX(0.0f), m_fOriginalY(0.0f),
m_bIsPulsing(false), m_bPulseRefeat(false), m_bPulseReverse(false), m_fOriginalSizeX(0.f), m_fOriginalSizeY(0.f),
m_fPulseMaxValue(0.f), m_fPulseMinValue(0.f), m_fPulseCurRate(0.f), m_fPulseSpeed(0.f)
{                                                                                                               
	ZeroMemory(&m_tInfo, sizeof(INFO));                                                                        
	ZeroMemory(&m_tRect, sizeof(RECT));
	ZeroMemory(&m_tFrame, sizeof(FRAME));

}


void CUI::MoveToPosition(float fGoalX, float fGoalY, float fSpeed)
{
	m_bIsMoving = true;
	m_fGoalX = fGoalX;
	m_fGoalY = fGoalY;
	m_fMoveSpeed = fSpeed;
}

void CUI::Update_Position()
{
    if (!m_bIsMoving)
        return;

    float fDiffX = m_fGoalX - m_tInfo.fX;
    float fDiffY = m_fGoalY - m_tInfo.fY;

    // 도착 판정
    if (abs(fDiffX) < 1.0f && abs(fDiffY) < 1.0f)
    {
        m_tInfo.fX = m_fGoalX;
        m_tInfo.fY = m_fGoalY;
        m_bIsMoving = false;
        return;
    }

    float fDistance = sqrt(fDiffX * fDiffX + fDiffY * fDiffY);
    float fNormalizedX = fDiffX / fDistance;
    float fNormalizedY = fDiffY / fDistance;

    // 이동 거리가 남은 거리보다 크면 바로 도착
    if (m_fMoveSpeed >= fDistance)
    {
        m_tInfo.fX = m_fGoalX;
        m_tInfo.fY = m_fGoalY;
        m_bIsMoving = false;
    }
    else
    {
        //아니면 속도대로 이동
        m_tInfo.fX += fNormalizedX * m_fMoveSpeed;
        m_tInfo.fY += fNormalizedY * m_fMoveSpeed;
    }
}

void CUI::ReturnToOriginalPos(float fSpeed)
{
    MoveToPosition(m_fOriginalX, m_fOriginalY, fSpeed); 
}

void CUI::Start_Pulse(float fsizeX, float fsizeY, float fMaxVal, float fMinVal, float fSpeed, bool repeat)
{
    //초기화
    if (!m_bIsPulsing)
        Stop_Pulse();

    if (m_fOriginalSizeX == 0.f) m_fOriginalSizeX = fsizeX;
    if (m_fOriginalSizeY == 0.f) m_fOriginalSizeY = fsizeY;

    m_bIsPulsing = true;
    m_bPulseReverse = false; //처음은 커지게
    m_bPulseRefeat = repeat;
    m_fPulseMaxValue = fMaxVal;
    m_fPulseMinValue = fMinVal;
    m_fPulseSpeed = fSpeed;
  

    m_fPulseCurRate = 1.0f;
}

void CUI::Update_Pulse()
{
    if (!m_bIsPulsing)
        return;

    if (!m_bPulseReverse)
    {
        m_fPulseCurRate += (m_fPulseSpeed * 0.05f);

        if (m_fPulseCurRate >= m_fPulseMaxValue) {
            m_fPulseCurRate = m_fPulseMaxValue;
            m_bPulseReverse = true;
        }
    }
    else
    {
        m_fPulseCurRate -= (m_fPulseSpeed * 0.05f);

        if (m_fPulseCurRate <= m_fPulseMinValue) {
            m_fPulseCurRate = m_fPulseMinValue;
            m_bPulseReverse = false;
        }
    }

    //m_fOriginalSizeX *= m_fPulseCurRate;
    //m_fOriginalSizeY *= m_fPulseCurRate;

    m_tInfo.fCX = m_fOriginalSizeX * m_fPulseCurRate;
    m_tInfo.fCY = m_fOriginalSizeY * m_fPulseCurRate;

    if (m_fPulseCurRate <= m_fPulseMinValue && !m_bPulseRefeat)
        Stop_Pulse();
}

void CUI::Stop_Pulse()
{
    m_bIsPulsing = false;

    m_fOriginalSizeX = 0.f;
    m_fOriginalSizeY = 0.f;

}



void CUI::Update_Rect()
{
	m_tRect.left = static_cast<LONG>(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.top = static_cast<LONG>(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.right = static_cast<LONG>(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.bottom = static_cast<LONG>(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
