OUTDATED
========
SNU is **outdated**. There is a newer, much slimmer and easier to use version available, called ![Skype Utility Project](https://github.com/dlehn/Skype-Utility-Project). It also has more features.

Use that instead of SNU!

SNU
===
Skype Notification Unf*cker (or Utility, if you're so inclined) is a small utility designed to adress "Skype for Windows Desktop"'s popup notification issues for users with multiple monitors.

When using the Skype Desktop version on a setup with multiple monitors, the tray popup notifications (for contacts signing on/off, new messages, etc.) will often be displayed off-screen since for some reason it seems to be too hard for our dear Skype developers to simply check how big the damn screen is.
Also, Skype offers (of course) no options to change on which screen or where on the screen notifications should be displayed.

SNU adresses these issues by overwriting Skype's default notification positions with something more sensible. The display position can (of course) be customized to your liking (choose on which monitor, in which corner and in which exact position notifications should pop up).

Installation
============
1. Acquire binaries (download the precompiled binaries offered in the "Releases" section or compile them yourself, if you don't trust me).
2. Copy *SNU.exe*, *SNU.dll* and *SNU.ini* to to your Skype installation directory (by default: *C:\Program Files (x86)\Skype\Phone*).
If you do not have the required rights to copy the files to the Skype folder (if it's somewhere in Program Files you will need administrator privileges on Win8), simply place them somewhere else (it doesn't matter as long as they're all in one folder) and adjust the path to the *Skype.exe* in step 3.
3. Open *SNU.ini* in your favorite text editor, have a look at the configuration options and adjust everything to your preferences.
4. From now on, start Skype by starting the *SNU.exe* instead of the normal *Skype.exe* (if you've got a shortcut to Skype on your desktop, change it to point to the *SNU.exe* instead of *Skype.exe*).

One drawback of this utility is that it won't work if you use Skype's "Start Skype when I Start Windows" option (since that will obviously launch Skype directly, and not via SNU).
In order to get that to work, disable the autostart option in Skype's options menu and instead place a shortcut to the *SNU.exe* in your autostart folder (on Windows 8 this is located in C:\Users\\*Your User Name*\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup, on older Windows version simply look for the folder in your start menu).

Troubleshooting
===============
Q: I've downloaded the precompiled binary version of SNU and it complains about some missing DLL files. What can I do?

A: You don't have the latest Visual C++ Redisitributable package installed. Get it from here: http://www.microsoft.com/en-us/download/details.aspx?id=40784

Q: SNU can't find my *Skype.exe*, why?

A: Make sure you have the correct app path set in the SNU.ini file. (If SNU is in the same folder as the Skype.exe, the entry should simply say *app=Skype.exe*, otherwise it should probably say *app=C:\Program Files (x86)\Skype\Phone\Skype.exe*).
