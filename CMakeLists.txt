cmake_minimum_required( VERSION 3.12 )

find_package( ecbuild REQUIRED )

project( cfbm-jedi VERSION 0.0.1 LANGUAGES CXX Fortran )

include( ecbuild_system )

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
# We need OOPS (The JEDI algorithm layer)
ecbuild_find_package( NAME oops REQUIRED )

# ADD THIS: We need fckit to pass Configs to Fortran
ecbuild_find_package( NAME fckit REQUIRED )

# We need the Fire Model we just compiled
ecbuild_find_package( NAME ufs_fire_behavior REQUIRED )

ecbuild_find_package( NAME atlas REQUIRED )

# ------------------------------------------------------------------------------
# Build the JEDI Interface Library
# ------------------------------------------------------------------------------
# This GLOB will automatically pick up your new .F90 file in src/cfbm/
file( GLOB_RECURSE interface_srcs "src/*.cc" "src/*.h" "src/*.F90" )

ecbuild_add_library( TARGET   cfbm_jedi
                     SOURCES  ${interface_srcs}
                     INCLUDES $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
                     # ADD fckit HERE:
                     PUBLIC_LIBS oops firelib fckit )

# ------------------------------------------------------------------------------
#  EXECUTABLES
# ------------------------------------------------------------------------------
ecbuild_add_executable( TARGET cfbm_test_geometry.x
                        SOURCES src/mains/TestGeometry.cc
                        LIBS cfbm_jedi )

# (Optional) Register this as a formal test so you can run 'ctest'
ecbuild_add_test( TARGET cfbm_test_geometry
                  COMMAND cfbm_test_geometry.x
                  ARGS "test_geometry.yaml"
                  TEST_DEPENDS cfbm_jedi )

# ------------------------------------------------------------------------------
# Finalize
# ------------------------------------------------------------------------------
ecbuild_install_project( NAME cfbm-jedi )