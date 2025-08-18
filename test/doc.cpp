#include <c2py/c2py.hpp>

///
inline int f1(int x) { return x; }

/// Implicit details - line 1.
inline int f2(int x) { return x; }

/**
 * Implicit details - line 1.
 * 
 * Implicit details - line 2.
 */
inline int f3(int x) { return x; }

/**
 * @details Explicit details - line 1.
 * Explicit details - line 2.
 * 
 * Implicit details - line 1.
 * 
 * @brief Explicit brief - line 1.
 * Explicit brief - line 2.
 */
inline int f4(int x) { return x; }

/// Inline math: \f$ x = 3.1415 \f$.
inline int f5(int x) { return x; }

/**
 * Multiline math:
 * \f[
 *   x = 3.1415 \; .
 * \f]
 * After math.
 */
inline int f6(int x) { return x; }

/**
 * Math environment:
 * \f{eqnarray*}{
 *   x &= 3.1415 \; ,
 *   y &= 2.7182 \; .
 * \f}
 * 
 * After math.
 */
inline int f7(int x) { return x; }

/**
 * Code block:
 * @code
 * #include <iostream>
 * int main() {
 *   std::cout << "Hello, world!" << std::endl;
 * }
 * @endcode
 * After code.
 */
inline int f8(int x) { return x; }

/**
 * Note:
 * @note Note - line 1.
 * Note - line 2.
 * 
 * After note.
 */
inline int f9(int x) { return x; }

/**
 * Warning:
 * @warning Warning - line 1.
 * Warning - line 2.
 * 
 * After warning.
 */
inline int f10(int x) { return x; }

/**
 * @param x Parameter - line 1.
 * Parameter - line 2.
 */
inline int f11(int x) { return x; }

/**
 * @return Return - line 1.
 * Return - line 2.
 */
inline int f12(int x) { return x; }

/**
 * @ingroup mygroup
 * @brief Brief - line 1.
 * Brief - line 2.
 * 
 * @details Details - line 1.
 * Details - line 2.
 * 
 * Multiline math: \f[ x = 3.1415 \; . \f]
 * 
 * List 1:
 * * List 1 - item 1.
 * * List 1 - item 2.
 * 
 *   * List 1 - item 2.1.
 * 
 * * List 1 - item 3.
 * 
 * After list.
 * 
 * @param x Parameter - line 1.
 * @return Return - line 1.
 */
inline int f13(int x) { return x; }

#include "doc.wrap.cxx"
