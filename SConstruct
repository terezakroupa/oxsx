#!python
import subprocess
import os
import sys

#use root utility to find out where the includes and libs are, Minuit2 not included by default 
root_incs = Split(subprocess.check_output("root-config --cflags", shell=True))
root_libs = Split(subprocess.check_output("root-config --glibs --noldflags", 
                                          shell=True)) + ["-lMinuit2"]

root_lib_dir  = subprocess.check_output("root-config --libdir", shell=True)

# Get the external library dependencies from the environment
try:
    armadillo_path = os.environ.get("OXSXROOT")
    print armadillo_path

except:
    print "Build failed, please source environment"


# Put built object files in build/ 
VariantDir("build", "src", duplicate=0)

# Compile all .cpp files in source tree
source_dirs  = [x[0] for x in os.walk("src")]
source_files = []
for x in source_dirs:
    source_files += Glob(os.path.join(x,"*.cpp"))


# Create the build environment
env = Environment(CCFLAGS = '-O2', CPPPATH = source_dirs + root_incs + ["Catch/include"])

# Build the library
objects = [env.Object(x) for x in source_files]
lib = env.Library("build/liboxsx", objects)
env.Default([objects, lib])


############################################################
# For compiling tests and user scripts against the library #
############################################################

unit_test_files = Glob("test/unit/*/*.cpp") + Glob("test/unit/*.cpp")
unit_tests = [testenv.Object(x) for x in unit_test_files]

unit_test_executible = testenv.Program("test/RunUnits", source = [unit_tests, lib])

env.Alias("units", [unit_tests, unit_test_executible])
