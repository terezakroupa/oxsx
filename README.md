<h1> OXSX </h2>
Signal Extraction framework for the SNO+ experiment


<h2> Dependencies </h2>
1. [Armadillo](http://arma.sourceforge.net/) is a linear algebra package used for quick matrix multiplication
2. [GSL](https://gcc.gnu.org/libstdc++/) - likely you already have this installed, especially if you are running RAT
3. [SCons](http://www.scons.org/) Is used for the build, also a dependency for RAT
4. [HDF5](https://www.hdfgroup.org/HDF5/release/obtain5.html)
Follow the installation instructions for each of the above using either the default install location or a different directory if you would prefer.

<h2>Installation Instructions </h2>

1. Clone this repository with ```git clone https://github.com/jackdunger/oxsx.git --recursive``` if you've already cloned without the recursive flag just run ```git submodule update --init```

2. Update env.sh to point to ROOT and scons installs 
e.g.
 ```ROOT_DIR    =  /software/..../root-5.34.30   ```
 ```SCONS_DIR   =  /software/..../scons-2.3.4```


3. Do the same for GSL,armadillo, HDF5 and if these were installed to system dirs /user/lib etc. these can be left as empty strings ""

4. Run ```source env.sh && scons && scons units```

5. Test the build was sucessful with ```./tests/RunUnits```


<h3> Compiling Your Own Scripts</h3>

scons auto-generates a script that compiles and links your c++ against the source code and dependencies just run ```./examples/compile.sh <your cpp file>``` to produce an executible of the same name

