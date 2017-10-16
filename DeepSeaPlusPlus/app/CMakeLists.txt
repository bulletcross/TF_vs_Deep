# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.5)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             src/main/cpp/native-lib.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

if(NOT log-lib)
   message(STATUS "log library cannot be found")
else()
   message(STATUS "found log library")
endif()

find_package( BLAS REQUIRED)

if(BLAS_FOUND)
  message(STATUS "BLAS found")
else()
  message(STATUS "BLAS not found")
endif()

#set( blaze_src_DIR ../../../blaze-3.2 )
#set( blaze_build_DIR ../../../lib_source/blaze/outputs )
#file(MAKE_DIRECTORY ${blaze_build_DIR})
#add_subdirectory(${blaze_src_DIR} ${blaze_build_DIR} )

#find_package( blaze )

#if( blaze_FOUND )
#   add_library( blaze_target INTERFACE )
#  target_link_libraries( blaze_target INTERFACE blaze::blaze )
#  message(STATUS "Added blaze library")
#else()
#  message(STATUS "Still Could not add blaze library")
#endif()

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )