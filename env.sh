#!/bin/bash

#Set these for the installation paths
SCONS_DIR="/data/snoplus/software/snocave_SL6/scons-2.3.4"
ROOT_DIR="/data/snoplus/software/snocave_SL6/root-5.34.30"

#####################################################
# Shouldn't need to change anything below this line #
#####################################################

OXSXROOT="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

PATH=$ROOT_DIR/bin:/$SCONS_DIR/script:$PATH

#tells python where the utility functions are
PYTHONPATH=$OXSXROOT/util:/data/snoplus/software/snocave_SL6/scons-2.3.4/engine:$PYTHONPATH
LD_LIBRARY_PATH=$OXSXROOT/build:$ROOT_DIR/lib:$LD_LIBRARY_PATH
DYLD_LIBRARY_PATH=$ROOT_DIR:$DYLD_LIBRARY_PATH

export LD_LIBRARY_PATH PYTHONPATH DYLD_LIBRARY_PATH
