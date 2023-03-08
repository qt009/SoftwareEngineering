find_package(Doxygen)
if (DOXYGEN_FOUND)
    # Doxygen is installed and a target will be available to generate Doxygen files
    get_target_property(COCKTAIL_PRO_SOURCES CocktailProSource SOURCES)
    doxygen_add_docs(CocktailProDoxygen ${COCKTAIL_PRO_SOURCES} COMMENT "Generating API documentation with Doxygen" WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
endif (DOXYGEN_FOUND)
