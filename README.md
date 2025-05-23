# Opera GX Automatic Old UI reverter!


App that automizes reverting back to old ui.


As of recent (may 2025) opera gx enforced the new ugly UI, we don't want it, lets boycott!
This app runs in system tray, and reverts back to old ui automatically for you!
You can either compile it yourself (its open source, the source code is above, so you can see for yourself no viruses here).
Or download the precompiled exe by me (scroll down a bit for it).


Compilation:
I used visual studio 2022, compile using v143 toolkit, /std:c++20, Default Legacy MSVC compiler, 64 bit, multibyte character set, /SUBSYSTEM:WINDOWS, and as "Release x64".


!!!TO COMPILE YOU NEED: https://github.com/nlohmann/json/releases/download/v3.12.0/json.hpp!!! (put it in the same folder as the .cpp file).


How to properly automate it? Locate the downloaded app, go to: C:\Users\YOURUSERNAME\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup and put a shortcut file to the downloaded app in there (you can right click the app, click "make shortcut" and just put the shortcut in that folder and it works).


[Download Precompiled EXE](https://github.com/hihasTheAutist/opera-gx-automatic-old-ui-reverter/blob/main/Project5.exe)

Here's how it looks:


![Description](https://cdn.discordapp.com/attachments/734747183122874398/1375017469319712768/Screenshot_4250.png?ex=6830284f&is=682ed6cf&hm=15bb8caf0524f6a180605678b3e12c8ebdc0b1a9da320e4b814732d8d26b8cff&)
![Description](https://cdn.discordapp.com/attachments/734747183122874398/1375017469051273246/Screenshot_4251.png?ex=6830284f&is=682ed6cf&hm=f587950e22ca97425ee989479f86d64af8394432d586d76cc154bdde947ef16e&)


-----------------------------------------------------------------------------------------------------

# Troubleshooting:

I'm aware of a bug where the app sometimes doesn't work (happens if you rapidly close and open the browser).

I'm not able to fix it, troubleshoot would be to just restart opera gx slower bruh, give the app time to think.

I managed to recreate the bug, but i like really fast closed and opened opera gx, borderline windows laggy, so it should be fine.


This app doesn't require administrator rights to work properly.


-----------------------------------------------------------------------------------------------------

# Manual PERMANENT OPTION! (this could be risky as opera gx might be able to not function properly).


Locate the "Local State" file in "C:\Users\YOURUSERNAME\AppData\Roaming\Opera Software\Opera GX Stable"


Right Click -> Properties -> Tick "Read-Only" option -> Go to "Security" tab -> Click "edit" -> select your account -> tick "Write" in the "Deny" options.


This works, i tested it, opera is unable to revert back to the old looks, but it can't update this file at all, future updates might cause issues with this method.
