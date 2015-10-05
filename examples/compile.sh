str=""
for dir in $(find $OXSXROOT/src -type d)
do
str="-I $dir $str"
done



outname=$(basename $1)
outname="${outname%.*}"

g++ -O2  -L$OXSXROOT/build -L/opt/local/lib -I/opt/local/include -loxsx -lMinuit2 -larmadillo -lgsl -o $outname $str `root-config --cflags --glibs`  $1
