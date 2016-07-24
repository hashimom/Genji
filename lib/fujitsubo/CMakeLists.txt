ADD_LIBRARY(fujitsubo SHARED   
  fujitsubo.cc
)

TARGET_LINK_LIBRARIES(fujitsubo ux)

INSTALL(TARGETS fujitsubo DESTINATION lib)
