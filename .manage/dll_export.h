// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file dll_export.h
 *
 * @brief This supports building DLL 
 *
 *        DLL_IMPLEMENTATION => This tells compiler that is it compiling 
 *                           the headers for DLL or for eomebody else.
 *        DLL_EXPORT =>     used to export / import stuff for / from DLL1
 */

#ifndef DLL_EXPORT_H
#define DLL_EXPORT_H

#if defined(_WIN32)   
    #if defined(DLL_IMPLEMENTATION)
        #define DLL_EXPORT __declspec(dllexport)            
    #else
        #define DLL_EXPORT __declspec(dllimport)            
    #endif  // defined(DLL_IMPLEMENTATION)    
#else  // defined(WIN32)
    #if defined(DLL_IMPLEMENTATION)
        #if __GNUC__ >= 4 || defined(__clang__)
            #define DLL_EXPORT __attribute__((visibility("default")))                
        #else
            #error Not Supported
        #endif
    #else
        #define DLL_EXPORT            
    #endif  // defined(DLL_IMPLEMENTATION)
#endif    

#ifdef __cplusplus
#define CP_BEGIN_EXTERN_C       extern "C" {
#define CP_END_EXTERN_C         }
#else
#define CP_BEGIN_EXTERN_C
#define CP_END_EXTERN_C
#endif

#endif  // DLL_EXPORT_H
