source /Users/Jack/snoplus/gitrat.sh

for f in src/pdf/*.cpp;
do
g++ -c  $f 
done;

for f in src/data/*.cpp;
do
g++ -c  `root-config --cflags` $f 
done;

for f in src/pdf/binned/*.cpp;
do
g++ -c  $f 
done;

for f in src/pdf/analytic/*.cpp;
do
g++ -c  $f 
done;

for f in src/systematic/*.cpp;
do
g++ -c `root-config --cflags` $f
done;

# for f in src/eval/*.cpp;
# do
# g++ -c `root-config --cflags` $f
# done;

# for f in src/optimise/*.cpp;
# do
# g++ -c `root-config --cflags` $f 
# done;

mv *.o ./obj/

g++ `root-config --glibs`  -o exec obj/*.o
