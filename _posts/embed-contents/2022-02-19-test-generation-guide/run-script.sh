scriptFile=$1
curDir=`pwd`
if [[ -n "$1"  ]]; then
    echo "Go to $2"
    cd $2
fi
while read line; do
    echo "> $line"
    eval $line
done < $curDir/$scriptFile > $curDir/$scriptFile.out
