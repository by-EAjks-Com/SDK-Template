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

#pragma once

// First-Party Headers
#include "byEAjksCom/Libraries/Template/GPU/PrecompiledHeaders.h"
#include "byEAjksCom/Libraries/Template/GPU/PreprocessorMacros.h"

// Third-Party Headers

// Standard C++/STL Headers

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

namespace byEAjksCom::Libraries::Template::GPU {

/// @brief This interface exposes methods and properties to ...
class TEMPLATE_GPU_DLL_EXPORT ObjectIF
{
public:

    /// @brief Constructs a new instance of the ObjectIF interface.
    explicit
    ObjectIF()
    noexcept;

    /// Avoids implicit generation of the copy constructor.
    explicit
    ObjectIF(
        const ObjectIF & other)
    noexcept = delete;

    /// Avoids implicit generation of the move constructor.
    explicit
    ObjectIF(
        ObjectIF && other)
    noexcept = delete;

    /// @brief Destructs the instance of the ObjectIF interface.
    virtual
    ~ObjectIF()
    noexcept;

    /// Avoids implicit generation of the copy assignment.
    auto
    operator=(
        const ObjectIF & other)
    noexcept -> ObjectIF & = delete;

    /// Avoids implicit generation of the move assignment.
    auto
    operator=(
        ObjectIF && other)
    noexcept -> ObjectIF & = delete;

    /// @brief Runs.
    virtual
    auto
    Run()
    noexcept -> void = 0;
};

} // byEAjksCom::Libraries::Template::GPU
