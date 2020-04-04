#include "specula/core/rng.hpp"
#include "specula/global/functions.hpp"
#include <specula/core/sampling.hpp>

#include <catch2/catch.hpp>

using namespace specula;

TEST_CASE("Sampling") {
  SECTION("Distribution1D") {
    SECTION("Discrete") {
      Float func[4] = {0, 1, 0, 3};
      Distribution1D dist(func, sizeof(func) / sizeof(func[0]));
      REQUIRE(4 == dist.count());

      REQUIRE(0.0 == dist.discrete_pdf(0));
      REQUIRE(0.25 == dist.discrete_pdf(1));
      REQUIRE(0.0 == dist.discrete_pdf(2));
      REQUIRE(0.75 == dist.discrete_pdf(3));

      Float pdf, remapped;
      REQUIRE(1.0 == dist.sample_discrete(0.0, &pdf));
      REQUIRE(0.25 == pdf);
      REQUIRE(1.0 == dist.sample_discrete(0.125, &pdf, &remapped));
      REQUIRE(0.25 == pdf);
      REQUIRE(0.5 == Approx(remapped));
      REQUIRE(1.0 == dist.sample_discrete(0.24999, &pdf));
      REQUIRE(0.25 == pdf);
      REQUIRE(3.0 == dist.sample_discrete(0.250001, &pdf));
      REQUIRE(0.75 == pdf);
      REQUIRE(3.0 == dist.sample_discrete(0.625, &pdf, &remapped));
      REQUIRE(0.75 == pdf);
      REQUIRE(0.5 == Approx(remapped));
      REQUIRE(3.0 == dist.sample_discrete(one_minus_epsilon, &pdf));
      REQUIRE(0.75 == pdf);
      REQUIRE(3.0 == dist.sample_discrete(1.0, &pdf));
      REQUIRE(0.75 == pdf);

      Float u = 0.25, u_max = 0.25;
      for (int i = 0; i < 20; ++i) {
        u = next_float_down(u);
        u_max = next_float_up(u_max);
      }
      for (; u < u_max; u = next_float_up(u)) {
        int interval = dist.sample_discrete(u);
        if (interval == 3)
          break;
        REQUIRE(1 == interval);
      }
      REQUIRE(u < u_max);
      for (; u <= u_max; u = next_float_up(u)) {
        int interval = dist.sample_discrete(u);
        REQUIRE(3 == interval);
      }
    }
    SECTION("Continuous") {
      Float func[5] = {1, 1, 2, 4, 8};
      Distribution1D dist(func, sizeof(func) / sizeof(func[0]));
      REQUIRE(5 == dist.count());

      Float pdf;
      int offset;
      REQUIRE(0.0 == dist.sample_continuous(0.0, &pdf, &offset));
      REQUIRE(dist.count() * 1.0 / 16.0 == Approx(pdf));
      REQUIRE(0 == offset);

      REQUIRE(0.8 == Approx(dist.sample_continuous(0.5f, &pdf, &offset)));
      REQUIRE(0.9 == Approx(dist.sample_continuous(0.75f, &pdf, &offset)));
      REQUIRE(dist.count() * 8.0 / 16.0 == Approx(pdf));
      REQUIRE(4 == offset);

      REQUIRE(0.0 == Approx(dist.sample_continuous(0.0f, &pdf)));
      REQUIRE(1.0 == Approx(dist.sample_continuous(1.0f, &pdf)));

    }
  }
}
