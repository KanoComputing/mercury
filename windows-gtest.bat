::
:: Run the Google tests on top of the Mercury Library
:: Requirements: Call the windows-build.bat
::

mkdir -p build\release
cd build\release
cmake -DCMAKE_BUILD_TYPE=Release ..\..

@echo ">>> BUILDING GOOGLE TESTS" >> build.log
msbuild.exe -p:Configuration=Release test\mercury_gtests.vcxproj
if %errorlevel% neq 0 exit /b %errorlevel%
