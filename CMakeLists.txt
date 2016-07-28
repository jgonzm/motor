cmake_minimum_required(VERSION 2.8.9)

project (motor)

set(CMAKE_VERBOSE_MAKEFILE OFF)

set(PROJECT_VERSION "0.1")
set(CPACK_PACKAGE_NAME "motor")
set(CPACK_PACKAGE_VERSION "0.1")

# install prefix
set(CMAKE_INSTALL_PREFIX "/usr/local")
set(BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(DATADIR ${CMAKE_INSTALL_PREFIX}/share)
set(SHARE_DIR \"${DATADIR}/motor\")

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

set(SOURCE kksystr/src/kkfsys.cc kksystr/src/kkiproc.cc parser/src/parlist.c parser/src/strfn.c parser/src/llist.c parser/src/parser_cgi.c parser/src/parser.c kkconsui/src/abstractui.cc kkconsui/src/fileselector.cc kkconsui/src/textbrowser.cc kkconsui/src/textwindow.cc kkconsui/src/texteditor.cc kkconsui/src/screenarea.cc kkconsui/src/horizontalbar.cc kkconsui/src/treeview.cc kkconsui/src/dialogbox.cc kkconsui/src/conscommon.cc kkconsui/src/textinputline.cc kkconsui/src/cmenus.cc kkconsui/src/linkedlist.cc kkstrtext/kkstrtext.cc src/ui/motorui.cc src/ui/ncurses/uigrepper.cc src/ui/ncurses/uiconfiguration.cc src/ui/ncurses/uiregexper.cc src/ui/ncurses/uiwatcher.cc src/ui/ncurses/uieditor.cc src/ui/ncurses/uivcs.cc src/ui/ncurses/uitagbrowser.cc src/ui/ncurses/ncursesui.cc src/vcs/motorvcs.cc src/project/projectdesk.cc src/project/projectpaths.cc src/project/motorproject.cc src/project/projectfiles.cc src/project/projectdebug.cc src/project/projecttake.cc src/project/projectname.cc src/project/projecttempl.cc src/project/motorfolder.cc src/project/motorfile.cc src/project/motordist.cc src/project/sourcetemplate.cc src/executor/motorexecutor.cc src/executor/parserule.cc src/main.cc src/configuration/motorconfiguration.cc src/configuration/extkey.cc src/debugger/watch.cc src/debugger/motordebugger.cc src/debugger/stackitem.cc src/debugger/breakpoint.cc src/debugger/debuggercommand.cc src/debugger/debuggermessage.cc src/manager/motormanager.cc src/tagbrowser/motortagbrowser.cc src/motormisc.cc src/grepper/motorgrepper.cc )
set(HEADERS kksystr/include/conf.h kksystr/include/kkfsys.h kksystr/include/kkiproc.h parser/include/strfn.h parser/include/llist.h parser/include/parser.h parser/include/parlist.h parser/include/parser_cgi.h kkconsui/include/screenarea.h kkconsui/include/abstractui.h kkconsui/include/dialogbox.h kkconsui/include/treeview.h kkconsui/include/texteditor.h kkconsui/include/horizontalbar.h kkconsui/include/conscommon.h kkconsui/include/conf.h kkconsui/include/linkedlist.h kkconsui/include/textbrowser.h kkconsui/include/textwindow.h kkconsui/include/cmenus.h kkconsui/include/fileselector.h kkconsui/include/textinputline.h kkstrtext/kkstrtext.h kkstrtext/conf.h src/ui/ncurses/ncursesui.h src/ui/ncurses/uiregexper.h src/ui/ncurses/uieditor.h src/ui/ncurses/uiwatcher.h src/ui/ncurses/uidefs.h src/ui/ncurses/uivcs.h src/ui/ncurses/uiconfiguration.h src/ui/ncurses/uitagbrowser.h src/ui/ncurses/uigrepper.h src/ui/motorui.h src/vcs/motorvcs.h src/project/motorfile.h src/project/motorproject.h src/project/projecttake.h src/project/sourcetemplate.h src/project/projectpaths.h src/project/projecttempl.h src/project/projectname.h src/project/motorfolder.h src/project/projectdebug.h src/project/motordist.h src/project/projectfiles.h src/project/projectdesk.h src/executor/motorexecutor.h src/executor/parserule.h src/configuration/motorconfiguration.h src/debugger/breakpoint.h src/debugger/debuggercommand.h src/debugger/stackitem.h src/debugger/debuggermessage.h src/debugger/motordebugger.h src/debugger/watch.h src/motorcommon.h src/manager/motormanager.h src/motormisc.h src/tagbrowser/motortagbrowser.h src/grepper/motorgrepper.h )
include_directories()

foreach( headerfile ${HEADERS} )

    GET_FILENAME_COMPONENT(HEADER ${headerfile} DIRECTORY)
    include_directories(${HEADER})

endforeach( headerfile ${HEADERS} )


# generate executable
add_executable(motor ${SOURCE} ${HEADERS})
add_dependencies(build motor)

# link external libraries
target_link_libraries(motor -lintl -lncursesw)

# make install => install in /usr/local/bin
install(DIRECTORY deployment/ DESTINATION ${DATADIR}/motor)
install(TARGETS motor DESTINATION bin)
