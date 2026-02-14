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

PROJECT(Template-CPU VERSION ${Template-SDK_VERSION} LANGUAGES CXX)

CONFIGURE_FILE(
    ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/Version.h.in
    ${PROJECT_BINARY_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/Version.h
    @ONLY)

FILE(GLOB_RECURSE Template-CPULibraryHeaders ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/*.h ${PROJECT_SOURCE_DIR}/include/byEAjksCom/Libraries/Template/CPU/*.h)
FILE(GLOB_RECURSE Template-CPULibrarySources ${PROJECT_SOURCE_DIR}/src/byEAjksCom/Libraries/Template-CPU.cpp ${PROJECT_SOURCE_DIR}/src/byEAjksCom/Libraries/Template/CPU/*.cpp)

# Let's define the static version of the library.

ADD_LIBRARY(
    Template-CPUStaticLibrary
        STATIC
            ${Template-CPULibraryHeaders}
            ${Template-CPULibrarySources})

TARGET_INCLUDE_DIRECTORIES(
    Template-CPUStaticLibrary
        INTERFACE $<INSTALL_INTERFACE:include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE   $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

IF(${USE_PRECOMPILED_HEADERS})
    TARGET_PRECOMPILE_HEADERS(
        Template-CPUStaticLibrary
            PRIVATE   ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/PrecompiledHeaders.h)
ENDIF()

TARGET_COMPILE_DEFINITIONS(
    Template-CPUStaticLibrary
        PUBLIC    TEMPLATE_CPU_LIBRARY_IS_STATIC
        PRIVATE   COMPILING_TEMPLATE_CPU_LIBRARY
        PRIVATE   $<$<CONFIG:Debug>:SPDLOG_DEBUG_ON>
        PRIVATE   SPDLOG_TRACE_ON)

TARGET_COMPILE_OPTIONS(
    Template-CPUStaticLibrary
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Wno-deprecated-gpu-targets>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Xcompiler=-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-Wno-tautological-constant-compare>)

TARGET_LINK_LIBRARIES(
    Template-CPUStaticLibrary
        PRIVATE   $<$<CXX_COMPILER_ID:GNU>:pthread>
        PRIVATE   spdlog::spdlog_header_only)

SET_TARGET_PROPERTIES(
    Template-CPUStaticLibrary
        PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION ON
            CXX_VISIBILITY_PRESET default
            VISIBILITY_INLINES_HIDDEN ON
            OUTPUT_NAME ${PROJECT_NAME})

# Let's define the shared version of the library.

ADD_LIBRARY(
    Template-CPUSharedLibrary
        SHARED
            ${Template-CPULibraryHeaders}
            ${Template-CPULibrarySources})

TARGET_INCLUDE_DIRECTORIES(
    Template-CPUSharedLibrary
        INTERFACE $<INSTALL_INTERFACE:include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include-api>
        PUBLIC    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        PRIVATE   $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

IF(${USE_PRECOMPILED_HEADERS})
    TARGET_PRECOMPILE_HEADERS(
        Template-CPUSharedLibrary
            PRIVATE   ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/PrecompiledHeaders.h)
ENDIF()

TARGET_COMPILE_DEFINITIONS(
    Template-CPUSharedLibrary
        PUBLIC    TEMPLATE_CPU_LIBRARY_IS_SHARED
        PRIVATE   COMPILING_TEMPLATE_CPU_LIBRARY
        PRIVATE   $<$<CONFIG:Debug>:SPDLOG_DEBUG_ON>
        PRIVATE   SPDLOG_TRACE_ON)

TARGET_COMPILE_OPTIONS(
    Template-CPUSharedLibrary
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Wno-deprecated-gpu-targets>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:GNU>,$<COMPILE_LANGUAGE:CUDA>>:-Xcompiler=-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-fvisibility=hidden>
        PRIVATE   $<$<AND:$<CXX_COMPILER_ID:IntelLLVM>,$<COMPILE_LANGUAGE:CXX>>:-Wno-tautological-constant-compare>)

TARGET_LINK_LIBRARIES(
    Template-CPUSharedLibrary
        PRIVATE   $<$<CXX_COMPILER_ID:GNU>:pthread>
        PRIVATE   spdlog::spdlog_header_only)

SET_TARGET_PROPERTIES(
    Template-CPUSharedLibrary
        PROPERTIES
            INTERPROCEDURAL_OPTIMIZATION ON
            CXX_VISIBILITY_PRESET default
            VISIBILITY_INLINES_HIDDEN ON
            OUTPUT_NAME ${PROJECT_NAME}
            VERSION ${PROJECT_VERSION}
            SOVERSION ${PROJECT_VERSION_MAJOR})

# Let's define where the C++ headers,
# and the static/shared libraries are installed.

INSTALL(
    FILES ${PROJECT_BINARY_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/Version.h
    DESTINATION include/byEAjksCom/Libraries/Template/CPU
    COMPONENT sdk)

INSTALL(
    DIRECTORY ${PROJECT_SOURCE_DIR}/include-api/byEAjksCom/Libraries/Template/CPU/
    DESTINATION include/byEAjksCom/Libraries/Template/CPU
    COMPONENT sdk
    FILES_MATCHING
    PATTERN *.h)

INSTALL(
    TARGETS
        Template-CPUStaticLibrary
        Template-CPUSharedLibrary
    ARCHIVE
        DESTINATION lib/static
        COMPONENT sdk
    LIBRARY
        DESTINATION lib/shared
        COMPONENT runtime
    RUNTIME
        DESTINATION bin
        COMPONENT runtime)

IF(${BUILD_API_DOCUMENTATION})

    IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")

        # Let's generate the API documentation of the library,
        # and define where the generated API documentation is installed.

        FIND_PACKAGE(Doxygen REQUIRED)

        CONFIGURE_FILE(
            ${PROJECT_SOURCE_DIR}/doc/api/Doxyfile.in
            ${PROJECT_BINARY_DIR}/doc/api/Doxyfile
            @ONLY)

        ADD_CUSTOM_COMMAND(
            COMMENT "Creating HTML documentation"
            DEPENDS ${PROJECT_SOURCE_DIR}/doc/api/Doxyfile.in
                    ${Template-CPULibraryHeaders}
                    ${Template-CPULibrarySources}
            OUTPUT  ${PROJECT_BINARY_DIR}/doc/api/html/index.html
            COMMAND ${DOXYGEN_EXECUTABLE} ARGS ${PROJECT_BINARY_DIR}/doc/api/Doxyfile
            WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc/api)

        ADD_CUSTOM_TARGET(
            Template-CPUApiDocumentation ALL
                DEPENDS ${PROJECT_BINARY_DIR}/doc/api/html/index.html
                VERBATIM)

        INSTALL(
            DIRECTORY ${PROJECT_BINARY_DIR}/doc/api/html
            DESTINATION doc/api/byEAjksCom/Libraries/Template/CPU
            COMPONENT sdk)

    ENDIF()

ENDIF()
