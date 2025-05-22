# Opera GX Automatic Old UI reverter!


App that automizes reverting back to old ui.


As of recent (may 2025) opera gx enforced the new ugly UI, we don't want it, lets boycott!
This app runs in system tray, and reverts back to old ui automatically for you!
You can either compile it yourself (its open source, the source code is above, so you can see for yourself no viruses here).
Or download the precompiled exe by me.


Compilation:
I used visual studio 2022, compile using v143 toolkit, /std:c++20, Default Legacy MSVC compiler, 64 bit, multibyte character set, /SUBSYSTEM:WINDOWS, and as "Releaxe x64".


!!!TO COMPILE YOU NEED: https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp!!! (put it in the same folder as the .cpp file).


How to properly automate it? Locate the downloaded app, go to: C:\Users\YOURUSERNAME\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup and put a shortcut file to the app in there (you can right click the app, click "make shortcut" and just put the shortcut in that folder and it works).


[Download Precompiled EXE](https://github.com/hihasTheAutist/opera-gx-automatic-old-ui-reverter/blob/main/Project5.exe)

-----------------------------------------------------------------------------------------------------

Manual PERMANENT OPTION! (this could be risky as opera gx might be able to not function properly).


Locate the "Local State" file in "C:\Users\YOURUSERNAME\AppData\Roaming\Opera Software\Opera GX Stable"


Right Click -> Properties -> Tick "Read-Only" window -> Go to "Security" tab -> Click "edit" -> select your account -> tick "Write" in the "Deny" options.


This works, i tested it, opera is unable to revert back to the old looks, but it can't update this file at all, future updates might cause issues with this method.
