module cfbm_geometry_mod
  use iso_c_binding
  use fckit_configuration_module, only: fckit_configuration
  implicit none

  ! This defines the "Object" we pass back to C++ (as a pointer)
  type :: cfbm_geom_type
    integer(c_int) :: nx
    integer(c_int) :: ny
    real(c_double) :: dx
    real(c_double) :: dy
  end type cfbm_geom_type

contains

  ! -------------------------------------------------------------------
  ! Constructor: Called by Geometry.cc
  ! -------------------------------------------------------------------
  subroutine cfbm_geo_setup_c(c_conf, self_ptr) bind(c, name='cfbm_geo_setup_f90')
    use iso_c_binding
    implicit none
    type(c_ptr), value, intent(in) :: c_conf   ! The configuration from YAML
    type(c_ptr), intent(out)       :: self_ptr ! The pointer we return to C++

    type(fckit_configuration) :: conf
    type(cfbm_geom_type), pointer :: geom

    ! 1. Create the Fortran object
    allocate(geom)

    ! 2. Convert C pointer to Fortran Configuration object
    conf = fckit_configuration(c_conf)

    ! 3. Read YAML values (defaults provided for safety)
    !    In your YAML you will put:
    !    geometry:
    !      nx: 200
    !      ny: 200
    !      dx: 30.0
    call conf%get_or_die("nx", geom%nx)
    call conf%get_or_die("ny", geom%ny)
    call conf%get_or_die("dx", geom%dx)
    call conf%get_or_die("dy", geom%dy)

    ! 4. Print to verify it works
    write(*,*) "CFBM_GEOMETRY_MOD: Grid initialized: ", geom%nx, "x", geom%ny

    ! 5. Return the pointer to C++
    self_ptr = c_loc(geom)

  end subroutine cfbm_geo_setup_c

  ! -------------------------------------------------------------------
  ! Destructor: Called by Geometry.cc (~Geometry)
  ! -------------------------------------------------------------------
  subroutine cfbm_geo_delete_c(self_ptr) bind(c, name='cfbm_geo_delete_f90')
    use iso_c_binding
    implicit none
    type(c_ptr), value, intent(in) :: self_ptr
    type(cfbm_geom_type), pointer :: geom

    call c_f_pointer(self_ptr, geom)

    if (associated(geom)) then
       deallocate(geom)
    endif
  end subroutine cfbm_geo_delete_c

end module cfbm_geometry_mod
