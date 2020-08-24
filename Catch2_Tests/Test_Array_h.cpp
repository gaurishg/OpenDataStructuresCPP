#include "Catch2.h"
#include "../OpenDataStructures/Array.h"

namespace Array_h_
{
	TEST_CASE("Check Array implementaion", "[Array]")
	{
		Array<int> arr(100);
		REQUIRE(arr.capacity() == 100);

		// Initialize all elements to zero
		for (int i{ 0 }; i < arr.capacity(); ++i)
			arr[i] = 0;

		SECTION("Check that all elements have been initialized to zero")
		{
			for (int i{ 0 }; i < arr.capacity(); ++i)
				REQUIRE(arr[i] == 0);
		}

		SECTION("Check for assignment operator")
		{
			SUCCEED("brr initiazing");
			Array<int> brr = arr;
			SUCCEED("brr initiazed");
			REQUIRE(brr.capacity() == arr.capacity());
			REQUIRE(brr == arr);

			SECTION("Check that it is doing shallow copy, because arrays are passed by reference in C++")
			{
				// First check that array has been copied
				for (int i{ 0 }; i < arr.capacity(); ++i)
					REQUIRE(arr[i] == brr[i]);

				// Now change some elements of arr
				arr[0] = 100;
				arr[5] = 100;

				REQUIRE(brr[0] == arr[0]);
				REQUIRE(brr[5] == arr[5]);

				Array<int> brr = arr;
				REQUIRE(arr == brr);

				Array<int> crr(arr);

				arr[0] = 100;
				REQUIRE(arr == brr);
				REQUIRE(arr == crr);

				SECTION("JUST Another Section")
				{
					Array<int> drr(50);
					for (int i{ 0 }; i < drr.capacity(); ++i)
						drr[i] = 99;

					arr = drr;

					REQUIRE(arr == drr);
					REQUIRE(arr != brr);
					REQUIRE(brr == crr);
					REQUIRE_FALSE(arr == brr);
				}
			}
		}
	}
}


