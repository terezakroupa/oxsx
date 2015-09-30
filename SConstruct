#!python
import subprocess
import os

root_flags = Split(subprocess.check_output("root-config --cflags --glibs", shell=True))
root_flags += ["-lMinuit2"]
root_flags += Split("-I/opt/local/include -L/opt/local/lib -lgsl -lgslblas")
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
tests = env.Program("test/RunTests", Glob("test/*/*.cpp") + Glob("test/*.cpp"), 
                    LIBS = ['oxsx', 'armadillo', "gsl"], LIBPATH = ["build", "/opt/local/lib/"],
                    CPPPATH = source_dirs + root_flags + ["Catch/include"]
                    )
env.Alias("tests", tests)
