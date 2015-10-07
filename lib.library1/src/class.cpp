// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file class.cpp
 *
 * @brief This demonstrates exporting functions.
 */

#include "class.h"
#include <stdlib.h> // NULL

const char*    TString::vStaticStr = NULL;

TString::TString()
{
    vStr = NULL;
}

TString::~TString()
{

}
const char** TString::GetStaticTStringPointer   ()
{
    return &vStaticStr;
}

const char* TString::GetStaticTString   ()
{
    return vStaticStr;
}
void TString::SetStaticTString   (const char* pStr)
{
    vStaticStr = pStr;
}

bool  TString::FuncTString   ()
{
    return true;
}

bool  TString::FuncNewTString   ()
{
    return true;
}
