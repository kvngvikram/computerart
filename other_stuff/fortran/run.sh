# ulimit -s unlimited

gfortran -ffree-form -c ./npy_save.f ./julia.f
gfortran npy_save.o julia.o -o julia.out
rm npy_save.o julia.o m_npy.mod

time ./julia.out /tmp/tmp_numpy_array.npy -5 5 -5 5 1920 1080
