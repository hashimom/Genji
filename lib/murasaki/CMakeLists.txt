ADD_LIBRARY(murasaki SHARED   
  murasaki.cc
  graph.cc
)

TARGET_LINK_LIBRARIES(murasaki ux)

INSTALL(TARGETS murasaki DESTINATION lib)
