# DllFinder
A simple tool to find manual mapped DLLs in a target process.

# Usage
`DllFinder.exe [PID`

# Example output
```
C:\Users\patate>DllFinder.exe 11828
PID : 11828
notepad.exe --> 0x00007FF7972A0000
ntdll.dll --> 0x00007FFBBF6F0000
KERNEL32.DLL --> 0x00007FFBBF3E0000
KERNELBASE.dll --> 0x00007FFBBCEB0000
GDI32.dll --> 0x00007FFBBDEC0000
win32u.dll --> 0x00007FFBBCDD0000
gdi32full.dll --> 0x00007FFBBD630000
msvcp_win.dll --> 0x00007FFBBD1B0000
ucrtbase.dll --> 0x00007FFBBD280000
USER32.dll --> 0x00007FFBBED70000
combase.dll --> 0x00007FFBBDA30000
RPCRT4.dll --> 0x00007FFBBEB20000
shcore.dll --> 0x00007FFBBF600000
msvcrt.dll --> 0x00007FFBBE6B0000
COMCTL32.dll --> 0x00007FFBA4BB0000
IMM32.DLL --> 0x00007FFBBD980000
bcryptPrimitives.dll --> 0x00007FFBBD4E0000
ADVAPI32.dll --> 0x00007FFBBF4B0000
sechost.dll --> 0x00007FFBBF560000
kernel.appcore.dll --> 0x00007FFBBAC90000
uxtheme.dll --> 0x00007FFBBA7C0000
clbcatq.dll --> 0x00007FFBBD8D0000
MrmCoreR.dll --> 0x00007FFBAB9C0000
SHELL32.dll --> 0x00007FFBBDEF0000
windows.storage.dll --> 0x00007FFBBAE90000
Wldp.dll --> 0x00007FFBBC810000
shlwapi.dll --> 0x00007FFBBF380000
MSCTF.dll --> 0x00007FFBBEC50000
OLEAUT32.dll --> 0x00007FFBBEA50000
TextShaping.dll --> 0x00007FFBAF610000
efswrt.dll --> 0x00007FFB9E060000
MPR.dll --> 0x00007FFBA0C50000
wintypes.dll --> 0x00007FFBB9960000
twinapi.appcore.dll --> 0x00007FFBB6B80000
oleacc.dll --> 0x00007FFBA4A50000
textinputframework.dll --> 0x00007FFBABEF0000
CoreMessaging.dll --> 0x00007FFBBA390000
WS2_32.dll --> 0x00007FFBBE900000
CoreUIComponents.dll --> 0x00007FFBBA030000
ntmarta.dll --> 0x00007FFBBBF30000
vcruntime140.dll --> 0x00007FFB9F640000
Found 41 modules.
Finding manual mapped dlls..

Module found --> 0x0000000180000000
Found 1 modules.
```