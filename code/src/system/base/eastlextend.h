#pragma once

#include "build_system_base.h"
#include "system/base/types.h"

//-----------------------------------------------------------------------------

namespace eastl
{
	template <typename TString>
	inline bool replace_all(TString& sSubject, const TString& sSource, const TString& sTarget)
	{
		uint64 nPos = sSubject.find_first_of(sSource);
		while (nPos != ZString::npos)
		{
			sSubject = sSubject.replace(nPos, sSource.length(), sTarget);
			nPos = sSubject.find_first_of(sSource);
		}
		return true;
	}

	template <typename TString>
	inline bool split(const TString& sSubject, TString& sLeft, TString& sRight, uint64 nPos)
	{
		if (nPos == TString::npos)
		{
			return false;
		}

		uint64 nLength = sSubject.length();
		if (nPos + 1 >= nLength)
		{
			return false;
		}
		sLeft = sSubject.substr(0, nPos);
		sRight = sSubject.substr(nPos + 1, nLength);
		return true;
	}

	template <typename TString>
	inline bool split_first(const TString& sSubject, TString& sLeft, TString& sRight, TString sSplit)
	{
		uint64 nPos = sSubject.find_first_of(sSplit);
		return split(sSubject, sLeft, sRight, nPos);
	}

	template <typename TString>
	inline bool split_last(const TString& sSubject, TString& sLeft, TString& sRight, TString sSplit)
	{
		uint64 nPos = sSubject.find_last_of(sSplit);
		return split(sSubject, sLeft, sRight, nPos);
	}

}
