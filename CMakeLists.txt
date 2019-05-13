cmake_minimum_required(VERSION 3.10)

project(demo_procedural)

# CMAKE_PREFIX_PATH must contain the path to the toolkit/cmake subdirectory of
# the Houdini installation. See the "Compiling with CMake" section of the HDK
# documentation for more details, which describes several options for
# specifying this path.
#
list(APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake")

# Locate Houdini's libraries and header files.
# Registers an imported library target named 'Houdini'.
#
find_package(Houdini REQUIRED)

# Make compile_commands.json in the build directory (useful for linter tools)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# This is going to be the name of the compiled file
set(library_name RAY_DemoBox)

add_library(
	${library_name}

	SHARED
		RAY_DemoBox.h
		RAY_DemoBox.C
)

# Link against the Houdini libraries, and add required include directories and compile definitions.
target_link_libraries(${library_name} Houdini)

# Include ${CMAKE_CURRENT_BINARY_DIR} so CMake will see the generated header.
target_include_directories(
	${library_name}

	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
)

# This sets several common target properties, such as the library's output directory.
houdini_configure_target(${library_name})

# This changes the directory so that it installs into
# `~/houdiniX.Y/dso/mantra` instead of the default `~/houdiniX.Y/dso`.
# We need it to be in the "mantra" folder because this is a Mantra plug-in
#
houdini_get_default_install_dir(INSTALLATION_DIRECTORY)
string(APPEND INSTALLATION_DIRECTORY "/dso/mantra")
set(output_dir_properties
    LIBRARY_OUTPUT_DIRECTORY
    LIBRARY_OUTPUT_DIRECTORY_DEBUG
    LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO
    LIBRARY_OUTPUT_DIRECTORY_RELEASE
)
foreach (output_dir_property ${output_dir_properties} )
    set_target_properties( ${library_name}
        PROPERTIES ${output_dir_property} "${INSTALLATION_DIRECTORY}" )
endforeach ()
