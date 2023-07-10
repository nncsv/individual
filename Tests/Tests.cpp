#include "pch.h"
#include "CppUnitTest.h"
#include "../Individual/Priority.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:

		TEST_METHOD(IS_EMPTY)
		{
			Priority<int> p;
			Assert::IsTrue(p.is_Empty());

			p.add(2, 2);
			Assert::IsFalse(p.is_Empty());
		}

		TEST_METHOD(ADD)
		{
			Priority<int> p;
			int arr[6] = { -1, 0, 1, 1, 3 ,5 };
			p.add(3, 3);
			p.add(5, 5);
			p.add(0, 0);
			p.add(-1, -1);
			p.add(1, 1);
			p.add(1, 1);

			for (int i = 0; i < 6; i++) {
				Assert::AreEqual(arr[i], p.extract());
			}
		}


		TEST_METHOD(PLUS)
		{
			Priority<int> p1, p2, p3;
			int arr[6] = { -3, -2, -1, 1, 2, 3 };
			p1.add(1, 1);
			p1.add(2, 2);
			p1.add(3, 3);

			p2.add(-1, -1);
			p2.add(-2, -2);
			p2.add(-3, -3);

			p3 = p1 + p2;
			for (int i = 0; i < 6; i++) {
				Assert::AreEqual(arr[i], p3.extract());
			}
		}

		TEST_METHOD(SET)
		{
			Priority<int> p1;
			int arr[2] = { 1,2 };
			p1.set_value(1);
			p1.set_value(2);

			for (int i = 0; i < 2; i++) {
				Assert::AreEqual(arr[i], p1.extract());
			}
		}

		TEST_METHOD(GET)
		{
			Priority<int> p1;
			int arr[3] = { 1,2,3 };
			p1.set_value(1);
			p1.set_value(2);
			p1.set_value(3);

			Assert::AreEqual(1, p1.get_value());
			for (int i = 0; i < 3; i++) {
				Assert::AreEqual(arr[i], p1.extract());
			}
		}

		TEST_METHOD(EXTRACT)
		{
			Priority<int> p1;
			int arr[3] = { 2,3 };
			p1.set_value(1);
			p1.set_value(2);
			p1.set_value(3);

			Assert::AreEqual(1, p1.extract());
			for (int i = 0; i < 2; i++) {
				Assert::AreEqual(arr[i], p1.extract());
			}
		}

		TEST_METHOD(OPERATOR)
		{
			Priority<int> p1;
			int arr[3] = { 3,6,9 };
			int x;

			p1 << 3;
			p1 << 6;
			p1 << 9;

			for (int i = 0; i < 2; i++) {
				p1 >> x;
				Assert::AreEqual(arr[i], x);
			}

			try {
				p1 >> x;
			}
			catch (exception) {
				Assert::IsTrue(true);
			}
		}
	};
}
