program trying_complex

implicit none

integer :: min_x =-3 , max_x = 1 
integer :: min_y =-2, max_y =4
integer :: p = 2 , q = 3
complex :: cc(2,3)

integer :: i=1 , j=1  


print*, cc*0+1 

do i = 1,p
  do j = 1,q
    cc(i,j) = cmplx(j,i)
  end do
end do        

print*, cc 

end program trying_complex
