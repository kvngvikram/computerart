python_wrapper:
	ln -sf subroutines.f subroutines.f90
	f2py -c subroutines.f90 -m fortran_subroutines
	rm subroutines.f90

clean:
	rm fortran_subroutines.cpython*
