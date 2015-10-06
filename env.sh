#!/bin/bash

#Set these for the installation paths
SCONS_DIR=/Users/Jack/snoplus/snoing/install/scons-2.3.4
ROOT_DIR=/Users/Jack/snoplus/snoing/install/root-5.34.30

# location of armadillo includes and libraries. 
# If these are installed to any of the standard /usr/... they may be left blank
ARMA_LIB=""
ARMA_HEADER=""
GSL_LIB=/opt/local/lib
GSL_HEADER=/opt/local/include

#####################################################
# Shouldn't need to change anything below this line #
#####################################################

OXSXROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

PATH=$ROOT_DIR/bin:/$SCONS_DIR/script:$PATH

#tells python where the utility functions are
PYTHONPATH=$OXSXROOT/util:/data/snoplus/software/snocave_SL6/scons-2.3.4/engine:$PYTHONPATH
export ARMA_HEADER ARMA_LIB GSL_LIB GSL_HEADER PYTHONPATH 
