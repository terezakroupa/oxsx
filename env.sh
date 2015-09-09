#!/bin/bash
OXSXROOT=/Users/Jack/snoplus/oxsx
PATH=/Users/Jack/snoplus/snoing/install/root-5.34.30/bin:/Users/Jack/snoplus/snoing/install/scons-2.3.4/script:$PATH
PYTHONPATH=$OXSXROOT/util:/Users/Jack/snoplus/snoing/install/scons-2.3.4/engine:$PYTHONPATH
LD_LIBRARY_PATH=$OXSXROOT/build:$LD_LIBRARY_PATH

export ROOTSYS=/Users/Jack/snoplus/snoing/install/root-5.34.30
export OXSX_SCONS=/Users/Jack/snoplus/snoing/install/scons-2.3.4
export LD_LIBRARY_PATH PYTHONPATH OXSXROOT
