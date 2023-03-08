# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/googletest/src/googletest"
  "/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/googletest/src/googletest-build"
  "/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/googletest"
  "/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/googletest/tmp"
  "/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/googletest/src/googletest-stamp"
  "/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/googletest/src"
  "/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/googletest/src/googletest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/cygdrive/c/Users/PC/OneDrive - stud.h-da.de/PRAKTIKUM/Software Engineering/CocktailPro/cmake-build-debug-cygwin/googletest/src/googletest-stamp/${subDir}")
endforeach()
