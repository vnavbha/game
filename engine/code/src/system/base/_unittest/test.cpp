#include "stdafx.h"
#include "CppUnitTest.h"
#include "eastl/utility.h"
#include "eastl/string.h"
#include "eastl/map.h"
#include "eastl/vector.h"
#include "eastl/array.h"
#include "eastl/algorithm.h"
#include "system/base/types.h"
#include "system/base/memory/memory.h"
#include "system/base/memory/dlmalloc.h"

#include <memory>
#include <Windows.h>
#include <tchar.h>

//-----------------------------------------------------------------------------

// EASTL also wants us to define this (see string.h line 197)
int Vsnprintf8(char8_t* pDestination, size_t n, const char8_t* pFormat, va_list arguments)
{
#ifdef _MSC_VER
	return _vsnprintf_s(pDestination, n, n, pFormat, arguments);
#else
	return _vsnprintf_s(pDestination, n, n, pFormat, arguments);
#endif
}


//-----------------------------------------------------------------------------

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define ZMEMORY_REPORT(test) OutputDebugString(_T(#test ## "\n")); dlmalloc_stats();

namespace UnitTest
{		
	TEST_CLASS(base)
	{
	public:
		
		TEST_METHOD(EASTLString)
		{
			ZString sTest = "test";
			ZString sTest2 = "test_2";
			ZString sTest3 = "test";

 			Assert::IsTrue(sTest3 == sTest);
			Assert::IsFalse(sTest == sTest2);
			
			sTest += "_append";
			ZString sTest4 = sTest + "_append";

			ZString sExpected = "test_append_append";

			Assert::IsTrue(sTest4 == sExpected);
		}

		TEST_METHOD(EASTLArray)
		{
			TArray<uint32> aDigits;
			Assert::IsTrue(aDigits.empty());
			for (int i = 0; i < 100; ++i)
			{
				aDigits.push_back(i);
			}
			aDigits.clear();
			aDigits.push_back(1);
			aDigits.push_back(2);
			aDigits.push_back(3);

			
			Assert::IsTrue(aDigits.size() == 3);
			
			aDigits.erase(TFind(aDigits.begin(), aDigits.end(), 2));
			Assert::IsTrue(aDigits.size() == 2);
			ZMEMORY_REPORT(EASTLArray);
		}
		
		TEST_METHOD(EASTLMap)
		{
			TMap<uint32, ZString> aMap;
			aMap.insert(TPair(1, ZString("1")));
			aMap.insert(TPair(2, ZString("2")));
			aMap.insert(TPair(3, ZString("3")));
			Assert::IsTrue(aMap.at(1) == ZString("1"));
			Assert::IsTrue(aMap[2] == ZString("2"));
			Assert::IsTrue(aMap.find(3) != aMap.end());
		}
	};
}