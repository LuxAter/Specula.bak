#include "doctest.h"

#include "util/fmt.hpp"

TEST_CASE("Core") {
  CHECK(fmt::fmt("Test {}", 1) == "Test 1");
  CHECK(fmt::fmt("Test {} {}", 1) == "Test 1 {}");
  CHECK(fmt::fmt("Test {}", "HI") == "Test HI");
  CHECK(fmt::fmt("Test {}", 3.1415) == "Test 3.1415");
  CHECK(fmt::fmt("Test {} {} {}", 1, "HI", 3.1415) == "Test 1 HI 3.1415");
}

TEST_CASE("Escaping") {
  CHECK(fmt::fmt("Test {{}}", 1) == "Test {}");
  CHECK(fmt::fmt("Test {{}} {}", "HI") == "Test {} HI");
  CHECK(fmt::fmt("Test {} {{}}", 3.1415) == "Test 3.1415 {}");
}

TEST_CASE("Indexing") {
  CHECK(fmt::fmt("A: {1} B: {0}", 'B', 'A') == "A: A B: B");
}

TEST_CASE("Formatting") {
  CHECK(fmt::fmt("Val: {:5}", "7") == "Val:     7");
  CHECK(fmt::fmt("Val: {:5>}", "7") == "Val:     7");
  CHECK(fmt::fmt("Val: {:5=}", "7") == "Val:   7  ");
  CHECK(fmt::fmt("Val: {:5<}", "7") == "Val: 7    ");

  CHECK(fmt::fmt("Val: {:010>}", 3.1415) == "Val: 00003.1415");
  CHECK(fmt::fmt("Val: {:010=}", 3.1415) == "Val: 003.141500");
  CHECK(fmt::fmt("Val: {:010<}", 3.1415) == "Val: 3.14150000");

  CHECK(fmt::fmt("Val: {:10.3}", 3.14159265) == "Val:      3.142");
}

TEST_CASE("Combined") {
  CHECK(fmt::fmt("{0:=25=}", "Title") == "==========Title==========");
}

TEST_CASE("Wrap") {
  CHECK(fmt::wrap("Hello this is a very long line of text, it should be nicly "
                  "wrapped with the appropriate level of indentation on each "
                  "line after the first one. I hope that it works correctly, "
                  "that would be very nice of it. Thanks!") ==
        "Hello this is a very long line of text, it should be nicly wrapped "
        "with the\n  appropriate level of indentation on each line after the "
        "first one. I hope\n  that it works correctly, that would be very nice "
        "of it. Thanks!");
}
