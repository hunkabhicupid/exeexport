// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file function.h
 *
 * @brief This demonstrates exporting functions.
 */

#ifndef DLL1_FUNCTION_H
#define DLL1_FUNCTION_H

#include "dll_export.h"
#include <stdint.h>
#include <stddef.h>

#ifndef _WIN32
#define __cdecl
#endif

CP_BEGIN_EXTERN_C
DLL_EXPORT void __cdecl PrintFunc1();
CP_END_EXTERN_C

#endif
