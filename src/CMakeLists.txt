set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
  computer.cpp
  game.cpp
  human.cpp
  logger.cpp
  player.cpp
  utils.cpp
)

add_executable(${BINARY}_run ${SOURCES} main.cpp)

add_library(${BINARY} STATIC ${SOURCES})