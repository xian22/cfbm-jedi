cmake_minimum_required( VERSION 3.12 )

find_package( ecbuild REQUIRED )

project( cfbm-jedi VERSION 0.0.1 LANGUAGES CXX Fortran )

include( ecbuild_system )

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------
# We need OOPS (The JEDI algorithm layer)
ecbuild_find_package( NAME oops REQUIRED )
# We need the Fire Model we just compiled
ecbuild_find_package( NAME ufs_fire_behavior REQUIRED )

# ------------------------------------------------------------------------------
# Build the JEDI Interface Library
# ------------------------------------------------------------------------------
# This assumes you will put your interface code in a 'src' folder
file( GLOB_RECURSE interface_srcs "src/*.cc" "src/*.h" "src/*.F90" )

ecbuild_add_library( TARGET   cfbm_jedi
                     SOURCES  ${interface_srcs}
                     # Link against OOPS and your Fire Model Library
                     PUBLIC_LIBS oops firelib )

# ------------------------------------------------------------------------------
# Finalize
# ------------------------------------------------------------------------------
ecbuild_install_project( NAME cfbm-jedi )
