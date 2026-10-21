CMAKE_MINIMUM_REQUIRED(VERSION 4.2.0)

project(
    RocketSim
    VERSION 1.0
    LANGUAGES
    CXX C
)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
    quill
    GIT_REPOSITORY https://github.com/odygrd/quill
    GIT_TAG        v13.1.0 
)
FetchContent_MakeAvailable(quill)

add_executable(RocketSim
    main.cpp
    src/app/app.cpp
)
target_include_directories(RocketSim PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(RocketSim PRIVATE quill::quill)
