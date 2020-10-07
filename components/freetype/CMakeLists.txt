idf_component_register(SRCS .
        INCLUDE_DIRS . lib/freetype/include)

set(CMAKE_DISABLE_FIND_PACKAGE_ZLIB TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_BZip2 TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_PNG TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_BrotliDec TRUE)
configure_file(lib/freetype/README ${BUILD_DIR}/README COPYONLY)
configure_file(lib/freetype/docs/LICENSE.TXT ${BUILD_DIR}/docs/LICENSE.TXT COPYONLY)

function(install)
endfunction()

function(export)
endfunction()

add_subdirectory(lib/freetype)

target_link_libraries(${COMPONENT_LIB} PUBLIC freetype)
