#!/bin/bash

#Set these for the installation paths
#SCONS_DIR=/Users/Jack/snoplus/snoing/install/scons-2.3.4
#ROOT_DIR=/Users/Jack/snoplus/snoing/install/root-5.34.30

# location of armadillo includes and libraries. 
# If these are installed to any of the standard /usr/... they may be left blank
# h5c++ -show tells you where the hdf libraries are (-L/.....)
PACKAGES_ROOT=/home/tseng/dev/snoplus
ARMA_LIB=$PACKAGES_ROOT/armadillo/usr/lib
ARMA_HEADER=$PACKAGES_ROOT/armadillo/usr/include
GSL_LIB=""
GSL_HEADER=""
HDF_HEADER=$PACKAGES_ROOT/hdf5/include
HDF_LIB=$PACKAGES_ROOT/hdf5/lib

ROOT_LIBDIR=`root-config --libdir`

#####################################################
# Shouldn't need to change anything below this line #
#####################################################
OXSXROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

#PATH=$ROOT_DIR/bin:/$SCONS_DIR/script:$PATH
#PATH=$ROOT_DIR/bin:$PATH

#tells python where the utility functions are
#PYTHONPATH=$OXSXROOT/util:$SCONS_DIR/engine:$PYTHONPATH
PYTHONPATH=$OXSXROOT/util:/usr/lib/scons/SCons:$PYTHONPATH
LD_LIBRARY_PATH=$OXSXROOT/build:$ROOT_LIBDIR:$ARMA_LIB:$HDF_LIB:$LD_LIBRARY_PATH
#DYLD_LIBRARY_PATH=$ROOT_LIBDIR:$ARMA_LIB:$HDF_LIB:$DYLD_LIBRARY_PATH

export ARMA_HEADER ARMA_LIB GSL_LIB GSL_HEADER PYTHONPATH LD_LIBRARY_PATH DYLD_LIBRARY_PATH HDF_LIB HDF_HEADER
