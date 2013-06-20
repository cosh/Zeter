INCLUDE_DIRECTORIES(../include/)

SET(ZETER_SRC ${ZETER_SRC}
  synchronization/threadSafeElement.cpp
  memory/arrayAllocator.cpp
  memory/growthByNextPowerOfTwo.cpp
)

ADD_LIBRARY(ZETER ${ZETER_SRC})

TARGET_LINK_LIBRARIES(ZETER ${Boost_LIBRARIES} )

INSTALL(TARGETS ZETER
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )

