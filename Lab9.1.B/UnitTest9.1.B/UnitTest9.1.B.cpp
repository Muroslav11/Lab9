#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab9.1.B/Lab9.1.B.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest91B
{
    TEST_CLASS(UnitTest91B)
    {
    public:

        TEST_METHOD(TestCountGoodMarks_WithUnion)
        {
            const int N = 3;
            Student* s = new Student[N];

            s[0].prizv = "S1";
            s[0].spec = COMPUTER_SCIENCE;
            s[0].physics = 3;
            s[0].math = 3;
            s[0].programming = 4;

            s[1].prizv = "S2";
            s[1].spec = INFORMATICS;
            s[1].physics = 4; 
            s[1].math = 3;
            s[1].numerical_methods = 4;

            s[2].prizv = "S3";
            s[2].spec = MATH_ECONOMICS;
            s[2].physics = 3;
            s[2].math = 4; 
            s[2].pedagogy = 5;

            int p, m, t;
            CountGoodMarks(s, N, p, m, t);

            Assert::AreEqual(1, p); 
            Assert::AreEqual(1, m); 
            Assert::AreEqual(2, t);

            delete[] s;
        }

        TEST_METHOD(TestPercentExcellent)
        {
            const int N = 2;
            Student* s = new Student[N];

            s[0].physics = 5;
            s[0].math = 5;

            s[1].physics = 5;
            s[1].math = 4;

            double result = PercentExcellentPhysicsAndMath(s, N);

            Assert::AreEqual(50.0, result, 0.01);

            delete[] s;
        }
    };
}