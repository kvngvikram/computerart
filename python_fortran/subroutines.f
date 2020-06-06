subroutine julia_set_complex_polinomial(min_x, max_x, min_y, max_y, x_res, y_res, c, p, max_iter, max_value, n)

implicit none

!! x_res, y_res are number of points in each direction
integer, intent(in)              :: x_res, y_res, max_iter
real,    intent(in)              :: min_x, max_x, min_y, max_y, max_value
complex, intent(in)              :: c, p

real,    intent(out)             :: n(y_res, x_res)

complex                          :: z(y_res, x_res)
integer                          :: i, j, k

!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
!!                                 preperation
!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
z = 0
do concurrent (i=0:x_res-1)
    z(:,i+1) = z(:,i+1) + cmplx(min_x + i*(max_x-min_x)/(x_res-1),0)
end do
do concurrent (i=0:y_res-1)
    z(i+1,:) = z(i+1,:) + cmplx(0, max_y - i*(max_y-min_y)/(y_res-1))
end do

!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
!!                                 calculation
!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
do concurrent (i=1:x_res)
    do concurrent (j=1:y_res)
        k = 0
        do while (k<max_iter .and. abs(z(j,i)) < max_value)
            z(j,i) = z(j,i)**p + c
            k = k + 1
        end do
        if (k .eq. max_iter) then
            n(j,i) = 0
        else
            n(j,i) = k
        end if
    end do
end do

n = log(n)

end subroutine julia_set_complex_polinomial
