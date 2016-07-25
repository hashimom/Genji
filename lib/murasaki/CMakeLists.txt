ADD_LIBRARY(murasaki SHARED   
  murasaki.cc
  graph.cc
)

TARGET_LINK_LIBRARIES(murasaki ux)

INSTALL(TARGETS murasaki DESTINATION lib)
INSTALL(FILES ${PROJECT_SOURCE_DIR}/include/murasaki.hh DESTINATION include)
