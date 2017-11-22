#Note: I should move these sources into a separate library
#      But i'm too lazy
set(ai_SRC
    "${CMAKE_SOURCE_DIR}/src/fw/process.cpp"
    "${CMAKE_SOURCE_DIR}/src/fw/config.cpp"
    "${CMAKE_SOURCE_DIR}/src/fw/game.cpp"
)
file(GLOB_RECURSE test_SRC "*.cpp")

add_executable(fw_ut ${test_SRC} ${ai_SRC})
target_link_libraries(fw_ut ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_include_directories(fw_ut PUBLIC ${Boost_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/src")
