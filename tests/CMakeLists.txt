add_executable(rfmodel_math_tests
    math/MathUtilitiesTests.cpp
)

target_link_libraries(rfmodel_math_tests PRIVATE rfmodel_math)

add_test(NAME rfmodel_math_tests COMMAND rfmodel_math_tests)
