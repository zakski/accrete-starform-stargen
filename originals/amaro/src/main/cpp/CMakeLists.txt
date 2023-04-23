project(stargen)

cmake_minimum_required(VERSION 2.8)

enable_language(Fortran)

find_library(M_LIB m)

add_executable(stargen main.c stargen.c accrete.c display.c Dumas.c enviro.c utils.c ring_universe.c ic3094.c ba_gal.c omega_galaxy.c)

add_executable(moon_orbits moon_orbits.f)

set_target_properties(stargen PROPERTIES COMPILE_FLAGS "-D_USE_LIBM_MATH_H")

target_link_libraries(stargen ${M_LIB})

install(TARGETS stargen moon_orbits RUNTIME DESTINATION bin)
# install(TARGETS moon_orbits RUNTIME DESTINATION bin)