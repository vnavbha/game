#include "stdafx.h"
#include "CppUnitTest.h"
#include "system/base/types.h"
#include "system/base/memory/memory.h"
#include "system/base/memory/dlmalloc.h"

#include <Windows.h>
#include <tchar.h>

DEFINE_NEW_OPERATORS

//-----------------------------------------------------------------------------

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define ZMEMORY_REPORT(test) OutputDebugString(_T(#test ## "\n")); dlmalloc_stats();

namespace UnitTest
{		
	TEST_CLASS(base)
	{
	public:
		TEST_METHOD(BaseMemory)
		{
			auto start = dlmallinfo();

			TArray<int> a;
			for (int i = 0; i < 100; ++i)
			{
				a.push_back(i);
			}

			auto mid = dlmallinfo();
			Assert::IsTrue(memcmp(&start, &mid, sizeof(mallinfo)) != 0);

			a.clear();
			a.shrink_to_fit();
			
			auto end = dlmallinfo();			
			Assert::IsTrue(memcmp(&start, &end, sizeof(mallinfo)) == 0);
		}

		TEST_METHOD(EASTLArray)
		{
			TArray<uint32> aDigits;
			Assert::IsTrue(aDigits.empty());

			aDigits.push_back(1);
			aDigits.push_back(2);
			aDigits.push_back(3);

			Assert::IsTrue(aDigits.size() == 3);

			aDigits.erase(ZFnFind(aDigits.begin(), aDigits.end(), 2));
			Assert::IsTrue(aDigits.size() == 2);
			ZMEMORY_REPORT(EASTLArray);
		}

		TEST_METHOD(EASTLFixedHashMap)
		{
			TFixedHashMap<int, ZString, 5> aMap;
			Assert::IsTrue(aMap.max_size() == 5);
			aMap.insert(ZFnMakePair(1, ZString("1")));
			aMap.insert(ZFnMakePair(2, ZString("2")));
			aMap.insert(ZFnMakePair(3, ZString("3")));
			Assert::IsTrue(aMap.at(1) == ZString("1"));
			Assert::IsTrue(aMap[2] == ZString("2"));
			Assert::IsTrue(aMap.find(3) != aMap.end());			
		}
		
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

			wchar_t* channel = L"channel";
			wchar_t* format = L"%d";
			//ZString result = ZString().sprintf(ZString(ZString(channel) + ", " + format).c_str(), 2);


			ZWString result = ZWString().sprintf(ZWString(ZWString(channel) + L", " + format).c_str());
			Logger::WriteMessage(result.c_str());
		}

		TEST_METHOD(EASTLMap)
		{
			TMap<uint32, ZString> aMap;
			aMap.insert(ZFnMakePair(1, ZString("1")));
			aMap.insert(ZFnMakePair(2, ZString("2")));
			aMap.insert(ZFnMakePair(3, ZString("3")));
			Assert::IsTrue(aMap.at(1) == ZString("1"));
			Assert::IsTrue(aMap[2] == ZString("2"));
			Assert::IsTrue(aMap.find(3) != aMap.end());
		}

		TEST_METHOD(EASTLHashMap)
		{
			THashMap<uint32, ZString> aMap;
			aMap.insert(ZFnMakePair(1, ZString("1")));
			aMap.insert(ZFnMakePair(2, ZString("2")));
			aMap.insert(ZFnMakePair(3, ZString("3")));
			Assert::IsTrue(aMap.find(1) != aMap.end());
			Assert::IsTrue(aMap.find(2) != aMap.end());
			Assert::IsTrue(aMap.find(3) != aMap.end());
			Assert::IsTrue(aMap.find(4) == aMap.end());
		}

		TEST_METHOD(EASTLQueue)
		{
			TQueue<uint32> aQueue;
			aQueue.push(1);
			aQueue.push(2);
			aQueue.push(3);

			int nExpected = 1;
			while (!aQueue.empty())
			{
				int32 n = aQueue.front();
				aQueue.pop();
				Assert::IsTrue(n == nExpected);
				nExpected++;
			}
		}

		TEST_METHOD(EASTLDQueue)
		{
			TDequeue<uint32> aQueue;
			aQueue.push_back(2);
			aQueue.push_back(3);
			aQueue.push_front(1);

			int nExpected = 1;
			while (!aQueue.empty())
			{
				int32 n = aQueue.front();
				aQueue.pop_front();
				Assert::IsTrue(n == nExpected);
				nExpected++;
			}
		}

		TEST_METHOD(EASTLSharedPtr)
		{
			static int s_iCount = 0;
			class ZTest
			{
			public:
				ZTest()
				{
					s_iCount++;
				}
				~ZTest() 
				{
					s_iCount--;
				}
			};
			TSharedPtr<ZTest> pPtr(ZNEW ZTest());
			Assert::IsTrue(s_iCount == 1);
			pPtr = nullptr;
			Assert::IsTrue(s_iCount == 0);
		}
	};
}