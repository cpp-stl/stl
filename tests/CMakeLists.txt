set(TEST_FILES test_vector.cpp)

add_executable(tests ${TEST_FILES})

target_include_directories(tests PUBLIC
    ${INCLUDE_DIR}
)