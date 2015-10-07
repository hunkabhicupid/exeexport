// Sri Ganeshji : Sri Balaji : Sri Pitreshwarji : Sri Durgaji : Sri Venkateshwara
/**
 * @file function.cpp
 *
 * @brief This demonstrates exporting functions.
 */
#include "print.h"
#include "function.h"
#include "data.h"
#include "class.h"
#include <stdio.h>

#define UNUSED(expr) do { (void)(expr); } while (0)

void __cdecl PrintFunc1()
{    
    // VALIDATE EXE
    // Are you able to call?
    // function.h
    void *a;
    a = ExternFunc1(32U);
    a = ExternFunc2(32);
    a = ExternFunc3();    
    //a = ExternNonExported(32U);
    
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
    printf("\nSVR 2 importing\n");
    printf("ExternFunc1: %p\n", ExternFunc1);
    printf("ExternFunc2: %p\n", ExternFunc2);
    printf("ExternFunc3: %p\n", ExternFunc3);
    printf("InlineFunc1: %p\n", InlineFunc1);    
    //printf("ExternNonExported: %p\n", ExternNonExported);
    printf("A::B::ExternFunc1: %p\n", A::B::ExternFunc1);
    printf("A::B::ExternFunc2: %p\n", A::B::ExternFunc2);
    printf("A::B::ExternFunc3: %p\n", A::B::ExternFunc3);
    // class.h
    printf("Class Static: TString::GetStaticTStringPointer%p\n", TString::GetStaticTStringPointer);
    printf("Class Static: TString::GetStaticTString: %p\n", TString::GetStaticTString);
    printf("Class Static: TString::SetStaticTString%p\n", TString::SetStaticTString);
    //printf("Class Static: TString::InlineFuncTString%p\n", &TString::InlineFuncTString);
    // data.h
    printf("GetFileStaticPointer: %p\n", ptr);
    printf("&gStr2: %p\n", (void*)ptr2);
    printf("&gStructInstance: %p\n", &gStructInstance);
    printf("GetStaticTString %s\n", v);
}

