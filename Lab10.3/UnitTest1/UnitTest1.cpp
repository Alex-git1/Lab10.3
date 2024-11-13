#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab10.3/Lab10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Note people[2] = {
				{ "Pershui", "Ychen", "123456789", {1, 1, 2000} },
				{ "Drygui", "Ychen", "987654321", {2, 2, 1999} }
			};
			int size = 2;
			sortBySurname(people, size);
			Assert::AreEqual(string("Pershui"), people[0].surname);
			Assert::AreEqual(string("Drygui"), people[1].surname);
		}
	};
}
