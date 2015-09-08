#!/bin/bash
OXSXROOT=/Users/Jack/snoplus/sigEx/oxsx/
PATH=/Users/Jack/snoplus/snoing/install/scons-2.3.4/script:$PATH
PYTHONPATH=$OXSXROOT/util:/Users/Jack/snoplus/snoing/install/scons-2.3.4/engine:$PYTHONPATH
LD_LIBRARY_PATH=$OXSXROOT/build:$LD_LIBRARY_PATH

export OXSX_SCONS=/Users/Jack/snoplus/snoing/install/scons-2.3.4
export LD_LIBRARY_PATH PYTHONPATH OXSXROOT
