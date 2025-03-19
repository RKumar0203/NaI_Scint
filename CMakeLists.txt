cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(simulation)

# Find the Geant4 package
find_package(Geant4 REQUIRED ui_all vis_all)

# Include Geant4 headers and libraries
include_directories(${Geant4_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)


# Gather source files from the 'src' directory
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)

# Gather header files from the 'include' directory
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

# Copying the macro files
file(GLOB MACRO_FILES "${PROJECT_SOURCE_DIR}/macros/*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# Create the executable target
add_executable(NaI sim.cc ${sources} ${headers})

# Link the Geant4 libraries to the executable
target_link_libraries(NaI ${Geant4_LIBRARIES})

# Optionally, if you want to specify the custom target `simulation` to depend on `NaI`, this line makes sense
add_custom_target(simulation DEPENDS NaI)
