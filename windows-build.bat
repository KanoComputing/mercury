::
:: windows-build.bat
::
:: Prepare Mercury to be built from Microsoft Developer Studio.
::
:: This Windows batch file will register and download conan prebuilt packages,
:: then call cmake to generate a release Solution file for Developer Studio.
:: Finally it will build the Static and Dynamic versions of the library in Release mode.
::
:: See the Windows section on the README file for software requirements.
::
:: For cpp client build steps, call windows-cppclient.bat
:: For Google Test built steps, call windows-gtest.bat
::

mkdir build
mkdir build\release
conan remote add dev-server http://dev.kano.me:9300
conan remote update dev-server http://dev.kano.me:9300

cd build\release

conan install -r dev-server --build=missing --profile=..\..\conan-platforms\conan-profile-Windows-devstudio-2019.info ..\..
conan install --build=missing --profile=..\..\conan-platforms\conan-profile-Windows-devstudio-2019.info ..\..

cmake -DCMAKE_BUILD_TYPE=release ..\..


@echo ">>> BUILDING MERCURY SHARED" >> build.log
msbuild.exe -p:Configuration=Release src\mercury_shared.vcxproj
if %errorlevel% neq 0 exit /b %errorlevel%

@echo ">>> BUILDING MERCURY STATIC" >> build.log
msbuild.exe -p:Configuration=Release src\mercury_static.vcxproj
if %errorlevel% neq 0 exit /b %errorlevel%
