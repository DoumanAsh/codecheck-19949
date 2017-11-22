file(GLOB main_SRC "*.cpp")
add_executable(ai ${main_SRC})
#target_link_libraries(ai ${Boost_LIBRARIES} ${TEXT_LIB} ${CLIPBOARD_LIB})
#target_include_directories(ai PUBLIC ${LIBS_INCLUDE} ${3PP_INCLUDE})
