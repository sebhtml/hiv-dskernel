# DSkernel
# DSkernel l sequenceFile delta_m theta_m out
./PermutationDS/PermutationDSKernel 2850 tmp/sequences.txt 30 30 tmp/MATRIX.30
./PermutationDS/PermutationDSKernel 2850 tmp/sequences.txt 35 35 tmp/MATRIX.35
./PermutationDS/PermutationDSKernel 2850 tmp/sequences.txt 40 40 tmp/MATRIX.40

#cp MATRIX.40 tmp
#cp MATRIX.35 tmp
#cp MATRIX.30 tmp

./MatrixSVM/svm_learn -u tmp/MATRIX.30 -t 4 -c 0.0001 -d 2850 tmp/train.txt.index.CXCR4 tmp/DS.CXCR4
./MatrixSVM/svm_classify tmp/test.txt.index.CXCR4 tmp/DS.CXCR4 tmp/DS.CXCR4.predictions
./Stats tmp/DS.CXCR4.predictions tmp/test.txt.index.CXCR4.y 1425 > tmp/DS.CXCR4.results
bash roc.sh tmp/test.txt.index.CXCR4.y tmp/DS.CXCR4.predictions > tmp/DS.CXCR4.roc

./MatrixSVM/svm_learn -u tmp/MATRIX.30 -t 4 -c 0.4 -d 2850 tmp/train.txt.index.CCR5 tmp/DS.CCR5
./MatrixSVM/svm_classify tmp/test.txt.index.CCR5 tmp/DS.CCR5 tmp/DS.CCR5.predictions
./Stats tmp/DS.CCR5.predictions tmp/test.txt.index.CCR5.y 1425 > tmp/DS.CCR5.results
bash roc.sh tmp/test.txt.index.CCR5.y tmp/DS.CCR5.predictions > tmp/DS.CCR5.roc

./MatrixSVM/svm_learn -u tmp/MATRIX.35 -t 4 -c 0.2 -d 2850 tmp/train.txt.index.CCR5_CXCR4 tmp/DS.CCR5_CXCR4
./MatrixSVM/svm_classify tmp/test.txt.index.CCR5_CXCR4 tmp/DS.CCR5_CXCR4 tmp/DS.CCR5_CXCR4.predictions
./Stats tmp/DS.CCR5_CXCR4.predictions tmp/test.txt.index.CCR5_CXCR4.y 1425 > tmp/DS-CCR5_CXCR4-results
bash roc.sh tmp/test.txt.index.CCR5_CXCR4.y tmp/DS.CCR5_CXCR4.predictions > tmp/DS-CCR5_CXCR4-roc

