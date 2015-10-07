MAYA
----

Maya Build System Initialization Process
----------------------------------------

1.	Get the latest maya from the following links
		
		Windows 	- \\benfps01\Dept\RnD\MayaBuildSystem\lib.base\windows\maya.exe
		Linux_64bit	- \\benfps01\Dept\RnD\MayaBuildSystem\lib.base\linux\maya
		Linux_32bit	- \\benfps01\Dept\RnD\MayaBuildSystem\lib.base\linux_32bit\maya
		
	Save the maya executable in an appropriate folder and add its path to 
	the environment variable PATH. Do not forget to set the path variable (even in linux).
	
2.	For Windows

		Once you have maya, open visual studio x86  command prompt. Make sure you have opened a 32 bit command prompt.
			ex- If you have visual studio 2013 you can find the command prompts at this 
			location : "C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools\Shortcuts"
			In case of vs 2013 
				for x86 - Developer Command Prompt for VS2013
				for x64 - VS2013 x64 Cross Tools Command Prompt
				
		Once you have opened the appropriate cmd prompt, type the following command
		
			maya --capture-env-as VSx86
			
		Now open visual studio x64 command prompt. See the above example. 
		Type the following command
		
			maya --capture-env-as VSx64
	
3.	For Linux
	
		In command prompt, run the following command
		
			In case of 32 bit machine :- maya --capture-env-as Linx86
			
			In case of 64 bit machine :- maya --capture-env-as Linx64

			
By doing so you can use maya in any command prompt(like git bash etc)
It is important that you type in the command exactly as mentioned.
	
#################################################################################################################################################

Usage of maya.config file
-------------------------

	There is one fixed config.maya file in .manage/maya folder (present under code.TallyWorld).

	There is another maya.config file existing in each lib or test folder. This file can
	be modified by the user. It provides user to enter details such as src files to be
	included, target name, dependencies etc. A template of this config file is present in 
	the .manage/maya folder. It is well commented and can be understood with ease. The config files 
	of lib.base and test of lib.base can be used as an example.
	
#################################################################################################################################################

WIP/Notes
---
	1. "maya fullclean" in linux. rm command executes but does nothing.(need to sit with maya makers and clarify this problem.)
	2. debug and release 32bit builds on linux 64bit machine.(This is yet to be done.)
	3. "maya debug release" (building two targets at once) this is not supported as of now.
	4. "maya -f my_maya_file testdebug" -f option can be used to use your own config file. Maya uses maya.config file by default.
	6. Currently if you tell maya to first build a dependent library, it builds the dependent library regardless of weather the lib was
		already built or not (i.e. it rebuilds it if the library was already built)
	7. The list of targets provided are:
			debug 			- builds debug(32bit)
			release			- builds release(32bit)
			debug64			- builds debug(64bit)
			release64		- builds release(64bit)
			debugrelease	- builds debug & release (32bit)
			debug64release64- builds debug & release (64bit)
			debugdebug64	- builds debug (32bit) & debug (64bit)
			releaserelease64- builds release (32bit) & release (64bit)
			all				- builds debug & release in 32bit and 64bit
			allclean		- Cleans all self builds
			fullclean		- Cleans all self builds and all builds of its dependencies 
			
			Note that no combination of fullclean or allclean is provided because maya by default rebuilds the target irrespective of weather 
			or not it is already built.
	8. Maya on linux 32bit machine and dynamic libraries as target are being worked on currently.
	9. Pre build block is yet to be added.
			
		
##################################################################################################################################################
Maintainers
-----------
	For any clarifications please contact the following

		Sweekrut S Joshi	- sweekrut.joshi@tallysolutions.com
		Raj Snehil Pathak 	- raj.pathak@tallysolutions.com
		
##################################################################################################################################################
