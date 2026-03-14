#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab9.3/Lab9.3.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RouteTests
{
	TEST_CLASS(RouteLogicTests)
	{
	public:

		// Тестуємо функцію сортування за номером
		TEST_METHOD(TestSortRoutesByNumber)
		{
			// 1. Arrange (Підготовка даних)
			const int size = 3;
			Route* testRoutes = new Route[size];
			testRoutes[0] = { "Point A", "Point B", 30 };
			testRoutes[1] = { "Point C", "Point D", 10 };
			testRoutes[2] = { "Point E", "Point F", 20 };

			// 2. Act (Виконання дії)
			sortRoutesByNumber(testRoutes, size);

			// 3. Assert (Перевірка результату)
			Assert::AreEqual(10, testRoutes[0].routeNumber);
			Assert::AreEqual(20, testRoutes[1].routeNumber);
			Assert::AreEqual(30, testRoutes[2].routeNumber);

			delete[] testRoutes;
		}

		// Тестуємо функцію пошуку індексу за номером
		TEST_METHOD(TestFindRouteIndex)
		{
			// Arrange
			const int size = 2;
			Route* testRoutes = new Route[size];
			testRoutes[0] = { "Lviv", "Kyiv", 101 };
			testRoutes[1] = { "Odesa", "Lviv", 202 };

			// Act
			int foundIndex = findRouteIndex(testRoutes, size, 202);
			int notFoundIndex = findRouteIndex(testRoutes, size, 999);

			// Assert
			Assert::AreEqual(1, foundIndex);      // Очікуємо індекс 1 для маршруту 202
			Assert::AreEqual(-1, notFoundIndex);  // Очікуємо -1, якщо маршруту немає

			delete[] testRoutes;
		}
	};
}