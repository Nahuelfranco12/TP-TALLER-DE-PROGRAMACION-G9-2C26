include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(taller_tests
    tests/position_test.cpp
    tests/inventory_test.cpp
    tests/sector_test.cpp
    tests/animal_test.cpp
)

target_link_libraries(taller_tests
    taller_common
    taller_game
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(taller_tests)
