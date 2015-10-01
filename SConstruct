#!python
import subprocess
import os

root_flags = Split(subprocess.check_output("root-config --cflags --glibs", shell=True))
root_flags += ["-lMinuit2"]
root_flags += Split("-I/opt/local/include -L/opt/local/lib -lgsl -lgslcblas")

env = Environment(CCFLAGS = '-O2')
#env = Environment()

VariantDir("build", "src", duplicate=0)

source_dirs = Split(
'''
build/data
build/rand
build/teststat
build/optimise
build/pdf
build/pdf/analytic
build/pdf/binned
build/systematic
build/binnedfit
'''
)

source_files = []
for x in source_dirs:
    source_files += Glob(os.path.join(x,"*.cpp"))

# By default just build the source
objects = [env.Object(x, CPPPATH = source_dirs + root_flags) for x in source_files]
lib = env.Library("build/liboxsx", objects)
env.Default([objects, lib])

# Build the tests
unit_tests = [env.Object(x, CPPPATH = source_dirs + root_flags + ["-ICatch/include"]
                         ) for x in  Glob("test/unit/*/*.cpp") + Glob("test/unit/*.cpp")]

unit_test_executable = Program("test/RunUnits", unit_tests, 
                               LIBPATH = ["/Users/Jack/snoplus/oxsx/build", 
                                          "/Users/Jack/snoplus/snoing/install/root-5.34.30/lib",
                                          "/opt/local/lib"],
                               RPATH = root_flags,
                               LIBS = ["liboxsx", "Hist", "Core","MathCore", "armadillo", "gsl", 
                                       "gslcblas"])
env.Alias("units", [unit_tests, unit_test_executable])
