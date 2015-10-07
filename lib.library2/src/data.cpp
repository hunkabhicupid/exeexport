// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file data.cpp
 *
 * @brief This demonstrates exporting functions.
 */

#include "data.h"
#include <stdio.h>
const char gStr2[] = "Abhishek Jain";

struct tStruct gStructInstance = {
    false,
    false
};

static uint32_t sFileStatic = 0;

uint32_t * GetFileStaticPointer(tStruct &pA)
{
    if (pA.uA)
        printf("size of structure is %u\n", (unsigned int)(sizeof(tStruct)));
    else 
        printf("size of structure is %u\n", (unsigned int)(sizeof(tStruct)));

    return &sFileStatic;
}

bool Derived::FuncTString ()
{
    return false;
}
