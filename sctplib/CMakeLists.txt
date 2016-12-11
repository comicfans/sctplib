set(GLIB_LIB C:/win32-libs/glib/lib/glib-2.0.lib)

add_definitions(/DWIN32)
add_definitions(/DMBCS)
add_subdirectory(sctp)

add_subdirectory(programs)

