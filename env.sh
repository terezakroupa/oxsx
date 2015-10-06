#!/bin/bash

#Set these for the installation paths
SCONS_DIR=/data/snoplus/software/snocave_SL6/scons-2.3.4/
ROOT_DIR=/data/snoplus/software/snocave_SL6/root-5.34.30/

# location of armadillo includes and libraries. 
# If these are installed to any of the standard /usr/... they may be left blank
ARMA_LIB=""
ARMA_HEADER=""
GSL_LIB=""
GSL_HEADER=""

#####################################################
# Shouldn't need to change anything below this line #
#####################################################

OXSXROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

PATH=$ROOT_DIR/bin:/$SCONS_DIR/script:$PATH

#tells python where the utility functions are
PYTHONPATH=$OXSXROOT/util:/data/snoplus/software/snocave_SL6/scons-2.3.4/engine:$PYTHONPATH
LD_LIBRARY_PATH=$ROOT_DIR/lib:$LD_LIBRARY_PATH
export ARMA_HEADER ARMA_LIB GSL_LIB GSL_HEADER PYTHONPATH LD_LIBRARY_PATH
