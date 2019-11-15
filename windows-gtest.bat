::
:: Run the Google tests on top of the Mercury Library
:: Requirements: Call the windows-build.bat
::

cd build\release
cmake -DCMAKE_BUILD_TYPE=release ..\..

@echo ">>> BUILDING GOOGLE TESTS" >> build.log
msbuild.exe -p:Configuration=Release test\mercury_gtests.vcxproj
if %errorlevel% neq 0 exit /b %errorlevel%
