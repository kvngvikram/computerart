# ulimit -s unlimited

gfortran -ffree-form -c ./npy_save.f ./julia.f
gfortran npy_save.o julia.o -o julia.out
rm npy_save.o julia.o m_npy.mod

./julia.out numpy_array.npy -5 5 -5 5 200 200
