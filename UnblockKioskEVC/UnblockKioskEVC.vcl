<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: UnblockKioskEVC - Win32 (WCE ARMV4I) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"ARMV4IRel/UnblockKioskEVC.res" /d UNDER_CE=500 /d _WIN32_WCE=500 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WCE_PLATFORM_STANDARDSDK_500" /d "THUMB" /d "_THUMB_" /d "ARM" /d "_ARM_" /d "ARMV4I" /r "d:\VS2008Projects\UnblockKioskEVC\UnblockKioskEVC.rc"" 
Creating temporary file "C:\DOCUME~1\matijaz\LOCALS~1\Temp\RSP370.tmp" with contents
[
/nologo /W3 /D _WIN32_WCE=500 /D "ARM" /D "_ARM_" /D "WCE_PLATFORM_STANDARDSDK_500" /D "ARMV4I" /D UNDER_CE=500 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /FR"ARMV4IRel/" /Fp"ARMV4IRel/UnblockKioskEVC.pch" /Yu"stdafx.h" /Fo"ARMV4IRel/" /QRarch4T /QRinterwork-return /O2 /MC /c 
"d:\VS2008Projects\UnblockKioskEVC\ParseCmdLine.cpp"
"d:\VS2008Projects\UnblockKioskEVC\Registry.cpp"
"d:\VS2008Projects\UnblockKioskEVC\UnblockKioskEVC.cpp"
]
Creating command line "clarm.exe @C:\DOCUME~1\matijaz\LOCALS~1\Temp\RSP370.tmp" 
Creating temporary file "C:\DOCUME~1\matijaz\LOCALS~1\Temp\RSP371.tmp" with contents
[
/nologo /W3 /D _WIN32_WCE=500 /D "ARM" /D "_ARM_" /D "WCE_PLATFORM_STANDARDSDK_500" /D "ARMV4I" /D UNDER_CE=500 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /FR"ARMV4IRel/" /Fp"ARMV4IRel/UnblockKioskEVC.pch" /Yc"stdafx.h" /Fo"ARMV4IRel/" /QRarch4T /QRinterwork-return /O2 /MC /c 
"d:\VS2008Projects\UnblockKioskEVC\StdAfx.cpp"
]
Creating command line "clarm.exe @C:\DOCUME~1\matijaz\LOCALS~1\Temp\RSP371.tmp" 
Creating temporary file "C:\DOCUME~1\matijaz\LOCALS~1\Temp\RSP372.tmp" with contents
[
commctrl.lib coredll.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"ARMV4IRel/UnblockKioskEVC.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib" /out:"ARMV4IRel/UnblockKioskEVC.exe" /subsystem:windowsce,5.00 /MACHINE:THUMB 
.\ARMV4IRel\ParseCmdLine.obj
.\ARMV4IRel\Registry.obj
.\ARMV4IRel\StdAfx.obj
.\ARMV4IRel\UnblockKioskEVC.obj
.\ARMV4IRel\UnblockKioskEVC.res
]
Creating command line "link.exe @C:\DOCUME~1\matijaz\LOCALS~1\Temp\RSP372.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
StdAfx.cpp
Compiling...
ParseCmdLine.cpp
Registry.cpp
UnblockKioskEVC.cpp
Generating Code...
Linking...
Creating command line "bscmake.exe /nologo /o"ARMV4IRel/UnblockKioskEVC.bsc"  .\ARMV4IRel\StdAfx.sbr .\ARMV4IRel\ParseCmdLine.sbr .\ARMV4IRel\Registry.sbr .\ARMV4IRel\UnblockKioskEVC.sbr"
Creating browse info file...
<h3>Output Window</h3>




<h3>Results</h3>
UnblockKioskEVC.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
