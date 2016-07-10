cmake_minimum_required(VERSION 2.8)
PROJECT(Genji)

SET(GENJI_DIC_HOME     "${CMAKE_HOME_DIRECTORY}/dic/")
SET(KASUGA_DIC_CSVNAME "${GENJI_DIC_HOME}/kasugadic.csv")
SET(GENJI_DIC_NAME     "${GENJI_DIC_HOME}/genjidic.dat")

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/include/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(lib/fujitsubo)
#ADD_SUBDIRECTORY(lib/murasaki)
ADD_SUBDIRECTORY(lib/aoi)
ADD_SUBDIRECTORY(lib/ux)
ADD_SUBDIRECTORY(src)

