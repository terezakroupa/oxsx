#!python
import os
import sys

# load the environment, accounting for the dependencies
env = SConscript("config/SConscript")
env.Append(CPPPATH = "#/include")
Export('env')

# now copy the headers to include and build the library
lib = env.SConscript("src/SConscript",
                     variant_dir="build", duplicate = 0)
Export('lib')

# now build the tests
env.SConscript("test/unit/SConscript")

