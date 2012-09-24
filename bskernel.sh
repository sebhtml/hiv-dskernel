# BSkernel
./BS/BSMatrix 2850 tmp/sequences.txt 9  tmp/BS-Matrix-9.txt
./BS/BSMatrix 2850 tmp/sequences.txt 3  tmp/BS-Matrix-3.txt
./BS/BSMatrix 2850 tmp/sequences.txt 15  tmp/BS-Matrix-15.txt

#cp BS-Matrix-3.txt tmp
./MatrixSVM/svm_learn -u tmp/BS-Matrix-3.txt -t 4 -c 0.04 -d 2850 tmp/train.txt.index.CCR5 tmp/BS.CCR5
./MatrixSVM/svm_classify tmp/test.txt.index.CCR5 tmp/BS.CCR5 tmp/BS.CCR5.predictions
./Stats tmp/BS.CCR5.predictions tmp/test.txt.index.CCR5.y 1425 > tmp/BS-CCR5-results
bash roc.sh tmp/test.txt.index.CCR5.y tmp/BS.CCR5.predictions > tmp/BS-CCR5-roc

#cp BS-Matrix-9.txt tmp
./MatrixSVM/svm_learn -u tmp/BS-Matrix-9.txt -t 4 -c 0.7 -d 2850 tmp/train.txt.index.CXCR4 tmp/BS.CXCR4
./MatrixSVM/svm_classify tmp/test.txt.index.CXCR4 tmp/BS.CXCR4 tmp/BS.CXCR4.predictions
./Stats tmp/BS.CXCR4.predictions tmp/test.txt.index.CXCR4.y 1425 > tmp/BS-CXCR4-results
bash roc.sh tmp/test.txt.index.CXCR4.y tmp/BS.CXCR4.predictions > tmp/BS-CXCR4-roc

#cp BS-Matrix-15.txt tmp
./MatrixSVM/svm_learn -u tmp/BS-Matrix-15.txt -t 4 -c 2 -d 2850 tmp/train.txt.index.CCR5_CXCR4 tmp/BS.CCR5_CXCR4
./MatrixSVM/svm_classify tmp/test.txt.index.CCR5_CXCR4 tmp/BS.CCR5_CXCR4 tmp/BS.CCR5_CXCR4.predictions
./Stats tmp/BS.CCR5_CXCR4.predictions tmp/test.txt.index.CCR5_CXCR4.y 1425 > tmp/BS-CCR5_CXCR4-results
bash roc.sh tmp/test.txt.index.CCR5_CXCR4.y tmp/BS.CCR5_CXCR4.predictions > tmp/BS-CCR5_CXCR4-roc
