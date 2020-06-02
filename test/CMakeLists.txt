set(BINARY ${CMAKE_PROJECT_NAME}_test)

set(TEST_SOURCES
  dummy_tests.cpp
  game_tests.cpp
)

add_executable(${BINARY} ${TEST_SOURCES} main.cpp)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME} gtest)