#ifndef SPECULA_RAND_HPP_
#define SPECULA_RAND_HPP_

#include <random>

namespace specula {
namespace rand {
extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<double> unif_rand_dist;
inline double frand(){
  return unif_rand_dist(gen);
}

} // namespace rand
} // namespace specula

#endif // SPECULA_RAND_HPP_
