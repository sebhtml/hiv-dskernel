# DSkernel on test
./MatrixSVM/svm_learn  -u tmp/MATRIX.40 -t 4 -c 0.1 -d 2850 tmp/test.txt.index.CXCR4 tmp/DS.CXCR4-test
./MatrixSVM/svm_classify tmp/test.txt.index.CXCR4 tmp/DS.CXCR4-test tmp/DS.CXCR4.predictions-test
./Stats tmp/DS.CXCR4.predictions-test tmp/test.txt.index.CXCR4.y 1425 > tmp/DS.CXCR4.results-test
bash roc.sh tmp/test.txt.index.CXCR4.y tmp/DS.CXCR4.predictions-test > tmp/DS.CXCR4.roc-test

./MatrixSVM/svm_learn  -u tmp/MATRIX.40 -t 4 -c 0.1 -d 2850 tmp/test.txt.index.CCR5 tmp/DS.CCR5-test
./MatrixSVM/svm_classify tmp/test.txt.index.CCR5 tmp/DS.CCR5-test tmp/DS.CCR5.predictions-test
./Stats tmp/DS.CCR5.predictions-test tmp/test.txt.index.CCR5.y 1425 > tmp/DS.CCR5.results-test
bash roc.sh tmp/test.txt.index.CCR5.y tmp/DS.CCR5.predictions-test > tmp/DS.CCR5.roc-test

./MatrixSVM/svm_learn  -u tmp/MATRIX.40 -t 4 -c 0.1 -d 2850 tmp/test.txt.index.CCR5_CXCR4 tmp/DS.CCR5_CXCR4-test
./MatrixSVM/svm_classify tmp/test.txt.index.CCR5_CXCR4 tmp/DS.CCR5_CXCR4-test tmp/DS.CCR5_CXCR4.predictions-test
./Stats tmp/DS.CCR5_CXCR4.predictions-test tmp/test.txt.index.CCR5_CXCR4.y 1425 > tmp/DS-CCR5_CXCR4-results-test
bash roc.sh tmp/test.txt.index.CCR5_CXCR4.y tmp/DS.CCR5_CXCR4.predictions-test > tmp/DS-CCR5_CXCR4-roc-test
