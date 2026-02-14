@echo off
::  SDK Template, by-EAjks.Com C++ Development Best Practices
::  Copyright (c) 2026 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
::
::  This program is free software: you can redistribute it and/or modify
::  it under the terms of the GNU General Public License as published by
::  the Free Software Foundation, either version 3 of the License, or
::  (at your option) any later version.
::
::  This program is distributed in the hope that it will be useful,
::  but WITHOUT ANY WARRANTY; without even the implied warranty of
::  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
::  GNU General Public License for more details.
::
::  You should have received a copy of the GNU General Public License
::  along with this program.  If not, see <https://www.gnu.org/licenses/>.

rmdir /s/q GeneratePackagesForWindowsUsingMicrosoftVisualStudio
mkdir      GeneratePackagesForWindowsUsingMicrosoftVisualStudio
pushd      GeneratePackagesForWindowsUsingMicrosoftVisualStudio

call "C:\Program Files (x86)\Intel\oneAPI\setvars.bat"
call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

C:\Tools\cmake-3.30.2-windows-x86_64\bin\cmake.exe ^
    -G "Visual Studio 17 2022" ^
    -D CMAKE_C_COMPILER=cl ^
    -D CMAKE_C_COMPILER_AR=lib ^
    -D CMAKE_CXX_COMPILER=cl ^
    -D CMAKE_CXX_COMPILER_AR=lib ^
    -D CMAKE_UNITY_BUILD=ON ^
    -D CMAKE_BUILD_TYPE=Release ^
    -D CMAKE_LINKER_TYPE=DEFAULT ^
    -D PYBIND11_FINDPYTHON=ON ^
    -D CMAKE_TOOLCHAIN_FILE=C:\Tools\VCPKG\scripts\buildsystems\vcpkg.cmake ^
    -D TEMPLATE_SDK_VERSION=1.2.3.4 ^
    -D USE_PRECOMPILED_HEADERS=ON ^
    -D BUILD_API_DOCUMENTATION=OFF ^
    ..\..\..\Code

msbuild -property:Configuration=Release Template-SDK.sln

popd
