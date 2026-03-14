#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab9.2.B/Lab9.2.B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92B
{
	TEST_CLASS(UnitTest92B)
	{
	public:
		TEST_METHOD(TestGetAverageGradeUnion)
		{
			Student s1;
			s1.specialty = COMPUTER_SCIENCE;
			s1.physics = 5; s1.math = 4; s1.programming = 3;
			Assert::AreEqual((5 + 4 + 3) / 3.0, GetAverageGrade(s1), 0.0001);
		}

		TEST_METHOD(TestIsBetterLogicVariant10)
		{
			Student s1 = { "Ivanenko", 1, COMPUTER_SCIENCE, 3, 3 }; s1.programming = 3;
			Student s2 = { "Petrenko", 1, LABOR_TRAINING, 5, 5 }; s2.pedagogy = 5;
			Assert::IsTrue(IsBetter(s1, s2, true));
		}

		TEST_METHOD(TestLastNameSorting)
		{
			// Використовуємо латиницю для стабільності тесту
			// За Варіантом 10: прізвища за спаданням (Z перед A)
			Student s1 = { "Zaitsev", 1, COMPUTER_SCIENCE, 5, 5 }; s1.programming = 5;
			Student s2 = { "Abramov", 1, COMPUTER_SCIENCE, 5, 5 }; s2.programming = 5;

			// IsBetter має повернути true, бо "Z" > "A" (спадання)
			bool result = IsBetter(s1, s2, true);
			Assert::IsTrue(result);
		}
	};
}