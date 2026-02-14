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
#include "byEAjksCom/Libraries/Template/CPU/ObjectFactoryIF.h"
#include "byEAjksCom/Libraries/Template/CPU/ObjectIF.h"

// Third-Party Headers
#include <spdlog/spdlog.h>

// Standard C++/STL Headers
#include <memory>

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

namespace byEAjksCom::Libraries::Template::CPU {

/// @brief This class implements ...
class TEMPLATE_CPU_DLL_EXPORT ObjectFactory final
:   public virtual ObjectFactoryIF
{
public:

    /// @brief Constructs a new instance of the ObjectFactory class.
    /// @param[in] logger The SpdLog logger used by the calling function.
    explicit
    ObjectFactory(
        ::std::shared_ptr<::spdlog::logger> logger)
    noexcept;

    /// Avoids implicit generation of the copy constructor.
    explicit
    ObjectFactory(
        const ObjectFactory & other)
    noexcept = delete;

    /// Avoids implicit generation of the move constructor.
    explicit
    ObjectFactory(
        ObjectFactory && other)
    noexcept = delete;

    /// @brief Destructs the instance of the ObjectFactory class.
    virtual
    ~ObjectFactory()
    noexcept;

    /// Avoids implicit generation of the copy assignment.
    auto
    operator=(
        const ObjectFactory & other)
    noexcept -> ObjectFactory & = delete;

    /// Avoids implicit generation of the move assignment.
    auto
    operator=(
        ObjectFactory && other)
    noexcept -> ObjectFactory & = delete;

    /// @brief Creates an instance.
    /// @return An instance.
    virtual
    auto
    CreateInstance()
    noexcept -> ::std::unique_ptr<ObjectIF> override final;

protected:

    ::std::shared_ptr<::spdlog::logger> logger { nullptr };
};

} // byEAjksCom::Libraries::Template::CPU
