# exeexport

Objective
 
To see if an executable(example tacs.exe) can export symbols (via static libraries it links to) and the same can be imported/used by the dynamic libraries(example our SVRs) it loads during run time.  This needs to be figured out on all targeted platforms like Windows, Mac OSX and Linux using their native compilers like cl, clang and gcc.
 
To further analyze the implications of this approach such that we can devise proper coding guidelines that help us avoid any incompatibility issues between the executables and dynamic libraries.
 
Approach
 
1.	Create one executable(exe) that links to 3 static libraries (lib.library1, lib.library2, lib.library3). The three static libraries actually export stuff.
a.	The lib.library1 exports a class with an inline function,  three static member functions, two non-inline member functions, one private data member, and one private static data member.
b.	The lib.library2 exports a two global data and a global function. It also:
i.	Defines  a structure. One of the global data exported is of this type of structure
ii.	It also has file level static data, pointer to which is returned by the global function exported.
iii.	It also uses lib.library1 and has a class derived from the class from lib.library1.
c.	The lib.library3 exports three global functions, three global functions within a hierarchical namespace. It also defines one global inline function in its header file.
d.	The executable links to these static libraries. The compilation of static libraries and executable define LIB_IMPLEMENTATION that helps determine that these symbols are exported.
e.	The executables uses all symbols from the libraries and also prints pointers to them to validate against the pointers in the dynamic libraries later.
f.	The executable also loads the dynamic libraries mentioned in point 2 and gets/executes the function exported by the dynamic libraries.
2.	Created two dynamic libraries (dll.svr1, dll.svr2) which import/use symbols from executable.
a.	The dynamic libraries uses the headers of all the static libraries and DONOT define LIB_IMPLEMENTATION that helps determine that these symbols are imported.
b.	The dynamic libraries have same code. They both export a function which uses all the symbols imported and also prints the pointers to them.
 
Build system changes 
1.	On mac os x, the DLL/.so equivalent used is bundles and not dylibs. There is difference between shared libraries (dylib) and dynamically loadable modules (bundles) on Mac OS X. It made more sense to use bundles as per our use case.
2.	While compilation, -fvisibility=hidden -fvisibility-inlines-hidden compiler flags are used on Mac OS X and Linux to not export symbols not needed and especially inline ones. This is done to match the default behavior on Windows.
3.	While building the executable, -force_load  and --whole-archive are passed to linker via clang and gcc respectively for each static library linked. This is done to not allow linker to strip the symbols exported but not referenced in the executable itself.
4.	The linker flag -rdynamic is used on GCC, to export symbols from an executable.
5.	The linker flag -bundle_loader <executable> is used on Clang, while building bundles to validate that the symbols are actually exported by the mentioned executable.
6.	On Mac OS X, the maya config files (build system) did not supported building the dynamic libraries. 
a.	As mentioned in point 1, instead of using -dynamiclib, now -bundle is used.
b.	Proper architecture was passed to build i386 and x86_64 dynamic libraries
 
 
Implications / to do
1.	Point 1 above. Need to find out more why not use dylib? There are few issues like
a.	While building dylibs, the same issue that some on windows of undefined symbols are thrown. On windows, you can pass the executable import library to resolve those symbols but there was no such concept on Mac OS X.
b.	Secondly, it was mentioned somewhere that dylibs cannot be unloaded once loaded, they still occupy the memory. Although the same can be used if they are loaded back again.
2.	Point 3 above, the same issue needs to addressed on Windows. If the symbols are not used in the executable, they are not getting exported. 
3.	Point 3 above, need to see what could be the implications of force loading the symbols. Does some unwanted / dead code also gets linked or exported? Is there an adverse effect on the binary size? Is there any other way to solve the problem.
4.	Point 4, --export_dynamic linker flag was not working. Need to check why?
5.	Also need to look into the incompatibility introduced due to structure/class data members / size change? Possible solutions, opaque types, size being one of the data member etc.
 
Observations
1.	On windows, the dynamic libraries should present either next to the executable or in the working directory (from where the executable is launched). On Mac / Linux, the dynamic libraries has to be in the working directory. Hence once the dynamic libraries built, they are copied on the respective paths. Obviously there would other standard paths where dynamic libraries must be looked up for loading. 
 
Please find the code in branch exeexport branch in team repo.
 
Compatibility checks 
 
Different version were created and compatibility was checked:
Please find the built binaries here. Source is also available there.
 
