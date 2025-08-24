cmake_minimum_required(VERSION 3.22)
project(pyraylib)
include(FetchContent)


# this is only relevant if we are building box2d
# (ie if FETCH_PRAYLIB is ON)
OPTION(BUILD_EXTENSION "Build the extension" ON)
OPTION(BUILD_WASM_HOST "Build the WASM host (when on emscripten)" ON)

OPTION(FETCH_RAYLIB          "Download/Fetch Raylib" OFF)
option(BUILD_SHARED_LIBS     "Build using shared libraries" OFF)


if(EMSCRIPTEN)
    set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
    # set the global definition PLATFORM_WEB
    add_compile_definitions(PLATFORM_WEB)
endif()





if(DEFINED SKBUILD)
    SET(CMAKE_INSTALL_LIBDIR ${SKBUILD_PROJECT_NAME}/lib)
else()
    SET(INSTALL_DIR  ${CMAKE_INSTALL_PREFIX})
    SET(CMAKE_INSTALL_LIBDIR lib)
endif()



if(BUILD_EXTENSION)

    if(EMSCRIPTEN)
        find_package(Python COMPONENTS Interpreter Development REQUIRED)
    else()
        find_package(Python 3.9
            REQUIRED COMPONENTS Interpreter Development.Module
            OPTIONAL_COMPONENTS Development.SABIModule)
    endif()


    if(FETCH_RAYLIB)
        set(CMAKE_POSITION_INDEPENDENT_CODE ON)
        FetchContent_Declare(
            raylib
            GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
            GIT_TAG "5.5"
            GIT_PROGRESS TRUE
        )
        FetchContent_MakeAvailable(raylib)
    else()
        if(NOT EMSCRIPTEN)
            find_package(raylib REQUIRED)
        endif()
    endif()

    find_package(nanobind CONFIG REQUIRED)


    SET(PY_SOURCES
        src/main.cpp
        # raylib itself
        src/raylib/export_raylib.cpp
        src/raylib/export_rcore.cpp
        src/raylib/export_rshapes.cpp
        src/raylib/export_rtext.cpp
        src/raylib/export_structs.cpp
        # raylib-extensions
        src/raylib_extensions/export_raylib_extensions.cpp
        src/raylib_extensions/export_flipped_camera_2d.cpp
    )


    if(NOT EMSCRIPTEN)
        nanobind_add_module(_praylib STABLE_ABI ${PY_SOURCES})
    else()
        nanobind_add_module(_praylib ${PY_SOURCES})
    endif()


    if(EMSCRIPTEN)
        target_link_options(_praylib
            PUBLIC "SHELL: -s SIDE_MODULE=1"
        )

        target_compile_options(_praylib
            PUBLIC "SHELL: -s SIDE_MODULE=1"
        )
    endif()


    # include directories
    target_include_directories(_praylib
        PRIVATE ${CMAKE_SOURCE_DIR}/src/
    )

    if(EMSCRIPTEN)
        # link raylib and hard code the path to the env variable $PREFIX/lib/libraylib.a
        target_link_libraries(_praylib PRIVATE $ENV{PREFIX}/lib/libraylib.a)
        target_include_directories(_praylib PRIVATE $ENV{PREFIX}/include)
    else()
        # link raylib
        target_link_libraries(_praylib PRIVATE  raylib)
    endif()    

    # after each build, copy the extension to the python package directory
    add_custom_command(TARGET _praylib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:_praylib> ${CMAKE_SOURCE_DIR}/src/module/praylib
        COMMENT "Copying _praylib to python package directory"
    )

    if(NOT DEFINED SKBUILD)
        # on mac or linux, set the shared library suffix to .so
        if(APPLE OR UNIX)
            set_target_properties(_praylib PROPERTIES SUFFIX ".so")
        endif()
    else()
        message(STATUS "using SKBUILD" ${SKBUILD})
    endif()


    if(DEFINED SKBUILD)
        message(STATUS "using SKBUILD" ${SKBUILD})
        install(TARGETS _praylib LIBRARY DESTINATION ${SKBUILD_PROJECT_NAME})
        install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/module/praylib/ DESTINATION ${SKBUILD_PROJECT_NAME})
    else()
        message(STATUS "not using SKBUILD")
    endif()

endif()


function(cat IN_FILE OUT_FILE)
  file(READ ${IN_FILE} CONTENTS)
  file(APPEND ${OUT_FILE} "\n${CONTENTS}")
endfunction()

if(EMSCRIPTEN)
if(BUILD_WASM_HOST)
    # include(CMakePackageConfigHelpers)
    include(GNUInstallDirs)

    find_package(pybind11 REQUIRED)
    find_package(pyjs REQUIRED)

    SET(PYTHON_UTIL_LIBS
        ${CMAKE_INSTALL_PREFIX}/lib/libbz2.a
        ${CMAKE_INSTALL_PREFIX}/lib/libz.a
        ${CMAKE_INSTALL_PREFIX}/lib/libsqlite3.a
        ${CMAKE_INSTALL_PREFIX}/lib/libffi.a
        ${CMAKE_INSTALL_PREFIX}/lib/libzstd.a
        ${CMAKE_INSTALL_PREFIX}/lib/libssl.a
        ${CMAKE_INSTALL_PREFIX}/lib/libcrypto.a
        ${CMAKE_INSTALL_PREFIX}/lib/liblzma.a
    )

    add_executable(praylib_host src/praylib_wasm_host.cpp)
    target_link_libraries(praylib_host PRIVATE ${PYTHON_UTIL_LIBS} pybind11::embed  pyjs)

    # fpic
    target_compile_options(praylib_host PRIVATE -fPIC)

    # link with bind 
    file(WRITE post.js.in "")
    cat(src/post.js  post.js.in)
    cat(${pyjs_POST_JS_PATH}  post.js.in)
    configure_file( post.js.in  ${CMAKE_CURRENT_BINARY_DIR}/post.js COPYONLY)

    # add shell file flag to the linker
    # target_link_options(praylib_host PUBLIC --shell-file ${CMAKE_SOURCE_DIR}/src/minshell.html)
    target_link_options(praylib_host PUBLIC -sMINIFY_HTML=0)
    target_link_options(praylib_host PUBLIC -sALLOW_MEMORY_GROWTH=1)
    target_link_options(praylib_host PUBLIC -sMAIN_MODULE=1)
    target_link_options(praylib_host PUBLIC --bind)
    target_link_options(praylib_host PUBLIC -sUSE_GLFW=3 PUBLIC)

    # wasm bigint
    target_link_options(praylib_host PUBLIC -sWASM_BIGINT=1)

    # modularize
    target_link_options(praylib_host PUBLIC -sMODULARIZE=1)


    target_link_options(praylib_host
        PUBLIC "SHELL: --post-js ${CMAKE_CURRENT_BINARY_DIR}/post.js"
        PUBLIC "SHELL: --pre-js ${pyjs_PRE_JS_PATH}"
        PUBLIC "SHELL: -s EXPORT_NAME=\"createModule\""
    )


    # set_target_properties(praylib_host PROPERTIES SUFFIX ".html")




    # install
    install(TARGETS praylib_host DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

    install(FILES
            "$<TARGET_FILE_DIR:praylib_host>/praylib_host.js"
            "$<TARGET_FILE_DIR:praylib_host>/praylib_host.wasm"
            DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

endif()
endif()