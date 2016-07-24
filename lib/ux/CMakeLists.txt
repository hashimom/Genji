INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/ux)

ADD_LIBRARY(ux SHARED   
  uxTrie.cpp
  bitVec.cpp
  rsDic.cpp
  uxUtil.cpp
  uxMap.cpp 
)

INSTALL(TARGETS ux DESTINATION lib)
