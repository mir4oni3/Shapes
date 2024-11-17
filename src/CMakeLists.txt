include_directories(src/headers)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/../src/impl/*.cpp)

add_library(ShapesLibrary STATIC ${SOURCES})
add_executable(ShapesApp ${CMAKE_CURRENT_SOURCE_DIR}/../main.cpp)
target_link_libraries(ShapesApp ShapesLibrary)

target_include_directories(ShapesLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)
