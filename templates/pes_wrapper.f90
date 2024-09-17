! About:
! This is a template of the interface in Fortran 90 for the external PES shared
! library that is loaded by the PES C++ module. Just implement the respective
! routines from the external PES into the pes_startup(), pes_value(), and
! pes_shutdown() wrappers defined below. The startup and shutdown internals are
! optional and could be simply no-op calls. The PES value, as a double precision
! floating point number, must be returned in atomic units (Hartree) for a given
! set of internuclear distances, also in atomic units (Bohr).
!
! The order of internuclear distances in an array, say x, for atoms a, b and c:
! x(1) = b-c
! x(2) = c-a
! x(3) = a-b
!
! Building an example using GNU gfortran:
! gfortran -shared -fPIC templates/pes_wrapper.f90 -o pes_wrapper.so

subroutine pes_startup()
  implicit none

end subroutine

real(kind = 8) function pes_value(x)
  implicit none
  real(kind = 8), intent(in) :: x(3)

  pes_value = 0.0d0
end function

subroutine pes_shutdown()
  implicit none

end subroutine
