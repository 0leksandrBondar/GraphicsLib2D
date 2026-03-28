cmake_minimum_required(VERSION 3.30..)

set(Source Main.cpp
        Game.h
        Game.cpp
        Player/Player.h
        Player/Player.cpp
        Levels/Level.h
        Levels/Level.cpp
        Levels/LevelController.h
        Levels/LevelController.cpp
        Levels/Overworld/Overworld.h
        Levels/Overworld/Overworld.cpp
        Core/Scene.h
        Core/Scene.cpp
        Core/BaseGameObject.h
        Core/BaseGameObject.cpp
        ResourceManager/ResourceManager.h
        ResourceManager/ResourceManager.cpp
)


add_executable(${PROJECT_NAME} ${Source})

target_link_libraries(${PROJECT_NAME} PRIVATE GraphicsLib)

# ----- copy assets to bin directory --

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin/Assets"
        COMMENT "Creating assets directory"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Assets"
        "${CMAKE_BINARY_DIR}/bin/Assets"
        COMMENT "Copying assets"
)

# -------------------------------------
