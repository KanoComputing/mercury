::
:: windows-build.bat
::
:: Prepare Mercury to be built from Microsoft Developer Studio.
::
:: This Windows batch file will register and download conan prebuilt packages,
:: then call cmake to generate a release Solution file for Developer Studio.
::
:: See the Windows section on the README file for software requirements.
::

mkdir build
mkdir build\debug
conan remote add dev-server http://dev.kano.me:9300
conan remote update dev-server http://dev.kano.me:9300

cd build\debug
conan install -r dev-server --build=missing --profile=..\..\conan-platforms\conan-profile-Windows-devstudio-2019.info ..\..
conan install --build=missing --profile=..\..\conan-platforms\conan-profile-Windows-devstudio-2019.info ..\..

cmake -DCMAKE_BUILD_TYPE=debug ..\..

cd build\debug
msbuild.exe src\mercury_static.vcxproj
msbuild.exe test\mercury_gtests.vcxproj
