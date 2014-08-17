#include "unit-test/unit-test.h"

/**
 * Demonstrates a simple test that passes and one that fails.
 * Input/Output via serial.
 * To start the test, press 't'.
 */
test(ok) 
{
  int x=3;
  int y=3;
  assertEqual(x,y);
}

test(bad)
{
  int x=3;
  int y=3;
  assertNotEqual(x,y);
}

test(gottaBeKidding) {
	int i = 3*2;
	assertMoreOrEqual(i, 42);
}

test(HelloWorld) {
	assertNotEqual("Hello", "World");
}

UNIT_TEST_APP()