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

CMAKE_MINIMUM_REQUIRED(VERSION 3.30.2)

SET(TEMPLATE_SDK_VERSION "0.0.0.0" CACHE STRING "Template-SDK Version")
SET(USE_PRECOMPILED_HEADERS ON  CACHE BOOL "Use the precompiled headers")
SET(BUILD_API_DOCUMENTATION OFF CACHE BOOL "Build the API documentation")

PROJECT(Template-SDK VERSION ${TEMPLATE_SDK_VERSION} LANGUAGES NONE)

IF(NOT DEFINED CMAKE_CXX_STANDARD)
    SET(CMAKE_CXX_STANDARD 23)
    SET(CMAKE_CXX_STANDARD_REQUIRED ON)
    SET(CMAKE_CXX_EXTENSIONS ON)
ENDIF()

IF(NOT DEFINED CMAKE_CUDA_STANDARD)
    SET(CMAKE_CUDA_STANDARD 20)
    SET(CMAKE_CUDA_STANDARD_REQUIRED ON)
    SET(CMAKE_CUDA_EXTENSIONS ON)
    SET(CMAKE_CUDA_ARCHITECTURES 90)
ENDIF()

SET(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)

FIND_PROGRAM(CCACHE_PROGRAM ccache)
IF (CCACHE_PROGRAM)
    SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
ENDIF()

INSTALL(
    FILES
        ${PROJECT_SOURCE_DIR}/AUTHORS.md
        ${PROJECT_SOURCE_DIR}/CHANGELOG.md
        ${PROJECT_SOURCE_DIR}/LICENSE
        ${PROJECT_SOURCE_DIR}/README.md
    DESTINATION .
    COMPONENT runtime)

ADD_SUBDIRECTORY(Dependencies)
ADD_SUBDIRECTORY(Libraries)
#DD_SUBDIRECTORY(Executables)
ADD_SUBDIRECTORY(Bindings)

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")

    SET(CMAKE_INSTALL_PREFIX /opt/by-EAjks.Com/${PROJECT_NAME})

    CONFIGURE_FILE(
        ${PROJECT_SOURCE_DIR}/Miscellaneous/Linux/DEBIAN/conffiles.in
        ${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/conffiles
        @ONLY)

    CONFIGURE_FILE(
        ${PROJECT_SOURCE_DIR}/Miscellaneous/Linux/DEBIAN/preinst.in
        ${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/preinst
        @ONLY)

    CONFIGURE_FILE(
        ${PROJECT_SOURCE_DIR}/Miscellaneous/Linux/DEBIAN/postinst.in
        ${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/postinst
        @ONLY)

    CONFIGURE_FILE(
        ${PROJECT_SOURCE_DIR}/Miscellaneous/Linux/DEBIAN/prerm.in
        ${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/prerm
        @ONLY)

    CONFIGURE_FILE(
        ${PROJECT_SOURCE_DIR}/Miscellaneous/Linux/DEBIAN/postrm.in
        ${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/postrm
        @ONLY)

    CONFIGURE_FILE(
        ${PROJECT_SOURCE_DIR}/Miscellaneous/Linux/etc/ld.so.conf.d/${PROJECT_NAME}.conf.in
        ${PROJECT_BINARY_DIR}/Miscellaneous/Linux/etc/ld.so.conf.d/${PROJECT_NAME}.conf
        @ONLY)

    INSTALL(
        FILES ${PROJECT_BINARY_DIR}/Miscellaneous/Linux/etc/ld.so.conf.d/${PROJECT_NAME}.conf
        DESTINATION /etc/ld.so.conf.d
        COMPONENT runtime)

    CONFIGURE_FILE(
        ${PROJECT_SOURCE_DIR}/Miscellaneous/Linux/usr/local/lib/python3.12/dist-packages/${PROJECT_NAME}.pth.in
        ${PROJECT_BINARY_DIR}/Miscellaneous/Linux/usr/local/lib/python3.12/dist-packages/${PROJECT_NAME}.pth
        @ONLY)

    INSTALL(
        FILES ${PROJECT_BINARY_DIR}/Miscellaneous/Linux/usr/local/lib/python3.12/dist-packages/${PROJECT_NAME}.pth
        DESTINATION /usr/local/lib/python3.12/dist-packages
        COMPONENT runtime)

ENDIF()

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_NAME ${PROJECT_NAME})
SET(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SDK Template by EAjks")
SET(CPACK_PACKAGE_VENDOR "by-EAjks.Com")
SET(CPACK_PACKAGE_CONTACT "Andrea and Eric DELAGE <Contact@by-EAjks.Com>")
SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}")

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")

    SET(CPACK_SET_DESTDIR ON)

    SET(LINUX_DISTRIBUTION_ID "unknown")

    IF(EXISTS "/etc/os-release")
        FILE(STRINGS "/etc/os-release" LINUX_DISTRIBUTION_ID REGEX "^ID=")
        IF(NOT LINUX_DISTRIBUTION_ID STREQUAL "")
            STRING(REPLACE "ID=" "" LINUX_DISTRIBUTION_ID "${LINUX_DISTRIBUTION_ID}")
            STRING(REPLACE "\""  "" LINUX_DISTRIBUTION_ID "${LINUX_DISTRIBUTION_ID}")
        ENDIF()
    ENDIF()

    MESSAGE("-- The Linux distribution identification is '${LINUX_DISTRIBUTION_ID}'.")

    IF(${LINUX_DISTRIBUTION_ID} MATCHES "debian|ubuntu")
        SET(CPACK_GENERATOR "DEB")
        SET(CPACK_DEB_PACKAGE_ARCHITECTURE "amd64")
        SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/conffiles;${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/preinst;${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/postinst;${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/prerm;${PROJECT_BINARY_DIR}/Miscellaneous/Linux/DEBIAN/postrm")
        SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libpython3.12")
    ENDIF()

    IF(${LINUX_DISTRIBUTION_ID} MATCHES "centos|redhat")
        SET(CPACK_GENERATOR "RPM")
        SET(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
    ENDIF()

    SET(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)

ENDIF()

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")

    SET(CPACK_GENERATOR "ZIP")

ENDIF()

INCLUDE(CPack)
