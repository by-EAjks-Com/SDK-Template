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

PROJECT(Benchmark VERSION ${Template-SDK_VERSION} LANGUAGES CXX)

CONFIGURE_FILE(
    ${PROJECT_SOURCE_DIR}/src/Version.h.in
    ${PROJECT_BINARY_DIR}/src/Version.h
    @ONLY)

FILE(GLOB_RECURSE BenchmarkExecutableHeaders ${PROJECT_SOURCE_DIR}/src/*.h)
FILE(GLOB_RECURSE BenchmarkExecutableSources ${PROJECT_SOURCE_DIR}/src/*.cpp)

ADD_EXECUTABLE(
    BenchmarkExecutable
        ${BenchmarkExecutableHeaders}
        ${BenchmarkExecutableSources})

TARGET_INCLUDE_DIRECTORIES(
    BenchmarkExecutable
        PRIVATE ${PROJECT_BINARY_DIR}/src
        PRIVATE ${PROJECT_SOURCE_DIR}/src)

IF(${USE_PRECOMPILED_HEADERS})
    TARGET_PRECOMPILE_HEADERS(
        BenchmarkExecutable
            PRIVATE ${PROJECT_SOURCE_DIR}/src/PrecompiledHeaders.h)
ENDIF()

TARGET_COMPILE_OPTIONS(
    BenchmarkExecutable
        PRIVATE $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-Wno-tautological-constant-compare>)

TARGET_LINK_LIBRARIES(
    BenchmarkExecutable
        PRIVATE CLI11::CLI11
        PRIVATE spdlog::spdlog_header_only
        PRIVATE Template-CPUSharedLibrary
        PRIVATE Template-GPUSharedLibrary)

SET_TARGET_PROPERTIES(
    BenchmarkExecutable
        PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION ON
            CXX_VISIBILITY_PRESET default
            VISIBILITY_INLINES_HIDDEN ON
            OUTPUT_NAME ${PROJECT_NAME})

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")

    ADD_CUSTOM_COMMAND(
        TARGET BenchmarkExecutable
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:BenchmarkExecutable> $<TARGET_FILE_DIR:BenchmarkExecutable>
        COMMAND_EXPAND_LISTS)

ENDIF()

INSTALL(
    TARGETS
        BenchmarkExecutable
    RUNTIME
        DESTINATION bin
        COMPONENT runtime)
