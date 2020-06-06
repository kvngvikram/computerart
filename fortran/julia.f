program julia_set_complex_polinomial

use m_npy ! this module has su

implicit none
integer                          :: x_res, y_res  ! number of points
real                             :: min_x, max_x, min_y, max_y
character(:), allocatable        :: npy_save_file_name

integer                          :: max_iter=5
complex                          :: c = (0,1), power = (2,0)

complex, allocatable             :: z(:,:)

integer                          :: i, j   ! can also be used temporarily
character(:), allocatable        :: tmp_str

!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
!!                             read input aurguments
!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!

!! First, make sure the right number of inputs have been provided
if(command_argument_count() < 7) then
    print*, 'ERROR: atleast 7 command-line arguments required, stopping'
    print*, 'format: ./binary save_file_name.npy min_x max_x min_y max_y x_res y_res'
    stop
endif

!! Done this way because length of the file name is unknown and why guess it to
!! less than some large length
call get_command_argument(1, length=i)  ! get length of first aurgument
allocate (character(i) :: npy_save_file_name)  ! allocate required length
call get_command_argument(1, npy_save_file_name)

!! Here variables like min_x are read into variables from input aurguments
!! It is done using an allocatable string with is allocated and deallocated
!! everytime an aurgument is read. In this case there is no need to worry about
!! size (number of characters) of input aurgument. It is not really necessary
!! though. A simpler way would be as follows
    !! call get_command_argument(4,tmp_str)
    !! read(tmp_str,*)min_y
!! then no need to make tmp_str as allocatable, just a size of 100 would be
!! enough like
    !! character(100) :: tmp_str
call get_command_argument(2, length=i)  ! get length of first aurgument
allocate (character(i) :: tmp_str)  ! allocate required length
call get_command_argument(2, tmp_str)
READ(tmp_str,*)min_x    ! read string as real number
deallocate(tmp_str)

call get_command_argument(3, length=i)  ! get length of first aurgument
allocate (character(i) :: tmp_str)  ! allocate required length
call get_command_argument(3, tmp_str)
READ(tmp_str,*)max_x    ! read string as real number
deallocate(tmp_str)

call get_command_argument(4, length=i)  ! get length of first aurgument
allocate (character(i) :: tmp_str)  ! allocate required length
call get_command_argument(4, tmp_str)
READ(tmp_str,*)min_y    ! read string as real number
deallocate(tmp_str)

call get_command_argument(5, length=i)  ! get length of first aurgument
allocate (character(i) :: tmp_str)  ! allocate required length
call get_command_argument(5, tmp_str)
READ(tmp_str,*)max_y    ! read string as real number
deallocate(tmp_str)

call get_command_argument(6, length=i)  ! get length of first aurgument
allocate (character(i) :: tmp_str)  ! allocate required length
call get_command_argument(6, tmp_str)
READ(tmp_str,*)x_res        ! read string as integer
deallocate(tmp_str)

call get_command_argument(7, length=i)  ! get length of first aurgument
allocate (character(i) :: tmp_str)  ! allocate required length
call get_command_argument(7, tmp_str)
READ(tmp_str,*)y_res        ! read string as integer
deallocate(tmp_str)

print*, 'limits in X-direction: ', min_x, max_x
print*, 'limits in Y-direction: ', min_y, max_y
print*, 'X and Y resolutions: ', x_res, y_res
print*, 'numpy .npy format save file name: ', npy_save_file_name

!!! allocate z to required size
allocate(z(y_res,x_res))

!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
!!                                 preperation
!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
z = 0
! c = 0
do concurrent (i=0:x_res-1)
    z(:,i+1) = z(:,i+1) + cmplx(min_x + i*(max_x-min_x)/(x_res-1),0)
    ! c(:,i+1) = c(:,i+1) + cmplx(min_x + i*(max_x-min_x)/(x_res-1),0)
end do
do concurrent (i=0:y_res-1)
    z(i+1,:) = z(i+1,:) + cmplx(0, max_y - i*(max_y-min_y)/(y_res-1))
    ! c(i+1,:) = c(i+1,:) + cmplx(0, max_y - i*(max_y-min_y)/(y_res-1))
end do

!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
!!                                 calculation
!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
do i=1,max_iter
    z = z**power + c
end do

!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
!!                                   saving
!!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!!
call save_npy(npy_save_file_name,log(abs(z)))  ! from m_npy module

!!! better deallocate it
deallocate(z)

end program julia_set_complex_polinomial
