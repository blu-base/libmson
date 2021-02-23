set ( CMAKE_EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )

macro( add_multiple_tests )
  foreach( test ${ARGN} )
    add_executable( test_${test} ${test}.cpp )
    add_test( isf-${test} test_${test} )
    target_link_libraries( test_${test} PUBLIC Qt5::Test Qt5::Core isf )
    set_property(TARGET test_${test} PROPERTY AUTOMOC ON)
  endforeach( test )
endmacro()

ADD_MULTIPLE_TESTS(
MultiByteEncoding
)

