MACRO(ZETER_TEST name)
        ADD_EXECUTABLE(${name} ${name}.cxx)
        TARGET_LINK_LIBRARIES(${name}  ZETER)
        ADD_TEST(${name} ${name})
ENDMACRO(ZETER_TEST name)

INCLUDE_DIRECTORIES(../include/)

ZETER_TEST(t_zeter_threadSafeElement)
