
mkdir -p tmp
rm tmp/* -Rf

# generate sequences
cat train.txt test.txt|awk '{print $3}' > tmp/sequences.txt

index=0
# train index file
for tropism in $(cat train.txt|awk '{print $2}')
do
	echo "$tropism # $index"
	index=$(($index+1))
done > tmp/train.txt.index

# test index file
for tropism in $(cat test.txt|awk '{print $2}')
do
	echo "$tropism # $index"
	index=$(($index+1))
done>tmp/test.txt.index

for file in train.txt test.txt
do
	cat $file |awk '{print $2" "$3}' > tmp/$file.seq
done

for file in train.txt.index test.txt.index train.txt.seq test.txt.seq
do
	ruby coreceptorUsage.rb tmp/$file +1 -1 +1 > tmp/$file.CCR5
	cat tmp/$file.CCR5|awk '{print $1}'>tmp/$file.CCR5.y
	ruby coreceptorUsage.rb tmp/$file -1 +1 +1 > tmp/$file.CXCR4
	cat tmp/$file.CXCR4|awk '{print $1}'>tmp/$file.CXCR4.y
	ruby coreceptorUsage.rb tmp/$file -1 -1 +1 > tmp/$file.CCR5_CXCR4
	cat  tmp/$file.CCR5_CXCR4|awk '{print $1}'> tmp/$file.CCR5_CXCR4.y
done

