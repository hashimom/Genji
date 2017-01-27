cmake_minimum_required(VERSION 2.8)
PROJECT(Genji)

SET(GENJI_DIC_HOME     "${CMAKE_HOME_DIRECTORY}/dic/")
SET(KASUGA_DBNAME      "${GENJI_DIC_HOME}/kasuga.db")
SET(KASUGA_CPS_CSVNAME "${GENJI_DIC_HOME}/kasugacps.csv")
SET(KASUGA_DIC_CSVNAME "${GENJI_DIC_HOME}/kasugadic.csv")
SET(GENJI_BASICWORDS   "${CMAKE_SOURCE_DIR}/lib/fujitsubo/basic_words.txt")
SET(GENJI_BASICNAIST   "${CMAKE_SOURCE_DIR}/lib/fujitsubo/basic_naist-jdic.csv")
SET(GENJI_YOMIDIC_NAME "${GENJI_DIC_HOME}/genji_yomidic.dat")
SET(GENJI_WORDDIC_NAME "${GENJI_DIC_HOME}/genji_worddic.dat")

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

CONFIGURE_FILE(${PROJECT_SOURCE_DIR}/include/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(lib/fujitsubo)
ADD_SUBDIRECTORY(lib/murasaki)
ADD_SUBDIRECTORY(lib/aoi)
ADD_SUBDIRECTORY(lib/ux)
ADD_SUBDIRECTORY(src)

