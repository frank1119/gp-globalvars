cmake_minimum_required(VERSION 3.21)
# Let's choose a name and version for the extension. Change the name to your
# liking. The version should be a string like "1.0".
set(PROJECT_NAME "GlobalVars-Ext") # Change this to your liking
set(CMAKE_CXX_COMPILER_FORCED TRUE)
project(${PROJECT_NAME} VERSION 1.0)


# Import the SDK
include(FetchContent)
FetchContent_Declare(
  gp-sdk
  GIT_REPOSITORY https://github.com/gigperformer/gp-sdk.git
  #GIT_TAG 6c5432518ef42ea0870fb44597e9d1d3780e2f98 # v44
  GIT_TAG origin/beta-sdk-v60
  #SOURCE_DIR C:/Users/fdenb/source/repos/gpextensions/gp-sdk
)
FetchContent_MakeAvailable(gp-sdk)



set(PROCESSOR_ARCHITECTURE=AMD64)

# Define our library including sources, include directories and dependencies
add_library(${PROJECT_NAME} SHARED)
target_sources(
  ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src/LibMain.cpp"
                          "${CMAKE_CURRENT_LIST_DIR}/src/LibMain.h"
                          "${CMAKE_CURRENT_LIST_DIR}/src/GlobalVar.cpp"
                          "${CMAKE_CURRENT_LIST_DIR}/src/GlobalVar.h"
                          "${CMAKE_CURRENT_LIST_DIR}/src/GlobalVarsMap.cpp"
                          "${CMAKE_CURRENT_LIST_DIR}/src/GlobalVarsMap.h"
                        )
target_link_libraries(${PROJECT_NAME} PRIVATE gigperformer::sdk::cpp)
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Language options: this will be a pure C++20 project
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES CXX_STANDARD 20
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS NO
)

# Install the extension on the development machine
install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION "${GIG_PERFORMER_EXTENSIONS_DIRECTORY}"
  RUNTIME DESTINATION "${GIG_PERFORMER_EXTENSIONS_DIRECTORY}")
