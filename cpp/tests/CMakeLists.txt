cmake_minimum_required(VERSION 3.30)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_EXES
    test_person
    test_book
)

foreach(EXE IN LISTS TEST_EXES)
    add_executable(${EXE} ${EXE}.cpp)

    target_link_libraries(${EXE} GTest::gtest_main ${LIB})

    target_include_directories(${EXE} PUBLIC
    	"${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/cpp/include"
    )
endforeach()

include(GoogleTest)
gtest_discover_tests(test_person)
gtest_discover_tests(test_book)
