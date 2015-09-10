str=""
for dir in $(find $OXSXROOT/src -type d)
do
str="-I $dir $str"
done

outname=$(basename $1)
outname="${outname%.*}"

g++ -L$OXSXROOT/build -loxsx -I$OXSXROOT/bench -o $outname $str `root-config --cflags --glibs`  $1 $OXSXROOT/bench/build/Bench.o