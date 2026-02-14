[![CI](https://github.com/by-EAjks-Com/SDK-Template/actions/workflows/ci.yml/badge.svg)](https://github.com/by-EAjks-Com/Template-SDK/actions/workflows/ci.yml)

# SDK Template, C++ Development Best Practices @ by-EAjks.Com

## Building, Testing, and Deploying the SDK-Template Container Image

```powershell
cd /Path/To/SDK-Template
```

### Prerequisites

#### GPU Support on Linux

```bash
apt update
apt install --yes nvidia-container-toolkit
nvidia-ctk runtime configure --runtime=containerd && systemctl restart containerd
nvidia-ctk runtime configure --runtime=docker && systemctl restart docker
```

### Building in Interactive Mode

#### On a Linux Host

```bash
docker run \
    --interactive \
    --tty \
    --gpus all \
    --name sdk-template \
    --volume '/Path/To/SDK-Template:/src' \
    --workdir /build \
    docker.io/eajkseajks/cpp-cuda:1.0.0-sdk-core-ubuntu-24.04
```

```powershell
docker start --interactive sdk-template
```

#### On a Windows Host

```powershell
docker run `
    --interactive `
    --tty `
    --gpus all `
    --name sdk-template `
    --volume '/Path/To/SDK-Template:/src' `
    --workdir /build `
    docker.io/eajkseajks/cpp-cuda:1.0.0-sdk-core-ubuntu-24.04
```

```powershell
docker start --interactive sdk-template
```

#### In the Linux Guest

##### Installing the Missing Development Libraries/Tools

```bash
apt-get update

apt-get install --yes --no-install-recommends \
    wget \
    libpython3.12-dev \
    python3.12

apt-get autoremove --yes --purge

rm -rf /var/lib/apt/lists/*
```

```bash
mkdir /tools

wget -c https://github.com/Kitware/CMake/releases/download/v3.30.2/cmake-3.30.2-linux-x86_64.tar.gz -O - | tar -xz -C /tools
```

##### Compiling with the Gnu GCC/G++ Compilers

```bash
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
    /src/Code

ninja package
```

##### Compiling with the LLVM CLANG/CLANG++ Compilers

```bash
. /opt/intel/oneapi/setvars.sh

/tools/cmake-3.30.2-linux-x86_64/bin/cmake \
    -G "Ninja" \
    -D CMAKE_C_COMPILER=clang \
    -D CMAKE_C_COMPILER_AR=llvm-ar \
    -D CMAKE_CXX_COMPILER=clang++ \
    -D CMAKE_CXX_COMPILER_AR=llvm-ar \
    -D CMAKE_UNITY_BUILD=OFF \
    -D CMAKE_BUILD_TYPE=Debug \
    -D CMAKE_LINKER_TYPE=DEFAULT \
    -D PYBIND11_FINDPYTHON=ON \
    -D TEMPLATE_SDK_VERSION=1.2.3.4 \
    -D USE_PRECOMPILED_HEADERS=ON \
    -D BUILD_API_DOCUMENTATION=OFF \
    /src/Code

ninja package
```

##### Compiling with the Intel ICX/ICPX Compilers

```bash
. /opt/intel/oneapi/setvars.sh

/tools/cmake-3.30.2-linux-x86_64/bin/cmake \
    -G "Ninja" \
    -D CMAKE_C_COMPILER=icx \
    -D CMAKE_C_COMPILER_AR=xiar \
    -D CMAKE_CXX_COMPILER=icpx \
    -D CMAKE_CXX_COMPILER_AR=xiar \
    -D CMAKE_UNITY_BUILD=ON \
    -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_LINKER_TYPE=DEFAULT \
    -D PYBIND11_FINDPYTHON=ON \
    -D TEMPLATE_SDK_VERSION=1.2.3.4 \
    -D USE_PRECOMPILED_HEADERS=ON \
    -D BUILD_API_DOCUMENTATION=OFF \
    /src/Code

ninja package
```

##### Testing

```bash
apt install ./SDK-Template_1.2.3.4.deb

export PATH=/opt/by-EAjks.Com/SDK-Template/bin${PATH:+:${PATH}}

Benchmark -vvv
Demonstration -vvv
```

### Building in Batch Mode

#### On a Linux Host

```bash
docker build \
    --build-arg IMAGE_REPOSITORY=docker.io/eajkseajks \
    --build-arg DEVELOPMENT_IMAGE_NAME=cpp-cuda \
    --build-arg DEVELOPMENT_IMAGE_TAG=1.0.0-sdk-core-ubuntu-24.04 \
    --build-arg RUNTIME_IMAGE_NAME=cpp-cuda \
    --build-arg RUNTIME_IMAGE_TAG=1.0.0-runtime-core-ubuntu-24.04 \
    --build-arg TEMPLATE_SDK_VERSION=1.2.3.4 \
    --file DevOps/Docker/SDK-Template/Dockerfile \
    --tag ghcr.io/by-eajks-com/sdk-template:v1.2.3.4 \
    --tag ghcr.io/by-eajks-com/sdk-template:latest \
    .
```

#### On a Windows Host

```powershell
docker build `
    --build-arg IMAGE_REPOSITORY=docker.io/eajkseajks `
    --build-arg DEVELOPMENT_IMAGE_NAME=cpp-cuda `
    --build-arg DEVELOPMENT_IMAGE_TAG=1.0.0-sdk-core-ubuntu-24.04 `
    --build-arg RUNTIME_IMAGE_NAME=cpp-cuda `
    --build-arg RUNTIME_IMAGE_TAG=1.0.0-runtime-core-ubuntu-24.04 `
    --build-arg TEMPLATE_SDK_VERSION=1.2.3.4 `
    --file DevOps/Docker/SDK-Template/Dockerfile `
    --tag ghcr.io/by-eajks-com/sdk-template:v1.2.3.4 `
    --tag ghcr.io/by-eajks-com/sdk-template:latest `
    .
```
