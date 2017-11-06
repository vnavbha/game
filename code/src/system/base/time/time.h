#pragma once

#include "../types.h"

//-----------------------------------------------------------------------------

struct STime
{
	STime();
	float32 m_fRealTime;
	float32 m_fRealTimeDelta;
};

inline STime::STime()
	: m_fRealTime(0.0f)
	, m_fRealTimeDelta(0.0f)
{

}
