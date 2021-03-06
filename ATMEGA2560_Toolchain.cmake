set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(MCU atmega2560)
add_definitions ( -DF_CPU=16000000UL)
set ( CMAKE_C_FLAGS "-mmcu=${MCU} -Wall -O3" )
set ( CMAKE_CXX_FLAGS "-mmcu=${MCU} -std=c++17 -O2 -Wall -Wextra -pedantic -fno-exceptions -fno-rtti -fno-unwind-tables -fno-threadsafe-statics -Wshadow -Wcast-qual -Wpointer-arith -Wundef" )
set ( CMAKE_ASM_FLAGS "-mmcu=${MCU} -Wall -O3" )
set ( CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU} -Wall -O3" )
