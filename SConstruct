#!python
import os
import sys
from build_tools import get_gsl_flags, get_arma_flags, get_root_flags, write_compile_script, get_hdf_flags

# Get the locations of root, armadillo and gsl from root-config and env.sh
root_incs, root_libs  = get_root_flags()
hdf5_incs, hdf5_libs  = get_hdf_flags()
root_incs, root_libs = Split(root_incs), Split(root_libs)
armadillo_include, armadillo_lib = get_arma_flags()
gsl_include, gsl_lib = get_gsl_flags()

hdf_lib_names = ["hdf5_hl_cpp", "hdf5_cpp", "hdf5_hl", "hdf5"]

###############################
# Building the static library #
###############################

# Put built object files in build/ 
VariantDir("build", "src", duplicate=0)

# Compile all .cpp files in source tree
source_dirs  = [x[0] for x in os.walk("src/")]
source_files = []
for x in source_dirs:
    source_files += Glob(os.path.join(x,"*.cpp"))

# Create the build environment
env = Environment(CCFLAGS = '-O2', 
                  CPPPATH = source_dirs + [armadillo_include, gsl_include] + root_incs
                  )

# Build the library
objects = [env.Object(x) for x in source_files]

lib = env.Library("build/liboxsx", objects)
env.Default([objects, lib])


############################################################
# For compiling tests and user scripts against the library #
############################################################
                      
testenv = Environment(parse_flags = root_libs + root_incs,
                      CCFLAGS = "-O2",
                      CPPPATH = ["Catch/include"] + source_dirs + [gsl_include, armadillo_include],
                      LIBS = ["armadillo", "gsl", "oxsx", "Minuit2"] + hdf_lib_names,
                      LIBPATH = [gsl_lib, armadillo_lib, "build"]
                      )

unit_test_files = Glob("test/unit/*/*.cpp") + Glob("test/unit/*.cpp")
unit_tests      = [testenv.Object(x) for x in unit_test_files]

unit_test_executible = testenv.Program("test/RunUnits", 
                                       source = [unit_tests, lib],
                                       )
testenv.Alias("units", unit_test_executible)
testenv.AlwaysBuild(unit_test_executible)

######################################
# Create a compiler for user scripts #
######################################
write_compile_script(testenv, "./examples")
