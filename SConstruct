#!python
import os

root_flags = Split("""-pthread -stdlib=libc++ -m64 
                    -I/Users/Jack/snoplus/snoing/install/root-5.34.30/include""")
env = Environment()

VariantDir("build", "src", duplicate=0)

source_dirs = Split(
'''
build/data
build/pdf
build/pdf/analytic
build/pdf/binned
build/systematic
'''
)

source_files = []
for x in source_dirs:
    source_files += Glob(os.path.join(x,"*.cpp"))

# By default just build the source
objects = [Object(x, CPPPATH = source_dirs + root_flags) for x in source_files]
lib = Library("build/liboxsx", objects)
env.Default([objects, lib])

# Build the tests
tests = [Object(x, CPPPATH = source_dirs + root_flags) for x in Glob("test/*.cpp")]
env.Alias("tests", tests)
