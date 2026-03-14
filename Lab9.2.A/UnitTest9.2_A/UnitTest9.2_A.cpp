#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab9.2.A/Lab9.2.A.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92A
{
	TEST_CLASS(UnitTest92A)
	{
	public:
		TEST_METHOD(TestGetAverageGrade)
		{
			Student s = { "“ест", 1, COMPUTER_SCIENCE, 5, 4, 3 };
			double expected = 4.0;
			double actual = GetAverageGrade(s);
			Assert::AreEqual(expected, actual, 0.0001);
		}

		TEST_METHOD(TestIsBetterLogic)
		{
			Student s1 = { "јаченко", 1, COMPUTER_SCIENCE, 3, 3, 3 };
			Student s2 = { "Ѕбченко", 1, INFORMATICS,      4, 4, 4 };
			bool result = IsBetter(s1, s2, true);
			Assert::IsTrue(result);
		}

		TEST_METHOD(TestLastNameSorting)
		{
			Student s1 = { "яковенко", 2, MATH_ECONOMICS, 5, 5, 5 };
			Student s2 = { "јвраменко", 2, MATH_ECONOMICS, 5, 5, 5 };
			bool result = IsBetter(s1, s2, true);
			Assert::IsTrue(result);
		}
	};
}