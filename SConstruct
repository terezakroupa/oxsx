#!python
import os
import sys

# load the environment, accounting for the dependencies
env = SConscript("config/SConscript")
env.Append(CPPPATH = "#/include")
Export('env')

# now copy the headers to include and build the library
env.SConscript("src/SConscript",
               variant_dir="build", duplicate = 0)


############################################################
# For compiling tests and user scripts against the library #
############################################################
                      
# testenv = Environment(parse_flags = root_libs + root_incs,
#                       CCFLAGS = "-O2",
#                       CPPPATH = ["Catch/include", "include", hdf5_incs, gsl_include, armadillo_include],
#                       LIBS = ["armadillo", "gsl", "gslcblas", "oxsx", "Minuit2"] + hdf_lib_names,
#                       LIBPATH = [gsl_lib, armadillo_lib, hdf5_libs, "build"]
#                       )

# unit_test_files = Glob("test/unit/*/*.cpp") + Glob("test/unit/*.cpp")
# unit_tests      = [testenv.Object(x) for x in unit_test_files]

# unit_test_executible = testenv.Program("test/RunUnits", 
#                                        source = [unit_tests, lib],
#                                        )
# testenv.Alias("units", unit_test_executible)

