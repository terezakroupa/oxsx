#!python
import os
import sys

try:
    from subprocess import check_output

except:
    print "Failed. are you running python 2.7"
    sys.exit()

#use root utility to find out where the includes and libs are, Minuit2 not included by default 
# Get the external library dependencies from the environment
try:
    armadillo_lib     = os.environ["ARMA_LIB"]
    armadillo_include = os.environ["ARMA_HEADER"]

except:
    print "Couldnt find armadillo enviroment vars - are they set?"
    sys.exit()

root_incs     = Split(check_output("root-config --cflags", shell=True))
root_libs     = Split(check_output("root-config --libs", shell=True))

env = Environment(CCFLAGS = '-O2')

# Put built object files in build/ 
VariantDir("build", "src", duplicate=0)

# Compile all .cpp files in source tree
source_dirs  = [x[0] for x in os.walk("src")]
source_files = []
for x in source_dirs:
    source_files += Glob(os.path.join(x,"*.cpp"))

# Create the build environment
env = Environment(CCFLAGS = '-O2', 
                  CPPPATH = source_dirs + [armadillo_include] + root_incs
                  )

# Build the library
objects = [env.Object(x) for x in source_files]
lib = env.Library("build/liboxsx", objects)
env.Default([objects, lib])


############################################################
# For compiling tests and user scripts against the library #
############################################################
                      
testenv = Environment(parse_flags = root_libs,
                      CCFLAGS = "-O2",
                      CPPPATH = ["Catch/include"] + source_dirs + root_incs,
                      )
testenv.Append(LIBS=["armadillo", "gsl"], LIBPATHS=armadillo_lib)

unit_test_files = Glob("test/unit/*/*.cpp") + Glob("test/unit/*.cpp")
unit_tests = [testenv.Object(x) for x in unit_test_files]

unit_test_executible = testenv.Program("test/RunUnits", 
                                       source = [unit_tests, lib],
                                       )

testenv.Alias("units", [unit_tests, unit_test_executible])
