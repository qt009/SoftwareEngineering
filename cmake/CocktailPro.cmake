# Add only the file holding the main function
add_executable(CocktailPro ../src/main/Main.cpp)

# Adds a bunch of flags, enabling some compiler warnings
addCompilerWarningFlags(CocktailPro)
# Link CocktailPro against CocktailProSource
linkCocktailProSource(CocktailPro)

option(RUN_GTESTS "Runs the googletest before building and if at least one of them fails, the executable will not be build" OFF)
if (RUN_GTESTS)
    # Running the googletests before building CocktailPro, if at least one of them fails, the executable will not be build
    add_dependencies(CocktailPro CocktailProTest)
    add_custom_command(TARGET CocktailPro PRE_BUILD COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest)
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest/include)
endif ()

install(TARGETS CocktailPro RUNTIME CONFIGURATIONS ${CMAKE_BUILD_TYPE})
