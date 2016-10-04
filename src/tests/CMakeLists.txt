include_directories(${FINANCES_SOURCE_DIR}/src/tests)
link_directories(${FINANCES_BINARY_DIR}/src/tests)

add_executable(tests tests.cpp 
              )
#target_link_libraries(cdemo m) #link the math library
