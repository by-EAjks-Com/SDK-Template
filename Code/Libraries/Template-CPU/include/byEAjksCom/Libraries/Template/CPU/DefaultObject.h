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
#include "byEAjksCom/Libraries/Template/CPU/PrecompiledHeaders.h"
#include "byEAjksCom/Libraries/Template/CPU/PreprocessorMacros.h"
#include "byEAjksCom/Libraries/Template/CPU/ObjectBase.h"

// Third-Party Headers
#include <spdlog/spdlog.h>

// Standard C++/STL Headers
#include <memory>

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

namespace byEAjksCom::Libraries::Template::CPU {

/// @brief This class implements ...
class TEMPLATE_CPU_DLL_HIDDEN DefaultObject final
:   public ObjectBase
{
public:

    /// @brief Constructs a new instance of the DefaultObject class.
    /// @param[in] logger The SpdLog logger used by the calling function.
    explicit
    DefaultObject(
        ::std::shared_ptr<::spdlog::logger> logger)
    noexcept;

    /// Avoids implicit generation of the copy constructor.
    explicit
    DefaultObject(
        const DefaultObject & other)
    noexcept = delete;

    /// Avoids implicit generation of the move constructor.
    explicit
    DefaultObject(
        DefaultObject && other)
    noexcept = delete;

    /// @brief Destructs the instance of the DefaultObject class.
    virtual
    ~DefaultObject()
    noexcept;

    /// Avoids implicit generation of the copy assignment.
    auto
    operator=(
        const DefaultObject & other)
    noexcept -> DefaultObject & = delete;

    /// Avoids implicit generation of the move assignment.
    auto
    operator=(
        DefaultObject && other)
    noexcept -> DefaultObject & = delete;

    /// @brief Runs.
    virtual
    auto
    Run()
    noexcept -> void override final;
};

} // byEAjksCom::Libraries::Template::CPU
