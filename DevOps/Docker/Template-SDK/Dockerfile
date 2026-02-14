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

ARG IMAGE_REPOSITORY
ARG DEVELOPMENT_IMAGE_NAME
ARG DEVELOPMENT_IMAGE_TAG
ARG RUNTIME_IMAGE_NAME
ARG RUNTIME_IMAGE_TAG
ARG TEMPLATE_SDK_VERSION

FROM ${IMAGE_REPOSITORY}/${DEVELOPMENT_IMAGE_NAME}:${DEVELOPMENT_IMAGE_TAG} AS build

LABEL maintainer="Andrea and Eric DELAGE <Contact@by-EAjks.Com>"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
 && apt-get install --yes --no-install-recommends \
        wget \
        libpython3.12-dev \
        python3.12 \
 && apt-get autoremove --yes --purge \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /tools

RUN wget -c https://github.com/Kitware/CMake/releases/download/v3.30.2/cmake-3.30.2-linux-x86_64.tar.gz -O - | tar -xz -C .

WORKDIR /src

COPY ./Code ./Code

WORKDIR /build

RUN . /opt/intel/oneapi/setvars.sh \
 && /tools/cmake-3.30.2-linux-x86_64/bin/cmake \
        -G "Ninja" \
        -D CMAKE_C_COMPILER=icx \
        -D CMAKE_C_COMPILER_AR=xiar \
        -D CMAKE_CXX_COMPILER=icpx \
        -D CMAKE_CXX_COMPILER_AR=xiar \
        -D CMAKE_UNITY_BUILD=OFF \
        -D CMAKE_BUILD_TYPE=Release \
        -D CMAKE_LINKER_TYPE=DEFAULT \
        -D PYBIND11_FINDPYTHON=ON \
        -D TEMPLATE_SDK_VERSION=${TEMPLATE_SDK_VERSION} \
        -D USE_PRECOMPILED_HEADERS=OFF \
        -D BUILD_API_DOCUMENTATION=ON \
        /src/Code \
 && ninja package

FROM ${IMAGE_REPOSITORY}/${RUNTIME_IMAGE_NAME}:${RUNTIME_IMAGE_TAG} AS deploy

LABEL maintainer="Andrea and Eric DELAGE <Contact@by-EAjks.Com>"

ENV DEBIAN_FRONTEND=noninteractive

COPY --from=build /build/Template-SDK_*.deb /root

RUN apt-get update \
 && apt-get install --yes --no-install-recommends \
        /root/Template-SDK_*.deb \
 && apt-get autoremove --yes --purge \
 && rm -f  /root/Template-SDK_*.deb \
 && rm -rf /var/lib/apt/lists/*

ENV PATH=/opt/by-EAjks.Com/Template-SDK/bin${PATH:+:${PATH}}
