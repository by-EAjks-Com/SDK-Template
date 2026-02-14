//  SDK Template, by-EAjks.Com C++ Development Best Practices
//  Copyright (c) 2026 Andrea and Eric DELAGE <Contact@by-EAjks.Com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "byEAjksCom/Libraries/Template/GPU/DefaultObject.h"

// First-Party Headers
#include "byEAjksCom/Libraries/Template/GPU/PrecompiledHeaders.h"
#include "byEAjksCom/Libraries/Template/GPU/ObjectBase.h"

// Third-Party Headers
#include <spdlog/spdlog.h>

// Nvidia CUDA Headers
#include <cuda_runtime.h>

// Standard C++/STL Headers
#include <memory>

// Standard C-->C++ Headers
#include <cassert>
#include <cmath>
#include <cstdint>

__global__
void add(int n, float *x, float *y)
{
    int index  = threadIdx.x;
    int stride = blockDim.x;

    for (int i = index; i < n; i += stride)
    {
        y[i] = x[i] + y[i];
    }
}

namespace byEAjksCom::Libraries::Template::GPU {

DefaultObject::DefaultObject(
    ::std::shared_ptr<::spdlog::logger> logger)
noexcept
:   ObjectBase(::std::move(logger))
{
    this->logger->debug("entering DefaultObject::CTOR()");
}

DefaultObject::~DefaultObject()
noexcept
{
    this->logger->debug("entering DefaultObject::DTOR()");
}

auto
DefaultObject::Run()
noexcept -> void
{
    this->logger->debug("entering DefaultObject::Run()");

    ObjectBase::Run();

    int deviceCount { 0 };

    cudaError_t error_id { cudaGetDeviceCount(&deviceCount) };

    if (error_id != cudaSuccess)
    {
        this->logger->critical(
            "cudaGetDeviceCount returned {} -> {}",
            static_cast<int>(error_id),
            cudaGetErrorString(error_id));

        return;
    }

    deviceCount == 0 ?
        this->logger->info("There are no available device(s) that support CUDA") :
        this->logger->info("Detected {} CUDA capable device(s)", deviceCount);

    int N { 1 << 20 };

    float * x;
    float * y;

    cudaMallocManaged(&x, N * sizeof(float));
    cudaMallocManaged(&y, N * sizeof(float));

    for (int i = 0; i < N; i++)
    {
        x[i] = 1.0f;
        y[i] = 2.0f;
    }

    int blockSize { 256 };
    int numBlocks { (N + blockSize - 1) / blockSize };
    add<<<numBlocks, blockSize>>>(N, x, y);

    cudaDeviceSynchronize();

    float maxError { 0.0f };

    for (int i = 0; i < N; i++)
    {
        maxError = fmax(maxError, fabs(y[i] - 3.0f));
    }

    this->logger->trace("Max error: {}", maxError);

    cudaFree(x);
    cudaFree(y);
}

} // byEAjksCom::Libraries::Template::GPU
