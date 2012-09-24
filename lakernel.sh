
#cp LA-E* tmp
# LAkernel
cd LA/LAkernel-0.3.2


rm -Rf parameters.txt
cp 0.05-parameters.txt parameters.txt
./compute_matrix 2850 ../../tmp/sequences.txt 0.05 ../../tmp/LA-Emp-0.05

rm -Rf parameters.txt
cp 1-parameters.txt parameters.txt
./compute_matrix 2850 ../../tmp/sequences.txt 1 ../../tmp/LA-Emp-1

rm -Rf parameters.txt
cp 0.1-parameters.txt parameters.txt
./compute_matrix 2850 ../../tmp/sequences.txt 0.1 ../../tmp/LA-Emp-0.1

cd ../..

# R5
./MatrixSVM/svm_learn -u tmp/LA-Emp-0.05 -t 4 -c 0.02 -d 2850 tmp/train.txt.index.CXCR4 tmp/LA.CXCR4
./MatrixSVM/svm_classify tmp/test.txt.index.CXCR4 tmp/LA.CXCR4 tmp/LA.CXCR4.predictions
./Stats tmp/LA.CXCR4.predictions tmp/test.txt.index.CXCR4.y 1425 > tmp/LA.CXCR4.results
bash roc.sh tmp/test.txt.index.CXCR4.y tmp/LA.CXCR4.predictions > tmp/LA.CXCR4.roc

./MatrixSVM/svm_learn -u tmp/LA-Emp-1 -t 4 -c 9 -d 2850 tmp/train.txt.index.CCR5 tmp/LA.CCR5
./MatrixSVM/svm_classify tmp/test.txt.index.CCR5 tmp/LA.CCR5 tmp/LA.CCR5.predictions
./Stats tmp/LA.CCR5.predictions tmp/test.txt.index.CCR5.y 1425 > tmp/LA.CCR5.results
bash roc.sh tmp/test.txt.index.CCR5.y tmp/LA.CCR5.predictions > tmp/LA.CCR5.roc

./MatrixSVM/svm_learn -u tmp/LA-Emp-0.1 -t 4 -c 0.5 -d 2850 tmp/train.txt.index.CCR5_CXCR4 tmp/LA.CCR5_CXCR4
./MatrixSVM/svm_classify tmp/test.txt.index.CCR5_CXCR4 tmp/LA.CCR5_CXCR4 tmp/LA.CCR5_CXCR4.predictions
./Stats tmp/LA.CCR5_CXCR4.predictions tmp/test.txt.index.CCR5_CXCR4.y 1425 > tmp/LA-CCR5_CXCR4-results
bash roc.sh tmp/test.txt.index.CCR5_CXCR4.y tmp/LA.CCR5_CXCR4.predictions > tmp/LA-CCR5_CXCR4-roc
