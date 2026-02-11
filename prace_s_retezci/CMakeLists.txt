PROJECT(retezce)

ADD_EXECUTABLE(retezce src/main.c)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set_property(TARGET retezce PROPERTY C_STANDARD 23)
