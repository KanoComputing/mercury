::
:: Build a simple CPP client to the Mercury Library
:: Requirements: Call the windows-build.bat
::

cd build\release
cmake -DCMAKE_BUILD_TYPE=Release ..\..

@echo ">>> BUILDING C++ CLIENT"
msbuild.exe -p:Configuration=Release src\cpp_client.vcxproj
if %errorlevel% neq 0 exit /b %errorlevel%
