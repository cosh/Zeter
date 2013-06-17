INCLUDE_DIRECTORIES(../include/)
INCLUDE_DIRECTORIES(../include/memory)

MACRO(ZETER_TEST name)
        ADD_EXECUTABLE(${name} ${name}.cxx)
        TARGET_LINK_LIBRARIES(${name} ${Boost_LIBRARIES} ZETER)
        ADD_TEST(${name} ${name})
ENDMACRO(ZETER_TEST name)

ZETER_TEST(t_zeter_threadSafeElement)
ZETER_TEST(t_zeter_objectPool)
