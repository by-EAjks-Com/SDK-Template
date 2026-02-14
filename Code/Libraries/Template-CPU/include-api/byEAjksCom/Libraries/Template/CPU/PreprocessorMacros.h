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

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
    #define TEMPLATE_CPU_DLL_HIDDEN_HELPER
    #define TEMPLATE_CPU_DLL_EXPORT_HELPER __declspec(dllexport)
    #define TEMPLATE_CPU_DLL_IMPORT_HELPER __declspec(dllimport)
    #define TEMPLATE_CPU_DEPRECATED_HELPER __declspec(deprecated)
#else
    #if __GNUC__ >= 4
        #define TEMPLATE_CPU_DLL_HIDDEN_HELPER __attribute__((visibility ("hidden")))
        #define TEMPLATE_CPU_DLL_EXPORT_HELPER __attribute__((visibility ("default")))
        #define TEMPLATE_CPU_DLL_IMPORT_HELPER __attribute__((visibility ("default")))
        #define TEMPLATE_CPU_DEPRECATED_HELPER __attribute__((deprecated))
    #else
        #define TEMPLATE_CPU_DLL_HIDDEN_HELPER
        #define TEMPLATE_CPU_DLL_EXPORT_HELPER
        #define TEMPLATE_CPU_DLL_IMPORT_HELPER
        #define TEMPLATE_CPU_DEPRECATED_HELPER
    #endif
#endif

#if defined TEMPLATE_CPU_LIBRARY_IS_SHARED
    #if defined COMPILING_TEMPLATE_CPU_LIBRARY
        #define TEMPLATE_CPU_DLL_HIDDEN TEMPLATE_CPU_DLL_HIDDEN_HELPER
        #define TEMPLATE_CPU_DLL_EXPORT TEMPLATE_CPU_DLL_EXPORT_HELPER
        #define TEMPLATE_CPU_DEPRECATED TEMPLATE_CPU_DEPRECATED_HELPER
    #else
        #define TEMPLATE_CPU_DLL_HIDDEN TEMPLATE_CPU_DLL_HIDDEN_HELPER
        #define TEMPLATE_CPU_DLL_EXPORT TEMPLATE_CPU_DLL_IMPORT_HELPER
        #define TEMPLATE_CPU_DEPRECATED TEMPLATE_CPU_DEPRECATED_HELPER
    #endif
#else
    #define TEMPLATE_CPU_DLL_HIDDEN
    #define TEMPLATE_CPU_DLL_EXPORT
    #define TEMPLATE_CPU_DEPRECATED TEMPLATE_CPU_DEPRECATED_HELPER
#endif
