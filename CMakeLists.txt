cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O0 -ggdb ")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -Wno-return-stack-address")
set(CMAKE_CXX_FLAGS  "-Wno-return-stack-address")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb")
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/Debug)

if (APPLE)
    set(PLIB ${PROJECT_SOURCE_DIR}/lib/macosx)
    include_directories(/usr/local/opt/llvm/include)
    link_directories(/usr/local/opt/llvm/lib)
elseif(UNIX)
    set(PLIB ${PROJECT_SOURCE_DIR}/lib/linux)
else()
    message(FATAL_ERROR "unsupport OS now")
endif(APPLE)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/llvm_lab)

#link_directories(${PLIB})
link_directories(/usr/lib)

set(EXPREFIX ${CMAKE_CURRENT_SOURCE_DIR}/examples)

add_executable(llvm_test ${EXPREFIX}/llvm_main.cpp)
target_link_libraries(llvm_test LLVM)

add_executable(llvm_ifelse ${EXPREFIX}/ifelse.cpp)
target_link_libraries(llvm_ifelse LLVM)

add_executable(llvm_func ${EXPREFIX}/func.cpp)
target_link_libraries(llvm_func LLVM)

add_executable(llvm_var ${EXPREFIX}/var.cpp)
target_link_libraries(llvm_var LLVM)

add_executable(llvm_varargs ${EXPREFIX}/varargs.cpp)
target_link_libraries(llvm_varargs LLVM)

add_executable(builder ${EXPREFIX}/builder.cpp)
target_link_libraries(builder LLVM)

#### Loops to build test targets
#file(GLOB LABSOURCES ${EXPREFIX}/*.cpp)
#foreach(test ${LABSOURCES})
#    string(REGEX REPLACE ".*/([a-zA-Z_0-9]+)\\.cpp" "llvm_\\1.exe" itarget "${test}")
#    message(STATUS "file ${test} ${itarget}")
#    add_executable(${itarget} ${test})
#    target_link_libraries(${itarget} LLVM)
#endforeach(test)

install(TARGETS builder llvm_var
    RUNTIME DESTINATION bin
)
