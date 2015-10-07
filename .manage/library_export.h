// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file library_export.h
 *
 * @brief This supports building the library1 as exporting as part of EXE and importing as part of DLLs
 *        LIB_IMPLEMENTATION => This tells compiler that is it compiling 
 *                           the headers of library1 as part of library compilation / 
 *                           as part of exe (if defined)  OR DLLs that depend on library1.                            
 *                           This primarily to differentiate whether we are exporting (by library1) 
 *                           or importing(dependent libs/exe).
 *        LIB_EXPORT =>     used to export / import stuff for / from library1
 */

#ifndef LIB_EXPORT_H
#define LIB_EXPORT_H

#if defined(_WIN32)   
    #if defined(LIB_IMPLEMENTATION)
        #define LIB_EXPORT __declspec(dllexport)            
    #else
        #define LIB_EXPORT __declspec(dllimport)            
    #endif  // defined(LIB_IMPLEMENTATION)    
#else  // defined(WIN32)
    #if defined(LIB_IMPLEMENTATION)
        #if __GNUC__ >= 4 || defined(__clang__)
            #define LIB_EXPORT __attribute__((visibility("default")))                
        #else
            #error Not Supported
        #endif
    #else
        #define LIB_EXPORT            
    #endif  // defined(LIB_IMPLEMENTATION)
#endif  

#if defined(__GNUC__)
#define TW_COMPILER_STD_GNUC  1
#define TW_COMPILER_GCC     1
#if defined(__clang__)
#define TW_COMPILER_CLANG   1
#endif
#elif defined(_MSC_VER)
#define TW_COMPILER_MSVC    1
#else
#error Please add support for your compiler
#endif

#ifdef TW_COMPILER_MSVC
    #define TW_FORCEINLINE 		        __forceinline
#elif defined(TW_COMPILER_GCC) || defined(TW_COMPILER_CLANG)
    #define TW_FORCEINLINE 		        inline __attribute__((always_inline))
#else
    #error Define the same for the target compiler
#endif 

#endif  // LIB_EXPORT_H
