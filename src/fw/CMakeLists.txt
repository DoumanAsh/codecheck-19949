file(GLOB main_SRC "*.cpp")
add_executable(fw ${main_SRC})
target_link_libraries(fw ${Boost_LIBRARIES})
