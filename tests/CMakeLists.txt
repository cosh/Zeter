INCLUDE_DIRECTORIES(../include/)
INCLUDE_DIRECTORIES(../include/memory)
INCLUDE_DIRECTORIES(../include/synchronization)
INCLUDE_DIRECTORIES(../include/collections)

MACRO(ZETER_TEST name)
        ADD_EXECUTABLE(${name} ${name}.cxx)
        TARGET_LINK_LIBRARIES(${name} ${Boost_LIBRARIES} ZETER)
        ADD_TEST(${name} ${name})
ENDMACRO(ZETER_TEST name)

ZETER_TEST(t_zeter_lockableElement)
ZETER_TEST(t_zeter_objectPool)