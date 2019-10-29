mkdir build
mkdir build\release
conan remote add dev-server http://dev.kano.me:9300
conan remote update dev-server http://dev.kano.me:9300

cd build\release
conan install -r dev-server --build=missing --profile=..\..\conan-platforms\conan-profile-Windows-devstudio-2019.info ..\..
conan install --build=missing --profile=..\..\conan-platforms\conan-profile-Windows-devstudio-2019.info ..\..

cmake -DCMAKE_BUILD_TYPE=release ..\..
