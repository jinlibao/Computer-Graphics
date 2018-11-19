cmake_minimum_required (VERSION 3.2)
project (Rayshader)
set (CMAKE_C_COMPILER "clang")
set (CMAKE_CXX_COMPILER "clang++")
set (CMAKE_CXX_FLAGS "-std=c++17 -stdlib=libc++ -Wno-deprecated")
include_directories ("${PROJECT_SOURCE_DIR}/include")

option (OPENGL_USE_APPLE_X11 "Use X11" OFF)
option (USE_FREEIMAGE "Use FreeImage" OFF)

if (OPENGL_USE_APPLE_X11)
    include_directories ("/opt/X11/include")
    find_library (OPENGL_gl_LIBRARY gl /opt/X11/lib)
    find_library (OPENGL_glu_LIBRARY glu /opt/X11/lib)
    set (OPENGL_glut_LIBRARY /opt/X11/lib/libglut.dylib)
    message ("${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${OPENGL_glut_LIBRARY}")
    set (EXTRA_LIBS ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${OPENGL_glut_LIBRARY})
    # project 3a
    add_executable (main3aX11 main.cpp)
    set (ATARGETFLAGS -DX11=1 -DPROJECT=\\"proj3a\\")
    string (REPLACE ";" " " ATARGETFLAGS "${ATARGETFLAGS}")
    set_target_properties (main3aX11 PROPERTIES COMPILE_FLAGS ${ATARGETFLAGS})
    target_link_libraries (main3aX11 ${EXTRA_LIBS})
    # project 3b
    add_executable (main3bX11 main.cpp)
    set (BTARGETFLAGS -DX11=1 -DPROJECT=\\"proj3b\\")
    string (REPLACE ";" " " BTARGETFLAGS "${BTARGETFLAGS}")
    set_target_properties (main3bX11 PROPERTIES COMPILE_FLAGS ${BTARGETFLAGS})
    target_link_libraries (main3bX11 ${EXTRA_LIBS})
    # project 3c
    add_executable (main3cX11 main.cpp)
    set (CTARGETFLAGS -DX11=1 -DPROJECT=\\"proj3c\\")
    string (REPLACE ";" " " CTARGETFLAGS "${CTARGETFLAGS}")
    set_target_properties (main3cX11 PROPERTIES COMPILE_FLAGS ${CTARGETFLAGS})
    target_link_libraries (main3cX11 ${EXTRA_LIBS})


    if (USE_FREEIMAGE)
        # add FreeImage include and lib
        include_directories ("/usr/local/include")
        find_library (FREEIMAGE_LIBRARY freeimage /usr/local/lib)
        set (EXTRA_LIBS ${EXTRA_LIBS} ${FREEIMAGE_LIBRARY})

        # project 3a
        add_executable (main3aX11F main.cpp)
        set (ATARGETFLAGS "${ATARGETFLAGS} -DUSEFREEIMAGE=1")
        message ("${EXTRA_LIBS} ${ATARGETFLAGS}")
        set_target_properties (main3aX11F PROPERTIES COMPILE_FLAGS ${ATARGETFLAGS})
        target_link_libraries (main3aX11F ${EXTRA_LIBS})

        # project 3b
        add_executable (main3bX11F main.cpp)
        set (BTARGETFLAGS "${BTARGETFLAGS} -DUSEFREEIMAGE=1")
        set_target_properties (main3bX11F PROPERTIES COMPILE_FLAGS ${BTARGETFLAGS})
        target_link_libraries (main3bX11F ${EXTRA_LIBS})

        # project 3c
        add_executable (main3cX11F main.cpp)
        set (CTARGETFLAGS "${CTARGETFLAGS} -DUSEFREEIMAGE=1")
        set_target_properties (main3cX11F PROPERTIES COMPILE_FLAGS ${CTARGETFLAGS})
        target_link_libraries (main3cX11F ${EXTRA_LIBS})
    endif (USE_FREEIMAGE)
endif (OPENGL_USE_APPLE_X11)

if (APPLE)
    # include_directories (/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk/System/Library/Frameworks/)
    include_directories (/System/Library/Frameworks/)
    find_library (GLUT_LIBRARIES GLUT)
    find_library (OpenGL_LIBRARIES OpenGL)
    set (EXTRA_LIBS ${GLUT_LIBRARIES} ${OpenGL_LIBRARIES})

    # project 3a
    add_executable (main3a main.cpp)
    set_target_properties (main3a PROPERTIES COMPILE_FLAGS -DPROJECT=\\"proj3a\\")
    target_link_libraries (main3a ${EXTRA_LIBS})
    # project 3b
    add_executable (main3b main.cpp)
    set_target_properties (main3b PROPERTIES COMPILE_FLAGS -DPROJECT=\\"proj3b\\")
    target_link_libraries (main3b ${EXTRA_LIBS})
    # project 3c
    add_executable (main3c main.cpp)
    set_target_properties (main3c PROPERTIES COMPILE_FLAGS -DPROJECT=\\"proj3c\\")
    target_link_libraries (main3c ${EXTRA_LIBS})

    if (USE_FREEIMAGE)
        include_directories ("/usr/local/include")
        find_library (FREEIMAGE_LIBRARY freeimage /usr/local/lib)
        set (EXTRA_LIBS ${EXTRA_LIBS} ${FREEIMAGE_LIBRARY})
        # project 3a
        add_executable (main3aF main.cpp)
        set (ATARGETFLAGS -DPROJECT=\\"proj3a\\" -DUSEFREEIMAGE=1)
        string (REPLACE ";" " " ATARGETFLAGS "${ATARGETFLAGS}")
        set_target_properties (main3aF PROPERTIES COMPILE_FLAGS ${ATARGETFLAGS})
        target_link_libraries (main3aF ${EXTRA_LIBS})
        # project 3b
        add_executable (main3bF main.cpp)
        set (BTARGETFLAGS -DPROJECT=\\"proj3b\\" -DUSEFREEIMAGE=1)
        string (REPLACE ";" " " BTARGETFLAGS "${BTARGETFLAGS}")
        set_target_properties (main3bF PROPERTIES COMPILE_FLAGS ${BTARGETFLAGS})
        target_link_libraries (main3bF ${EXTRA_LIBS})
        # project 3c
        add_executable (main3cF main.cpp)
        set (CTARGETFLAGS -DPROJECT=\\"proj3c\\" -DUSEFREEIMAGE=1)
        string (REPLACE ";" " " CTARGETFLAGS "${CTARGETFLAGS}")
        set_target_properties (main3cF PROPERTIES COMPILE_FLAGS ${CTARGETFLAGS})
        target_link_libraries (main3cF ${EXTRA_LIBS})
    endif (USE_FREEIMAGE)
endif (APPLE)
