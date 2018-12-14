program trying_complex

implicit none

integer :: p=1 , q=3 , i=1 , j=1  
complex :: cc(2,3)
integer :: a(10) 


do i = p,q
  print*,i
end do

print*, cc*0+1 

do i = p,q 
  do j = p,q
    cc(i,j) = cmplx(i,j)
  end do
end do        

print*, cc 

end program trying_complex
