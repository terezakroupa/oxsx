#!/bin/bash
OXSXROOT=/Users/Jack/snoplus/oxsx

PATH=/Users/Jack/snoplus/snoing/install/root-5.34.30/bin:/Users/Jack/snoplus/snoing/install/scons-2.3.4/script:/Users/jack/snoplus/snoing/install/root-5.34.30/include$PATH

PYTHONPATH=$OXSXROOT/util:/Users/Jack/snoplus/snoing/install/scons-2.3.4/engine:$PYTHONPATH
LD_LIBRARY_PATH=$OXSXROOT/build:/Users/Jack/snoplus/snoing/install/root-5.34.30/lib:$LD_LIBRARY_PATH

DYLD_LIBRARY_PATH=/Users/Jack/snoplus/snoing/install/root-5.34.30/lib:$DYLD_LIBRARY_PATH
export ROOTSYS=/Users/Jack/snoplus/snoing/install/root-5.34.30
export OXSX_SCONS=/Users/Jack/snoplus/snoing/install/scons-2.3.4
export LD_LIBRARY_PATH PYTHONPATH OXSXROOT DYLD_LIBRARY_PATH
