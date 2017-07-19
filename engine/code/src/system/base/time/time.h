#pragma once

#include "../types.h"

//-----------------------------------------------------------------------------

struct SGameTime
{
	SGameTime();
	float32 m_fRealTime;
	float32 m_fRealTimeDelta;

	float32 m_fGameTime;
	float32 m_fGameTimeDelta;
};

inline SGameTime::SGameTime()
	: m_fRealTime(0.0f)
	, m_fRealTimeDelta(0.0f)
	, m_fGameTime(0.0f)
	, m_fGameTimeDelta(0.0f)
{

}
