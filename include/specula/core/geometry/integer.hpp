#ifndef SPECULA_CORE_GEOMETRY_INTEGER_HPP_
#define SPECULA_CORE_GEOMETRY_INTEGER_HPP_

#include <type_traits>

#include "matrix.hpp"
#include "normal.hpp"
#include "point.hpp"
#include "quaternion.hpp"
#include "vector.hpp"

#include "inheritance.hpp"

namespace specula {
GLM_FUNC_NAME(bit_count, bitCount, value);
GLM_FUNC_NAME(bitfield_extract, bitfieldExtract, value, offset, bits);
//   GLM_FUNC_NAME(bitfield_insert, bitfieldInsert, base, insert, offset, bits)
GLM_FUNC_NAME(bitfield_reverse, bitfieldReverse, value);
GLM_FUNC_NAME(find_lsb, findMSB, value);
GLM_FUNC_NAME(find_msb, findMSB, value);
// GLM_FUNC_NAME(imul_extended, imulExtended, x, y, msb, lsb)
GLM_FUNC_NAME(uadd_carray, uaddCarry, x, y, carry);
// GLM_FUNC_NAME(umul_extended, umulExtended, x, y, msb, lsb);
GLM_FUNC_NAME(usub_borrow, usubBorrow, x, y, borrow);
} // namespace specula

#endif // SPECULA_CORE_GEOMETRY_INTEGER_HPP_