Version	What changed?	Results
Version 2	Exported class's inline function's logic changed 	Exe Version 1 and DLL version 2 / vice versa also worked as per expectation. The EXE and DLL returned value as the inline function with which they compiled.
Version 3	Exported global function's parameter removed	Exe version 2 and DLL version 3 and vice versa. DLL load failed.
Version 4	A new function introduced in Exported class and used in exe/dll	Exe version 3 and DLL version 4. DLL load failed as new function is not found in old exe.
Whereas Vice versa worked.
Version 5	Struct element's data type changed from bool to int	Exe version 4 and DLL version 5 and vice versa. Worked. The parameter name was same, only type changed. DOUBT: there should be some issue.
Version 6	A global inline function logic changed	Exe version 5 and DLL version 6 and vice versa - Worked as expected as all have their own versions of inline.
Version 7	A global inline function's parameters added at last	Exe version 6 and DLL version 7 and vice versa - Worked as exe and DLL used their own versions.
Version 8	A global inline function's optional parameter added at last	Exe version 7 and DLL version 8 and vice versa - Worked. Same as above.
Version 9 base for 10	Started using a value returned by non-inline class function in dll/exe	 
Version 10 	A non -inline class function logic changed to return true instead of false	Exe version 9 and DLL version 10 and vice versa. Logic of function in EXE was taken in both cases.
 
Version 11 base for 12	An exported global function started taking parameter of type of the structure.
That function started printing the size of the structure	 
Version 12	The structure changed: the type of one of the data members changed from int to bool.	Exe version 11 and DLL version 12 and vice versa. The structure size printed as per exe as the function in which size is calculated is exe exported function.
 
Version 13	The structure changed: one more data member added in between the earlier two.	Exe version 12 and DLL version 13 and vice versa. Size of structure as per exe. BUT structure passed is as per DLL and EXE. DOUBT: it did not crash bit must be incompatible.
Version 14	The newly added data member in structure being used in exe / dll.	Exe version 13 and DLL version 14 as per exe, as the new element was not used in the exported function. Whereas in Vice versa
i.	Exe print the value right as that member was set in the exe
ii.	BUT not in DLLs, hence it gets printed but not the right value. (incompatible)
Version 15	The newly added data member removed.	Exe version 14 and DLL version 15 - EXE worked fine as had the data member. Whereas in vice versa:
a.	DLL though when executed the exe's imported func, printed garbage value for  the data element deleted.
b.	Vice versa - EXE exported function do not expect that parameter, hence does not print it.
 
 
Findings (It can be done, looks good to me)
1.	Inline functions can create the possibility of version conflicts. An inline function gets expanded into the code (exe / dlls); therefore, if you later rewrite the function, it does not get updated unless the exe / dlls both are recompiled. 
a.	We need to introduce certain guidelines on the basis of findings like do not export inline functions and hence do not make any exported interface inline. 
b.	Although inline functions which will be used as is in EXE and DLL should be used only for really trivial tasks or for absolutely generic functions.
c.	We should change inline to non-inline or vice versa of already exposed symbols.
2.	We don't export types, we export linker symbols. There's nothing to export in the struct, it doesn't have any code. The change in the structure can bring in version incompatibility. The same applies to class's data members / size.
 
Binary Compatibility
 
Library N is said to be Binary Compatible with library O if it possible to replace an instance of library O with an instance of library N without making any changes to software that uses library O.
 
There is one obvious restriction to binary compatibility: it only applies to shared libraries because a library that is statically linked into an executable program cannot be changed after the fact.
 
API Compatibility
 
Library Nis said to be API compatible with library O if it is possible to recompile the software using library O and link it against library N without making any other changes to that software.
 
Binary compatibility and API compatibility are two different creatures: binary compatibility is really all about the library's ABI (Application Binary Interface) which is determined not only by its API, but also by the dependencies exposed through that API. For example: if your library is written in C++ and uses some structure ABC, and that use of ABC is exposed in the API you have exposed the dependency on ABC in your API. That means that your library will only be compatible with software that uses the same implementation of ABC as you do - or at least uses a compatible one. 
 
This may sound easier than it really is: Structure ABC can change, adding a member to it for example. 
 
So binary compatibility (in C++) is really about four things:
 
