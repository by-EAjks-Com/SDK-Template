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

#include "byEAjksCom/Libraries/Template/CPU/ObjectBase.h"

// First-Party Headers
#include "byEAjksCom/Libraries/Template/CPU/PrecompiledHeaders.h"

// Third-Party Headers
#include <spdlog/spdlog.h>

// Standard C++/STL Headers
#include <memory>

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

namespace byEAjksCom::Libraries::Template::CPU {

ObjectBase::ObjectBase(
    ::std::shared_ptr<::spdlog::logger> logger)
noexcept
:   logger(::std::move(logger))
{
    this->logger->debug("entering ObjectBase::CTOR()");
}

ObjectBase::~ObjectBase()
noexcept
{
    this->logger->debug("entering ObjectBase::DTOR()");

    this->logger = nullptr;
}

auto
ObjectBase::Run()
noexcept -> void
{
    this->logger->debug("entering ObjectBase::Run()");
}

} // byEAjksCom::Libraries::Template::CPU
