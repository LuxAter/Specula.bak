#include <specula/core/parallel.hpp>

#include <atomic>

#include <catch2/catch.hpp>

using namespace specula;

TEST_CASE("Parallel") {
  SECTION("Basics") {
    parallel_init();

    std::atomic<int> counter{0};
    parallel_for([&](int64_t) { ++counter; }, 1000, 1);
    REQUIRE(1000 == counter);

    counter = 0;
    parallel_for([&](int64_t) { ++counter; }, 1000, 19);
    REQUIRE(1000 == counter);

    counter = 0;
    parallel_for([&](Point2i) { ++counter; }, Point2i(15, 14));
    REQUIRE((15 * 14) == counter);

    parallel_cleanup();
  }
  SECTION("Do Nothing") {
    parallel_init();

    std::atomic<int> counter{0};
    parallel_for([&](int64_t) { ++counter; }, 0);
    REQUIRE(0 == counter);

    counter = 0;
    parallel_for([&](Point2i) { ++counter; }, Point2i(0, 0));
    REQUIRE(0 == counter);

    parallel_cleanup();
  }
}
