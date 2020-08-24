#include "Catch2.h"
#include "../OpenDataStructures/ArrayStack.h"

TEST_CASE("Check Default Constructor for ArrayStack", "[ArrayStack]")
{
	ArrayStack<int> stack;
	REQUIRE(stack.capacity() == 100);
	REQUIRE(stack.size() == 0);
	REQUIRE(stack.get_top() == -1);
}

TEST_CASE("Check Resize operation", "[ArrayStack]")
{
	ArrayStack<int> stack(2);
	REQUIRE(stack.capacity() == 2);
	REQUIRE(stack.size() == 0);
	REQUIRE(stack.get_top() == -1);

	// "First: Pop on empty stack throws"
	REQUIRE_THROWS_AS(stack.pop(), PopFromEmptyStack);

	// Push an element
	REQUIRE_NOTHROW(stack.push(1));
	REQUIRE(stack.capacity() == 2);
	REQUIRE(stack.size() == 1);
	REQUIRE(stack.get_top() == 0);
	REQUIRE(stack.peep() == 1);
	REQUIRE(stack[0] == 1);

	// Since array should have only two elements, lets check out of bounds behaviour
	REQUIRE_THROWS_AS(stack[2], ArrayIndexOutOfBounds);

	// Push another element
	REQUIRE_NOTHROW(stack.push(2));
	REQUIRE(stack.capacity() == 2);
	REQUIRE(stack.size() == 2);
	REQUIRE(stack.get_top() == 1);
	REQUIRE(stack.peep() == 2);
	REQUIRE(stack[0] == 1);
	REQUIRE(stack[1] == 2);

	// Push one more, this time array should be resized to capacity 5
	REQUIRE_NOTHROW(stack.push(3));
	REQUIRE(stack.capacity() == 5);
	REQUIRE(stack.size() == 3);
	REQUIRE(stack.get_top() == 2);
	REQUIRE(stack.peep() == 3);
	REQUIRE(stack[0] == 1);
	REQUIRE(stack[1] == 2);
	REQUIRE(stack[2] == 3);

	// Pop an element
	int temp;
	REQUIRE_NOTHROW(temp = stack.pop());
	REQUIRE(temp == 3);
	REQUIRE(stack.capacity() == 5);
	REQUIRE(stack.size() == 2);
	REQUIRE(stack.get_top() == 1);
	REQUIRE(stack.peep() == 2);
	REQUIRE(stack[0] == 1);
	REQUIRE(stack[1] == 2);
	// Although we have removed the element from stack, but nothing is stopping us from 
	// getting the element through raw array access
	REQUIRE(stack[2] == 3);

	// Free the array
	REQUIRE_NOTHROW(stack.free());
	REQUIRE(stack.capacity() == 0);
	REQUIRE(stack.size() == 0);
	REQUIRE(stack.get_top() == -1);
	REQUIRE_THROWS_AS(stack.peep(), PeepOnEmptyStack);
	REQUIRE_THROWS_AS(stack.pop(), PopFromEmptyStack);
	REQUIRE_THROWS_AS(stack[0], ArrayIndexOutOfBounds);
	REQUIRE_THROWS_AS(stack[1], ArrayIndexOutOfBounds);

	// Push one element, array should be resized to one
	REQUIRE_NOTHROW(stack.push(1));
	REQUIRE(stack.capacity() == 1);
	REQUIRE(stack.size() == 1);
	REQUIRE(stack.get_top() == 0);
	REQUIRE(stack.peep() == 1);
	REQUIRE(stack[0] == 1);
	REQUIRE_THROWS_AS(stack[1], ArrayIndexOutOfBounds);

	// Push one more element, array should resize to three
	REQUIRE_NOTHROW(stack.push(2));
	REQUIRE(stack.capacity() == 3);
	REQUIRE(stack.size() == 2);
	REQUIRE(stack.get_top() == 1);
	REQUIRE(stack.peep() == 2);
	REQUIRE(stack[0] == 1);
	REQUIRE(stack[1] == 2);
	REQUIRE_NOTHROW(stack[2]);
	REQUIRE_THROWS_AS(stack[3], ArrayIndexOutOfBounds);
}