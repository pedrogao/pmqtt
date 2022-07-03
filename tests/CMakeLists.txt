include_directories(../lib)

file(GLOB TEST_SOURCES "${PROJECT_SOURCE_DIR}/tests/*test.c")

foreach (test_source ${TEST_SOURCES})
    # Create a human readable name.
    get_filename_component(test_filename ${test_source} NAME)
    string(REPLACE ".c" "" bustub_test_name ${test_filename})

    # Add the test target separately and as part of "make check-tests".
    add_executable(${bustub_test_name} EXCLUDE_FROM_ALL ${test_source})
    target_link_libraries(${bustub_test_name} pmqtt_shared)
endforeach(test_source ${test_sourceS})