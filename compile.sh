cd BS
g++ -Wall BSMatrix.cpp -o BSMatrix -O4
cd ..

cd LA/LAkernel-0.3.2
gcc -Wall -O4 compute_matrix.c LAkernel.c -o compute_matrix -lm
cd ../..

cd PermutationDS
g++ PermutationDSKernel.cpp -Wall -O4 -o PermutationDSKernel
cd ..


cd MatrixSVM
make
cd ..

g++ Stats.cpp -O4 -o Stats
