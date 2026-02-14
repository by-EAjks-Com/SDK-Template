#!/bin/bash
#   SDK Template, by-EAjks.Com C++ Development Best Practices
#   Copyright (c) 2026 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <https://www.gnu.org/licenses/>.

rm    -rf GeneratePackagesForLinuxUsingGnuCompiler
mkdir -p  GeneratePackagesForLinuxUsingGnuCompiler
pushd     GeneratePackagesForLinuxUsingGnuCompiler

. /opt/intel/oneapi/setvars.sh

/tools/cmake-3.30.2-linux-x86_64/bin/cmake \
    -G "Ninja" \
    -D CMAKE_C_COMPILER=gcc \
    -D CMAKE_C_COMPILER_AR=ar \
    -D CMAKE_CXX_COMPILER=g++ \
    -D CMAKE_CXX_COMPILER_AR=ar \
    -D CMAKE_UNITY_BUILD=OFF \
    -D CMAKE_BUILD_TYPE=Debug \
    -D CMAKE_LINKER_TYPE=DEFAULT \
    -D PYBIND11_FINDPYTHON=ON \
    -D TEMPLATE_SDK_VERSION=1.2.3.4 \
    -D USE_PRECOMPILED_HEADERS=OFF \
    -D BUILD_API_DOCUMENTATION=ON \
    ../../../Code

ninja package

popd
