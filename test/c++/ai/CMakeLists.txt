set(ai_SRC "${CMAKE_SOURCE_DIR}/src/ai/word.cpp")
file(GLOB_RECURSE test_SRC "*.cpp")

add_executable(ai_ut ${test_SRC} ${ai_SRC})
target_link_libraries(ai_ut ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_include_directories(ai_ut PUBLIC ${Boost_INCLUDE_DIRS} "${CMAKE_SOURCE_DIR}/src")
