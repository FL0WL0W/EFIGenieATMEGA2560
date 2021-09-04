cmake_minimum_required ( VERSION 3.9 )
project ( EFIGenie C CXX ASM )

set(LIBRARIES	libs)

include_directories(include)
include_directories(libs/avr-libstdcpp/include)

file(GLOB_RECURSE LIBSTDCPP_CXXSOURCES libs/avr-libstdcpp/src/*.cc)
#this file doesn't compile for some reason so just remove it
file(GLOB_RECURSE LIBSTDCPP_CXXSOURCES_REMOVE libs/avr-libstdcpp/src/hash_bytes.cc)
list(REMOVE_ITEM LIBSTDCPP_CXXSOURCES ${LIBSTDCPP_CXXSOURCES_REMOVE})

file(GLOB_RECURSE USER_CSOURCES src/*.c)
file(GLOB_RECURSE USER_CXXSOURCES src/*.cpp)

set(SOURCE_FILES ${LIBSTDCPP_CXXSOURCES} ${USER_CSOURCES} ${USER_CXXSOURCES})
add_executable(firmware.elf ${SOURCE_FILES})

add_subdirectory (${LIBRARIES}/OperationArchitecture)
add_subdirectory (${LIBRARIES}/EmbeddedIOServices)
add_subdirectory (${LIBRARIES}/EmbeddedIOOperations)
add_subdirectory (${LIBRARIES}/ReluctorOperations)
add_subdirectory (${LIBRARIES}/EFIGenie)
target_link_libraries(firmware.elf OperationArchitecture)
target_link_libraries(firmware.elf EmbeddedIOServices)
target_link_libraries(firmware.elf EmbeddedIOOperations)
target_link_libraries(firmware.elf ReluctorOperations)
target_link_libraries(firmware.elf EFIGenie)

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/firmware.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/firmware.bin)
add_custom_command(TARGET firmware.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex $<TARGET_FILE:firmware.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} ARGS -O binary $<TARGET_FILE:firmware.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")
