// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file function.cpp
 *
 * @brief This demonstrates exporting functions.
 */

#include "function.h"
#include "data.h"

void* ExternFunc1(size_t p)
{
    return (void*)(p);
}

void* ExternFunc2(int p)
{
    return (void*)(uintptr_t)(gStr2);
}

void* ExternFunc3()
{
    return (void*)nullptr;
}

void* ExternNonExported(size_t p)
{
    return (void*)(uintptr_t)(p);
}

namespace A {
namespace B {
void* ExternFunc1(size_t p)
{
    return ExternNonExported(p);
}

void* ExternFunc2(int p)
{
    return (void*)(uintptr_t)(p);
}

void* ExternFunc3(char p)
{
    return (void*)(uintptr_t)(p);
}

} // namespace A
} // namespace B
