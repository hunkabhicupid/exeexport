// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file data.h
 *
 * @brief This demonstrates exporting functions.
 */

#ifndef LIB2_DATA_H
#define LIB2_DATA_H

#include "library_export.h"
#include "class.h"
#include <stdint.h>

LIB_EXPORT extern const char gStr2[];

struct tStruct {
  bool uA; 
  bool uB; 
};

LIB_EXPORT extern struct tStruct gStructInstance;

LIB_EXPORT uint32_t* GetFileStaticPointer(tStruct& pA);

//To use library1
class LIB_EXPORT Derived : public TString {
public:
    Derived(){};
   ~Derived(){};
    bool FuncTString();
private:
};

#endif
