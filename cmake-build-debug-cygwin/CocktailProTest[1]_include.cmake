if(EXISTS "/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/CocktailProTest[1]_tests.cmake")
  include("/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/CocktailProTest[1]_tests.cmake")
else()
  add_test(CocktailProTest_NOT_BUILT CocktailProTest_NOT_BUILT)
endif()
