// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file data.cpp
 *
 * @brief This demonstrates importing and using the constructs 
 *        from dynamic libraries (implicitly linked)
 */

#include "function.h"
#include "data.h"
#include "class.h"
#include <stdio.h>

#ifndef _WIN32
#define __cdecl
#if defined(__APPLE__) // mac
#include <dlfcn.h>
#else // linux
#include <dlfcn.h>
#endif
#else
#include <windows.h>
#endif

#define UNUSED(expr) do { (void)(expr); } while (0)

typedef void (__cdecl *PrintFunc) ();

int __cdecl main () 
{
    // VALIDATE EXE
    // Are you able to call?
    // function.h
    void *a;
    a = ExternFunc1(32U);
    a = ExternFunc2(32);
    a = ExternFunc3();    
    a = ExternNonExported(32U);
    
    InlineFunc1(a, true);
    
    a = A::B::ExternFunc1(32U);
    a = A::B::ExternFunc2(32);
    a = A::B::ExternFunc3('b');
    
    // class.h
    TString b;
    bool c;
    const char* v;
    c = b.InlineFuncTString   ();
    if (c) {
        printf("TString::InlineFuncTString returned true\n");
    } else {
        printf("TString::InlineFuncTString returned false\n");
    }
    
    v = TString::GetStaticTString ();    
    TString::SetStaticTString   ("Abhishek");  
    v = TString::GetStaticTString ();
    c = b.FuncTString   ();
    c = b.FuncNewTString();
    if (c) {
        printf("TString::FuncNewTString returned true\n");
    } else {
        printf("TString::FuncNewTString returned false\n");
    }
    UNUSED(c);
    
    // data.h
    tStruct ab = {false, false};
    uint32_t* ptr = GetFileStaticPointer(ab);
    gStructInstance.uA = true;
    gStructInstance.uB = true;
    uintptr_t ptr2 = (uintptr_t)&gStr2;
    
    // Printing pointers
    // function.h
    printf("EXE exporting\n");
    printf("ExternFunc1: %p\n", ExternFunc1);
    printf("ExternFunc2: %p\n", ExternFunc2);
    printf("ExternFunc3: %p\n", ExternFunc3);
    printf("InlineFunc1: %p\n", InlineFunc1);    
    printf("ExternNonExported: %p\n", ExternNonExported);
    printf("A::B::ExternFunc1: %p\n", A::B::ExternFunc1);
    printf("A::B::ExternFunc2: %p\n", A::B::ExternFunc2);
    printf("A::B::ExternFunc3: %p\n", A::B::ExternFunc3);
    // class.h
    printf("Class Static: TString::GetStaticTStringPointer%p\n", TString::GetStaticTStringPointer);
    printf("Class Static: TString::GetStaticTString: %p\n", TString::GetStaticTString);
    printf("Class Static: TString::SetStaticTString%p\n", TString::SetStaticTString);
    //bool (TString::*fptr)() = &TString::InlineFuncTString;
    //printf("Class Static: TString::InlineFuncTString%p\n", (void*)fptr);
    // data.h
    printf("GetFileStaticPointer: %p\n", ptr);
    printf("&gStr2: %p\n", (void*)ptr2);
    printf("&gStructInstance: %p\n", &gStructInstance);
    printf("GetStaticTString %s\n", v);

    // SVR1
#ifdef _WIN32
    HMODULE dll = LoadLibraryA ("svr1.dll");
    if (!dll)
	    printf ("Error: %d\n", ::GetLastError());	
#elif defined(__APPLE__) 
    void*   dll = dlopen("./svr1.so", RTLD_LAZY);
    if (!dll)
	    printf ("Error: %s\n", dlerror());
#else // Linux
    void*   dll = dlopen("./svr1.so", RTLD_LAZY);
    if (!dll)
	    printf ("Error: %s\n", dlerror());		
#endif

#ifdef _WIN32
    PrintFunc func1 = (PrintFunc) ::GetProcAddress (dll, "PrintFunc1");
#elif defined(__APPLE__) 
    PrintFunc func1 = (PrintFunc) dlsym (dll, "PrintFunc1");
#else // Linux
    PrintFunc func1 = (PrintFunc) dlsym (dll, "PrintFunc1");
#endif
    func1();

    // SVR2
#ifdef _WIN32
    dll = LoadLibraryA ("svr2.dll");
    if (!dll)
	    printf ("Error: %d\n", ::GetLastError());	
#elif defined(__APPLE__) 
    dll = dlopen("./svr2.so", RTLD_LAZY);
    if (!dll)
	    printf ("Error: %s\n", dlerror());
#else // Linux
    dll = dlopen("./svr2.so", RTLD_LAZY);
    if (!dll)
	    printf ("Error: %s\n", dlerror());		
#endif

#ifdef _WIN32
    func1 = (PrintFunc) ::GetProcAddress (dll, "PrintFunc1");
#elif defined(__APPLE__) 
    func1 = (PrintFunc) dlsym (dll, "PrintFunc1");
#else // Linux
    func1 = (PrintFunc) dlsym (dll, "PrintFunc1");
#endif
    func1();

    return 0;
}
