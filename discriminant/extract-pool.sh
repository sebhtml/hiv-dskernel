
# usage extract-pool x-file id-file

# x-file: a file with lines
# id-file: a file with line number, starting at 0

file=$1
idfile=$2

for id in $(cat $idfile)
do
	head -n$(($id+1)) $file|tail -n1
done
