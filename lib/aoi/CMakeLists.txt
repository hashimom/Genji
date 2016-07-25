ADD_LIBRARY(aoi SHARED   
  aoi.c
  aoidic.c
  aoiconv.c
  aoistr.c
)

INSTALL(TARGETS aoi DESTINATION lib)
INSTALL(FILES ${PROJECT_SOURCE_DIR}/include/aoi.h DESTINATION include)
