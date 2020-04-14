/**
 * @file macros.hpp
 * @brief Global macros
 * @author Arden Rasmussen
 * @version 1.0
 * @date 2020-04-02
 * @ingroup global global-macros
 */
#ifndef SPECULA_GLOBAL_MACROS_HPP_
#define SPECULA_GLOBAL_MACROS_HPP_

/**
 * @defgroup global-macros Global Macros
 * @ingroup global
 *
 * A collection of commonly used preprocessor macros. Preferably this should be
 * empty.
 */

#define ALLOCA(TYPE, COUNT) (TYPE* ) alloca((COUNT) * sizeof(TYPE))

#endif /* end of include guard: SPECULA_GLOBAL_MACROS_HPP_ */
