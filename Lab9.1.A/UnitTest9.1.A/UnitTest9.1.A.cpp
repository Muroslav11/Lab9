#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab9.1.A/Lab9.1.A.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest91A
{
	TEST_CLASS(UnitTest91A)
	{
	public:

		TEST_METHOD(TestCountGoodMarks)
		{
			const int N = 2;
			Student* s = new Student[N];

			s[0] = { "Test1", 1, COMPUTER_SCIENCE, 4, 3, 4 }; 
			s[1] = { "Test2", 2, INFORMATICS, 5, 4, 3 };      

			int p, m, i;
			int total = CountGoodMarks(s, N, p, m, i);

			Assert::AreEqual(1, p); 
			Assert::AreEqual(1, m); 
			Assert::AreEqual(1, i); 
			Assert::AreEqual(3, total); 

			delete[] s;
		}

		TEST_METHOD(TestPercentExcellent)
		{
			const int N = 3;
			Student* s = new Student[N];

			s[0] = { "Ex1", 1, COMPUTER_SCIENCE, 5, 5, 4 }; 
			s[1] = { "Ex2", 1, MATH_ECONOMICS, 5, 4, 5 };  
			s[2] = { "Ex3", 2, INFORMATICS, 4, 5, 5 };

			double result = PercentExcellentPhysicsAndMath(s, N);

			Assert::AreEqual(33.33, result, 0.01);

			delete[] s;
		}
	};
}