/**
 * @file dev.hpp
 * @brief Global Development
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2020-04-02
 */
#ifndef SPECULA_DEV_HPP_
#define SPECULA_DEV_HPP_

/**
 * @defgroup dev Development
 * Development based code, for prefomance and analysis.
 *
 * This code is not neccessary for the renderer to run, and is structured such
 * that in relase builds it is not included at all to improve preformce.
 * However, during development builds there files provide the ability for
 * indepth logging for debugging purposes. Detailed preformance statistics, and
 * object snapshots.
 */

#include "dev/error.hpp"
#include "dev/log.hpp"
#include "dev/prof.hpp"

#endif // SPECULA_DEV_HPP_
