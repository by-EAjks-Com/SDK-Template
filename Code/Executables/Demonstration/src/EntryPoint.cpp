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

// First-Party Headers
#include "PrecompiledHeaders.h"
#include "Version.h"
#include "byEAjksCom/Libraries/Template/CPU/ObjectFactory.h"
#include "byEAjksCom/Libraries/Template/CPU/ObjectFactoryIF.h"
#include "byEAjksCom/Libraries/Template/CPU/ObjectIF.h"
#include "byEAjksCom/Libraries/Template/GPU/ObjectFactory.h"
#include "byEAjksCom/Libraries/Template/GPU/ObjectFactoryIF.h"
#include "byEAjksCom/Libraries/Template/GPU/ObjectIF.h"

// Third-Party Headers
#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Standard C++/STL Headers
#include <memory>
#include <string>

// Standard C-->C++ Headers
#include <cmath>
#include <cstdint>

namespace CPU = ::byEAjksCom::Libraries::Template::CPU;
namespace GPU = ::byEAjksCom::Libraries::Template::GPU;

/// @brief Is the entry-point of the executable.
/// @param[in] argc The number of command-line arguments.
/// @param[in] argv The command-line arguments.
int
main(
    int argc,
    char ** argv)
{
    ::std::shared_ptr<::spdlog::logger>
    logger { ::std::make_shared<::spdlog::logger>(EXECUTABLE_NAME) };
    logger->flush_on(::spdlog::level::err);
    logger->set_level(::spdlog::level::trace);
    ::spdlog::register_logger(logger);

    ::spdlog::sink_ptr
    sink { ::std::make_shared<::spdlog::sinks::stdout_color_sink_mt>() };
    sink->set_pattern("%^[%L] %v%$");
    sink->set_level(::spdlog::level::info);
    logger->sinks().push_back(sink);

    try
    {
        ::CLI::App
        cliParser { EXECUTABLE_NAME + ", v" + EXECUTABLE_VERSION };

        cliParser.add_flag_function(
            "-v,--verbose",
            [logger](
                int32_t verbosityLevel)
            {
                switch (verbosityLevel)
                {
                    case  0: logger->set_level(::spdlog::level::info);  break;
                    case  1: logger->set_level(::spdlog::level::debug); break;
                    default: logger->set_level(::spdlog::level::trace); break;
                }
            },
            "Sets the verbosity level");

        cliParser.add_option_function<::std::string>(
            "--log-to",
            [logger](
                ::std::string logFileName)
            {
                ::spdlog::sink_ptr
                sink { ::std::make_shared<::spdlog::sinks::basic_file_sink_mt>(logFileName) };
                sink->set_pattern("[%T.%F] %l: %v (%n)");
                sink->set_level(::spdlog::level::trace);
                logger->sinks().push_back(sink);
            },
            "Saves the logs into a file.");

        try
        {
            cliParser.parse(argc, argv);
        }
        catch (const ::CLI::ParseError & exception)
        {
            return cliParser.exit(exception);
        }

        logger->info("starting {}, v{}", EXECUTABLE_NAME, EXECUTABLE_VERSION);

        ::std::unique_ptr<CPU::ObjectFactoryIF>
        cpuObjectFactory { ::std::make_unique<CPU::ObjectFactory>(logger) };

        ::std::unique_ptr<CPU::ObjectIF>
        cpuObject { cpuObjectFactory->CreateInstance() };

        cpuObject->Run();

        ::std::unique_ptr<GPU::ObjectFactoryIF>
        gpuObjectFactory { ::std::make_unique<GPU::ObjectFactory>(logger) };

        ::std::unique_ptr<GPU::ObjectIF>
        gpuObject { gpuObjectFactory->CreateInstance() };

        gpuObject->Run();

        logger->info("finished successfully");
        logger->flush();

        return (0);
    }
    catch (const ::std::exception & exception)
    {
        logger->error(exception.what());
        logger->info("finished prematurely with error(s)");
        logger->flush();

        return (1);
    }
}
