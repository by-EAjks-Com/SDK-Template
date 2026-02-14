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

PROJECT(Template_CPU VERSION ${Template-SDK_VERSION} LANGUAGES CXX)

FILE(GLOB_RECURSE Template_CPUPythonBindingHeaders ${PROJECT_SOURCE_DIR}/include/*.h)
FILE(GLOB_RECURSE Template_CPUPythonBindingSources ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Let's define the Python binding of the C++ shared library.

PYBIND11_ADD_MODULE(
    Template_CPUPythonBinding
        MODULE
            ${Template_CPUPythonBindingHeaders}
            ${Template_CPUPythonBindingSources})

IF(${USE_PRECOMPILED_HEADERS})
    TARGET_PRECOMPILE_HEADERS(
        Template_CPUPythonBinding
            PRIVATE ${PROJECT_SOURCE_DIR}/src/PrecompiledHeaders.h)
ENDIF()

TARGET_COMPILE_DEFINITIONS(
    Template_CPUPythonBinding
        PRIVATE $<$<CONFIG:Debug>:SPDLOG_DEBUG_ON>
        PRIVATE SPDLOG_TRACE_ON)

TARGET_COMPILE_OPTIONS(
    Template_CPUPythonBinding
        PRIVATE $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-Wno-tautological-constant-compare>)

TARGET_LINK_LIBRARIES(
    Template_CPUPythonBinding
        PRIVATE pybind11::headers
        PRIVATE spdlog::spdlog_header_only
        PRIVATE Template-CPUSharedLibrary)

SET_TARGET_PROPERTIES(
    Template_CPUPythonBinding
        PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION ON
            CXX_VISIBILITY_PRESET default
            VISIBILITY_INLINES_HIDDEN ON
            OUTPUT_NAME ${PROJECT_NAME})

# Let's define where the python binding is installed.

INSTALL(
    TARGETS
        Template_CPUPythonBinding
    LIBRARY
        DESTINATION bindings/python/${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
        COMPONENT runtime
    RUNTIME
        DESTINATION bindings/python/${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR}
        COMPONENT runtime)