"	The behavior of a function changes so that it no longer meets its original specification,
"	object layout Ex: exported data items change 
"	API compatibility ex: An exported function is removed, interface of an exported function changes.
"	3rd Party:
"	Use of different compiler versions ex: they produce different C++ name mangling
"	exposed dependencies on third-part libraries (including the STL, Boost, the RTL, etc.)
 
SO,
 
If you can go through the compile and link steps without changing anything, you are API compatible. 
 
The next step is to run your program. When you do that, your OS will load your program into memory and scan it for any dependencies - any shared libraries you depend on. It will then try to find those libraries and load them into memory, looking for their dependencies, and so on. When they are all loaded, a final linking step is performed in which the functions (mangled and all) your application was looking for are all resolved. Then, your application starts running. If you got to here, you might be binary compatible. 
 
Might be? Well, remember the remark I made about "exposed dependencies" earlier? If our application goes through all its functional and unit tests, and we've testing everything, we are binary compatible. If we haven't tested everything, we're on thin ice.
 
Avoiding it
 
Removing a function or a method from the API is a sure way to break your API compatibility. 
Changing a type of member might break API compatibility, but will almost certainly break binary compatibility. Changing the order of members in a structure won't break API compatibility, but will break binary compatibility. 
I could go on.
 
Routine maintenance and innocent-looking changes may break it in very subtle ways. What may seem like simply recompiling your library might, in fact, break binary compatibility: you might be using a slightly different version of the RTL than you did last time, or you might be using different optimization settings, that change the alignment of your exposed structures a bit, breaking binary compatibility.
 
The point is: binary compatibility is a lot more fragile than API compatibility. Sure-fire ways to not break binary compatibility don't exist, but there are some ways to avoid the most common problems:
 
I have not read it full.
http://rlc.vlinder.ca/blog/2009/08/binary-compatibility/
 

OTHERS:
http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html
http://www.ibm.com/developerworks/library/l-shlibs/
https://developer.apple.com/library/mac/documentation/MacOSX/Conceptual/BPFrameworks/Concepts/VersionInformation.html
https://gcc.gnu.org/onlinedocs/libstdc++/manual/abi.html
http://www.pixelbeat.org/programming/linux_binary_compatibility.html

Useful links
 
Build
http://stackoverflow.com/questions/23200755/gcc-compiler-error-unrecognized-option-export-dynamic?rq=1
https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
http://stackoverflow.com/questions/23200755/gcc-compiler-error-unrecognized-option-export-dynamic?rq=1
http://stackoverflow.com/questions/16737347/shared-libraries-windows-vs-linux-method
http://stackoverflow.com/questions/3954137/mac-how-to-export-symbols-from-an-executable
https://blog.flameeyes.eu/2008/02/why-would-an-executable-export-symbols#gsc.tab=0
http://lists.apple.com/archives/unix-porting/2007/Aug/msg00027.html
http://lists.apple.com/archives/unix-porting/2007/Aug/msg00030.html
http://stackoverflow.com/questions/3065535/what-are-the-meanings-of-the-columns-of-the-symbol-table-displayed-by-readelf
 
Inline
https://msdn.microsoft.com/en-us/library/feffc7b5.aspx
https://msdn.microsoft.com/en-us/library/xa0d9ste.aspx
https://developer.apple.com/library/mac/documentation/DeveloperTools/Conceptual/CppRuntimeEnv/Articles/SymbolVisibility.html
http://stackoverflow.com/questions/2138110/how-does-a-compiler-deal-with-inlined-exported-functions
https://gcc.gnu.org/wiki/Visibility
 
Exe export unreferenced
http://stackoverflow.com/questions/17070536/keep-an-exported-function-from-being-deleted-by-the-linker
http://stackoverflow.com/questions/6687630/c-c-gcc-ld-remove-unused-symbols
https://cxwangyi.wordpress.com/2012/01/20/using-clang-linker-on-different-platforms/
http://stackoverflow.com/questions/16294842/how-to-disable-c-dead-code-stripping-in-xcode
http://stackoverflow.com/questions/805555/ld-linker-question-the-whole-archive-option
http://stackoverflow.com/questions/4175802/symbols-from-convenience-library-not-getting-exported-in-executable
 
Structure
http://stackoverflow.com/questions/15342138/how-to-export-import-a-c-struct-from-a-dll-to-a-console-application-using-dec
https://blog.flameeyes.eu/2009/11/the-importance-of-opaque-types#gsc.tab=0
 
ABI
https://en.wikipedia.org/wiki/Application_binary_interface

