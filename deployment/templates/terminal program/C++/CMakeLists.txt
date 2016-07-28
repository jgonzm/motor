cmake_minimum_required(VERSION 2.8.9)

project ([value name])

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(PROJECT_VERSION "[value version]")
set(CPACK_PACKAGE_NAME "[value name]")
set(CPACK_PACKAGE_VERSION "[value version]")

# install prefix
set(CMAKE_INSTALL_PREFIX "/usr/local")
set(BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(DATADIR ${CMAKE_INSTALL_PREFIX}/share)
set(SHARE_DIR \"${DATADIR}/[value name]\")

# Definitions
add_definitions(-DSHARE_DIR=${SHARE_DIR})

# CXX FLAGS
set (CMAKE_CXX_FLAGS "-fexceptions -DINT=intptr_t -DUINT=uintptr_t")

# Debug symbols
# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_BUILD_TYPE Release)

include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
  set($ENV{MAKEFLAGS} "-j${N}")
endif()

# make build
add_custom_target(build)

# make dist => generate the tar.gz
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION}")
set(CPACK_SOURCE_IGNORE_FILES
  "/build/;/.git/;~$;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)

add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

set(SOURCE [loop 0;{fsource};1][value fsource.{^loopvalue}] [loopend])
set(HEADERS [loop 0;{fheader};1][value fheader.{^loopvalue}] [loopend])
include_directories([loop 0;{dheader};1][value dheader.{^loopvalue}] [loopend])

foreach( headerfile ${HEADERS} )

    GET_FILENAME_COMPONENT(HEADER ${headerfile} DIRECTORY)
    include_directories(${HEADER})

endforeach( headerfile ${HEADERS} )


# generate executable
add_executable([value name] ${SOURCE} ${HEADERS})
add_dependencies(build [value name])

# link external libraries
target_link_libraries([value name] [value linkeroptions][loop 0;{dlib};1] -L[value dlib.{^loopvalue}][loopend])

# make install => install in /usr/local/bin
install(DIRECTORY deployment/ DESTINATION ${DATADIR}/[value name])
install(TARGETS [value name] DESTINATION bin)
