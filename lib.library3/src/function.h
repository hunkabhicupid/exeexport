// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file function.h
 *
 * @brief This demonstrates exporting functions.
 */

#ifndef LIB3_FUNCTION_H
#define LIB3_FUNCTION_H

#include "library_export.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

LIB_EXPORT void* ExternFunc1(size_t);
LIB_EXPORT void* ExternFunc2(int);
LIB_EXPORT void* ExternFunc3();

// not exported
void* ExternNonExported(size_t p);

TW_FORCEINLINE void InlineFunc1(void* ptr, bool x, bool y = false) {
    printf("Executing InlineFunc1 - Modified");
}

namespace A {
namespace B {
    LIB_EXPORT void* ExternFunc1(size_t);
    LIB_EXPORT void* ExternFunc2(int);
    LIB_EXPORT void* ExternFunc3(char);
} // namespace A
} // namespace B

#endif
