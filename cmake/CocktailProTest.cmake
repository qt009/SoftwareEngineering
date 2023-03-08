# Add all test files including the file holding the test main function
add_executable(CocktailProTest
        ../src/test/RecipeBook_Test.cpp
        ../src/test/AvailableIngredients_Test.cpp
        ../src/test/RecipeStep_Test.cpp
        ../src/test/Shaker_Test.cpp
        ../src/test/Subject_Test.cpp
        ../src/test/Timer_Test.cpp
        ../src/test/Waage_Test.cpp
        ../src/test/Dispenser_Test.cpp ../src/test/DeviceVerwalter_Test.cpp ../src/test/Drainer_Test.cpp ../src/test/MixableRecipeBook_Test.cpp ../src/test/InternalDevice_Test.cpp ../src/test/Masher_Test.cpp ../src/test/Mixer_Test.cpp ../src/test/Recipe_Test.cpp ../src/test/BarTender_Test.cpp ../src/test/CocktailPro_Test.cpp ../src/test/UserStory1.cpp ../src/test/UserStory2.cpp ../src/test/UserStory3.cpp ../src/test/UserStory4.cpp ../src/test/UserStory5_test.cpp)

# Link CocktailProTest against CocktailProSource
linkCocktailProSource(CocktailProTest)

find_package(GTest)
if (GTEST_FOUND)
    # GTest is installed global
    target_link_libraries(CocktailProTest GTest::GTest GTest::Main)
else ()
    # GTest is not found. Download, build, and install it in the build directory
    set(GOOGLETEST_DIR ${CMAKE_BINARY_DIR}/googletest)
    externalproject_add(googletest
    #        URL https://github.com/google/googletest/archive/release-1.8.1.tar.gz
            URL https://github.com/google/googletest/archive/release-1.11.0.tar.gz
            PREFIX ${GOOGLETEST_DIR}
            CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${GOOGLETEST_DIR}
            -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
            -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
            -DBUILD_GMOCK=OFF)
    add_dependencies(CocktailProTest googletest)

    # Link CocktailProTest against the Library
    target_include_directories(CocktailProTest PUBLIC ${GOOGLETEST_DIR}/include)
    # Add ${CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX} as suffix to lib, in case the Operating system uses lib32 or lib64 as install directory
    target_link_directories(CocktailProTest PUBLIC ${GOOGLETEST_DIR}/lib64)
    target_link_directories(CocktailProTest PUBLIC ${GOOGLETEST_DIR}/lib)
    target_link_libraries(CocktailProTest gtest gtest_main pthread)
endif ()

# In case you wish to use CTest, testing is enabled and the tests were discovered
include(GoogleTest)
enable_testing()
gtest_discover_tests(CocktailProTest)

install(TARGETS CocktailProTest RUNTIME CONFIGURATIONS ${CMAKE_BUILD_TYPE})
