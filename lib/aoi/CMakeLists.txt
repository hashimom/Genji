ADD_LIBRARY(aoi SHARED   
  aoi.c
  aoidic.c
  aoiconv.c
  aoistr.c
)

INSTALL(TARGETS aoi DESTINATION lib)
