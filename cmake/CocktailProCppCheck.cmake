find_program(CPPCHECK_EXECUTABLE cppcheck)
if (NOT CPPCHECK_EXECUTABLE MATCHES "NOTFOUND")
    # CppCheck is found and a target will be available to run CppCheck
    get_target_property(COCKTAIL_PRO_SOURCE_SOURCES CocktailProSource SOURCES)
    get_target_property(COCKTAIL_PRO_SOURCES CocktailPro SOURCES)
    list(APPEND COCKTAIL_PRO_SOURCES ${COCKTAIL_PRO_SOURCE_SOURCES})
    add_custom_target(CocktailProCppCheck
            ${CPPCHECK_EXECUTABLE} --suppress=missingIncludeSystem --xml --xml-version=2 --enable=all --language=c++ --std=c++11 --quiet ${COCKTAIL_PRO_SOURCES}
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
endif ()
