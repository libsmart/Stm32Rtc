cmake_minimum_required(VERSION 3.27)

project(Stm32Rtc)

file(GLOB_RECURSE SOURCES ${sources}
        "src/*.*"
)
add_library(Stm32Rtc STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
        src
)
