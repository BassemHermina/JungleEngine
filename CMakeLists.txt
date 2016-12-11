# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (jungle)

find_package(OpenGL REQUIRED)

# Compile external dependencies
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-1c73e35")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP


if(INCLUDE_DISTRIB)
        add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
        external/AntTweakBar-1.16/include/
        external/glfw-2.7.6/include/
        external/glm-0.9.4.0/
        external/glew-1.9.0/include/
        external/assimp-3.0.1270/include/
        external/bullet-2.81-rev2613/src/
        .
)

set(ALL_LIBS
        ${OPENGL_LIBRARY}
        GLFW_276
        GLEW_190
)

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)




add_executable( main
    main.cpp
    hierarchy/hierarchy.cpp
    hierarchy/hierarchy.hpp
    monobehavior/monobehavior.cpp
    monobehavior/monobehavior.hpp
    transformation/transformation.cpp
    transformation/transformation.hpp
    fileLoaders/shader.cpp
    fileLoaders/shader.hpp
    fileLoaders/texture.cpp
    fileLoaders/texture.hpp
    fileLoaders/objloader.cpp
    fileLoaders/objloader.hpp
    Objects/Suzanne.cpp
    Objects/Suzanne.hpp
    Objects/Shell.cpp
    Objects/Shell.hpp
    includes.hpp
    fileLoaders/controls.cpp
    fileLoaders/controls.hpp
    Objects/plane.cpp
    Objects/plane.hpp
    Shaders.cpp
    Shaders.hpp
    shaderlibrary.cpp
    shaderlibrary.h
    helpers/Shadows.cpp
    helpers/Shadows.hpp
    SkyBoxes/SkyBox.cpp
    SkyBoxes/SkyBox.hpp
    Maze/Maze.cpp
    Maze/Maze.hpp
    Maze/Parts.cpp
    Maze/Parts.hpp
    Objects/Harry_frames.cpp
    Objects/Harry_frames.hpp


)
target_link_libraries(main
        ${ALL_LIBS}
)





SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

add_custom_command(
   TARGET example POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/example${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/example/"
)


elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
