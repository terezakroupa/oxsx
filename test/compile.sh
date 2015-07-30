g++ -L../build -loxsx -I../src/pdf -I../src/pdf/binned -I../src/pdf/analytic -I../src/pdf/analytic -I../src/data `root-config --cflags --glibs`  $1 
