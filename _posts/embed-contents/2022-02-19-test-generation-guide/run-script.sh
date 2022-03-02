scriptFile=$1
curDir=`pwd`
outDir="$curDir/out"
mkdir -p $outDir

if [[ -n "$1" ]]; then
    echo "Cd to $2"
    cd $2
fi
while read line; do
    echo "\$ $line"
    eval $line
done < $curDir/$scriptFile > $outDir/$scriptFile.out
