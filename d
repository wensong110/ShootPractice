[33mcommit e1056bf5daa35451d761e661f11c68d6e2307234[m[33m ([m[1;36mHEAD -> [m[1;32mmain[m[33m)[m
Author: akkcdb110 <1148138385@qq.com>
Date:   Sat Oct 23 20:20:21 2021 +0800

    删除输出的文件

[1mdiff --git a/.gitignore b/.gitignore[m
[1mindex 6582eaf..7eea68e 100644[m
[1m--- a/.gitignore[m
[1m+++ b/.gitignore[m
[36m@@ -51,7 +51,7 @@[m [mPlugins/*/Binaries/*[m
 [m
 # Builds[m
 Build/*[m
[31m-[m
[32m+[m[32mout/*[m
 # Whitelist PakBlacklist-<BuildConfiguration>.txt files[m
 !Build/*/[m
 Build/*/**[m
[1mdiff --git a/out/Android_ASTC/Install_ShootPractice-armv7.bat b/out/Android_ASTC/Install_ShootPractice-armv7.bat[m
[1mdeleted file mode 100644[m
[1mindex 9900c33..0000000[m
[1m--- a/out/Android_ASTC/Install_ShootPractice-armv7.bat[m
[1m+++ /dev/null[m
[36m@@ -1,51 +0,0 @@[m
[31m-setlocal[m
[31m-if NOT "%UE_SDKS_ROOT%"=="" (call %UE_SDKS_ROOT%\HostWin64\Android\SetupEnvironmentVars.bat)[m
[31m-set ANDROIDHOME=%ANDROID_HOME%[m
[31m-if "%ANDROIDHOME%"=="" set ANDROIDHOME=D:/android/android-sdk_r24.4.1-windows/android-sdk-windows[m
[31m-set ADB=%ANDROIDHOME%\platform-tools\adb.exe[m
[31m-set DEVICE=[m
[31m-if not "%1"=="" set DEVICE=-s %1[m
[31m-for /f "delims=" %%A in ('%ADB% %DEVICE% shell "echo $EXTERNAL_STORAGE"') do @set STORAGE=%%A[m
[31m-@echo.[m
[31m-@echo Uninstalling existing application. Failures here can almost always be ignored.[m
[31m-%ADB% %DEVICE% uninstall com.YourCompany.ShootPractice[m
[31m-@echo.[m
[31m-@echo Installing existing application. Failures here indicate a problem with the device (connection or storage permissions) and are fatal.[m
[31m-%ADB% %DEVICE% install ShootPractice-armv7.apk[m
[31m-@if "%ERRORLEVEL%" NEQ "0" goto Error[m
[31m-%ADB% %DEVICE% shell rm -r %STORAGE%/UE4Game/ShootPractice[m
[31m-%ADB% %DEVICE% shell rm -r %STORAGE%/UE4Game/UE4CommandLine.txt[m
[31m-%ADB% %DEVICE% shell rm -r %STORAGE%/obb/com.YourCompany.ShootPractice[m
[31m-%ADB% %DEVICE% shell rm -r %STORAGE%/Android/obb/com.YourCompany.ShootPractice[m
[31m-%ADB% %DEVICE% shell rm -r %STORAGE%/Download/obb/com.YourCompany.ShootPractice[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-[m
[31m-@echo.[m
[31m-@echo Grant READ_EXTERNAL_STORAGE and WRITE_EXTERNAL_STORAGE to the apk for reading OBB file or game file in external storage.[m
[31m-%ADB% %DEVICE% shell pm grant com.YourCompany.ShootPractice android.permission.READ_EXTERNAL_STORAGE[m
[31m-%ADB% %DEVICE% shell pm grant com.YourCompany.ShootPractice android.permission.WRITE_EXTERNAL_STORAGE[m
[31m-[m
[31m-@echo.[m
[31m-@echo Installation successful[m
[31m-goto:eof[m
[31m-:Error[m
[31m-@echo.[m
[31m-@echo There was an error installing the game or the obb file. Look above for more info.[m
[31m-@echo.[m
[31m-@echo Things to try:[m
[31m-@echo Check that the device (and only the device) is listed with "%ADB$ devices" from a command prompt.[m
[31m-@echo Make sure all Developer options look normal on the device[m
[31m-@echo Check that the device has an SD card.[m
[31m-@pause[m
[1mdiff --git a/out/Android_ASTC/ShootPractice-armv7.apk b/out/Android_ASTC/ShootPractice-armv7.apk[m
[1mdeleted file mode 100644[m
[1mindex 3c6b732..0000000[m
Binary files a/out/Android_ASTC/ShootPractice-armv7.apk and /dev/null differ
[1mdiff --git a/out/Android_ASTC/Uninstall_ShootPractice-armv7.bat b/out/Android_ASTC/Uninstall_ShootPractice-armv7.bat[m
[1mdeleted file mode 100644[m
[1mindex b3e742d..0000000[m
[1m--- a/out/Android_ASTC/Uninstall_ShootPractice-armv7.bat[m
[1m+++ /dev/null[m
[36m@@ -1,19 +0,0 @@[m
[31m-setlocal[m
[31m-if NOT "%UE_SDKS_ROOT%"=="" (call %UE_SDKS_ROOT%\HostWin64\Android\SetupEnvironmentVars.bat)[m
[31m-set ANDROIDHOME=%ANDROID_HOME%[m
[31m-if "%ANDROIDHOME%"=="" set ANDROIDHOME=D:/android/android-sdk_r24.4.1-windows/android-sdk-windows[m
[31m-set ADB=%ANDROIDHOME%\platform-tools\adb.exe[m
[31m-set DEVICE=[m
[31m-if not "%1"=="" set DEVICE=-s %1[m
[31m-for /f "delims=" %%A in ('%ADB% %DEVICE% shell "echo $EXTERNAL_STORAGE"') do @set STORAGE=%%A[m
[31m-@echo.[m
[31m-@echo Uninstalling existing application. Failures here can almost always be ignored.[m
[31m-%ADB% %DEVICE% uninstall com.YourCompany.ShootPractice[m
[31m-@echo.[m
[31m-echo Removing old data. Failures here are usually fine - indicating the files were not on the device.[m
[31m-%ADB% %DEVICE% shell rm -r %STORAGE%/UE4Game/ShootPractice[m
[31m-%ADB% %DEVICE% shell rm -r %STORAGE%/UE4Game/UE4CommandLine.txt[m
[31m-%ADB% %DEVICE% shell rm -r %STORAGE%/obb/com.YourCompany.ShootPractice[m
[31m-%ADB% %DEVICE% shell rm -r %STORAGE%/Android/obb/com.YourCompany.ShootPractice[m
[31m-@echo.[m
[31m-@echo Uninstall completed[m
