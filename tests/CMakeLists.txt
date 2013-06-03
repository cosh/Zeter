INCLUDE_DIRECTORIES(../include/)
INCLUDE_DIRECTORIES(../include/memory)

MACRO(ZETER_TEST name)
        ADD_EXECUTABLE(${name} ${name}.cxx)
        TARGET_LINK_LIBRARIES(${name} ZETER ${Boost_SYSTEM_LIBRARY} )
        ADD_TEST(${name} ${name})
ENDMACRO(ZETER_TEST name)

ZETER_TEST(t_zeter_threadSafeElement)
ZETER_TEST(t_zeter_objectPool)
