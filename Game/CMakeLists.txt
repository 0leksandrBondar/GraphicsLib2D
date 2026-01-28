cmake_minimum_required(VERSION 3.30..)

add_executable(${PROJECT_NAME} Main.cpp Game.cpp Game.h Player.h Player.cpp)

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
