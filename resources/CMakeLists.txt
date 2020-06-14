
#add_subdirectory(sample-single-text)


file(GLOB_RECURSE SAMPLEFILES LIST_DIRECTORIES true sample-single-text/*)


file(COPY ${SAMPLEFILES} DESTINATION ${CMAKE_BINARY_DIR}/resources/sample-single-text)

