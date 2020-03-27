#include <algorithm>
#include <random>
#include <specula/core/spectrum/common.hpp>
#include <specula/specula.hpp>

#include <catch2/catch.hpp>

using namespace specula;

TEST_CASE("Spectrum") {
  SECTION("Blackbody") {
    auto err = [](Float val, Float ref) { return std::abs(val - ref) / ref; };
    Float v[][3] = {
        {483, 6000, 3.1849e13},
        {600, 6000, 2.86772e13},
        {500, 3700, 1.59845e12},
        {600, 4500, 7.46497e12},
    };
    std::size_t n = sizeof(v) / sizeof(v[0]);
    for (std::size_t i = 0; i < n; ++i) {
      Float Le;
      blackbody(&v[i][0], 1, v[i][1], &Le);
      REQUIRE(err(Le, v[i][2]) <= 0.001);
    }

    for (Float T : {2700, 3000, 4500, 5600, 6000}) {
      Float lambda_max = 2.8977721e-3 / T * 1e9;
      Float lambda[3] = {Float(0.999 * lambda_max), lambda_max,
                         Float(1.001 * lambda_max)};
      Float Le[3];
      blackbody(lambda, 3, T, Le);
      REQUIRE(Le[0] < Le[1]);
      REQUIRE(Le[1] > Le[2]);
    }
  }
  SECTION("LinearUpsampleSimple") {
    Float lambda[5] = {0, 1, 2, 3, 4};
    Float val[5] = {1, 3, 5, 7, 9};
    const std::size_t n_in = 5;
    Float new_val[n_in];
    resample_linear_spectrum(lambda, val, n_in, lambda[0], lambda[n_in - 1],
                             n_in, new_val);
    for (std::size_t i = 0; i < 5; ++i)
      REQUIRE(val[i] == new_val[i]);
  }
  SECTION("LinearUpsampleSubset") {
    Float lambda[5] = {0, 1, 2, 3, 4};
    Float val[5] = {1, 3, 5, 7, 9};
    const std::size_t n_in = 5;
    const std::size_t n_out = 3;
    Float new_val[n_out];
    resample_linear_spectrum(lambda, val, n_in, lambda[1], lambda[3], n_out,
                             new_val);
    for (std::size_t i = 0; i < 3; ++i)
      REQUIRE(val[i + 1] == new_val[i]);
  }
  SECTION("LinearUpsampleHigher") {
    Float lambda[5] = {0, 1, 2, 3, 4};
    Float val[5] = {1, 3, 5, 7, 9};
    const std::size_t n_in = 5;
    const std::size_t n_out = 20;
    Float new_val[n_out];
    resample_linear_spectrum(lambda, val, n_in, lambda[1], lambda[3], n_out,
                             new_val);
    for (std::size_t i = 0; i < n_out; ++i) {
      Float t = i / Float(n_out - 1);
      REQUIRE(lerp(t, val[1], val[3]) == Approx(new_val[i]));
    }
  }
  SECTION("LinearUpsampling") {
    Float lambda[5] = {0, 1, 2, 3, 4};
    Float val[5] = {1, 3, 5, 7, 9};
    const std::size_t n_in = 5;
    const std::size_t n_out = 40;
    Float new_val[n_out];
    const Float lambda_min = 1.5, lambda_max = 3.75;
    resample_linear_spectrum(lambda, val, n_in, lambda_min, lambda_max, n_out,
                             new_val);
    for (std::size_t i = 0; i < n_out; ++i) {
      Float t = i / Float(n_out - 1);
      REQUIRE(lerp(t, 1 + 2 * lambda_min, 1 + 2 * lambda_max) ==
              Approx(new_val[i]));
    }
  }
  SECTION("LinearIrregularResample") {
    Float lambda_irreg[] = {-1.5, -0.5, 0.01, 0.6, 1,   2,     2.1, 3.4, 4.6,
                            5.7,  7,    8.2,  9,   9.8, 11.11, 12,  13,  14.7};
    const std::size_t n_in = sizeof(lambda_irreg) / sizeof(lambda_irreg[0]);
    Float val_irreg[n_in];
    for (std::size_t i = 0; i < n_in; ++i)
      val_irreg[i] = lambda_irreg[i] * lambda_irreg[i];
    const std::size_t n_out = 30;
    const Float lambda_min = -0.5, lambda_max = 14;
    Float new_val[n_out];
    resample_linear_spectrum(lambda_irreg, val_irreg, n_in, lambda_min,
                             lambda_max, n_out, new_val);
    for (std::size_t i = 0; i < n_out; ++i) {
      Float t = i / Float(n_out - 1);
      Float lambda = lerp(t, lambda_min, lambda_max);
      REQUIRE(std::abs(lambda * lambda - new_val[i]) < 0.75);
    }
  }
  SECTION("LinearDownsampleBasic") {
    Float lambda[5] = {0, 1, 2, 3, 4};
    Float val[5] = {1, 3, 5, 7, 9};
    const std::size_t n_in = sizeof(lambda) / sizeof(lambda[0]);
    const std::size_t n_out = 3;
    Float new_val[n_out];
    const Float lambda_min = 0, lambda_max = 4;
    resample_linear_spectrum(lambda, val, n_in, lambda_min, lambda_max, n_out,
                             new_val);
    REQUIRE(1.5 == Approx(new_val[0]));
    REQUIRE(5.0 == Approx(new_val[1]));
    REQUIRE(8.5 == Approx(new_val[2]));
  }
  SECTION("LinearDownsampleOffset") {
    Float lambda[5] = {0, 1, 2, 3, 4};
    Float val[5] = {1, 3, 5, 7, 9};
    const std::size_t n_in = sizeof(lambda) / sizeof(lambda[0]);
    const std::size_t n_out = 4;
    Float new_val[n_out];
    const Float lambda_min = 0.5, lambda_max = 3.5;
    resample_linear_spectrum(lambda, val, n_in, lambda_min, lambda_max, n_out,
                             new_val);
    REQUIRE(2.0 == Approx(new_val[0]));
    REQUIRE(4.0 == Approx(new_val[1]));
    REQUIRE(6.0 == Approx(new_val[2]));
    REQUIRE(8.0 == Approx(new_val[3]));
  }
  SECTION("LinearDownsampleIrreg") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<Float> dist(0.0, 1.0);

    std::vector<Float> lambda_irreg, val_irreg;
    lambda_irreg.push_back(-25);
    val_irreg.push_back(lambda_irreg.back() * lambda_irreg.back());
    for (std::size_t i = 0; i < 100; ++i) {
      lambda_irreg.push_back(lambda_irreg.back() + dist(gen));
      val_irreg.push_back(lambda_irreg.back() * lambda_irreg.back());
    }
    const std::size_t n_out = 10;
    Float new_val[n_out];
    const Float lambda_min = -5, lambda_max = 20;
    resample_linear_spectrum(lambda_irreg.data(), val_irreg.data(),
                             lambda_irreg.size(), lambda_min, lambda_max, n_out,
                             new_val);
    for (std::size_t i = 0; i < n_out; ++i) {
      Float t = Float(i) / Float(n_out - 1);
      Float lambda = lerp(t, lambda_min, lambda_max);
      REQUIRE(std::abs(lambda * lambda - new_val[i]) < 0.8);
    }
  }
}
