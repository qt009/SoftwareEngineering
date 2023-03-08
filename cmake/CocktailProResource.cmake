add_custom_target(CocktailProResource SOURCES ../src/resources/zutaten.txt)

# Resolving absolute (real) paths to prevent misleading relative paths
get_target_property(COCKTAIL_PRO_RESOURCES CocktailProResource SOURCES)
foreach (resource ${COCKTAIL_PRO_RESOURCES})
    get_filename_component(resourceAbsolute ${CMAKE_CURRENT_LIST_DIR}/${resource} REALPATH)
    list(APPEND COCKTAIL_PRO_RESOURCES_ABSOLUTE ${resourceAbsolute})
endforeach ()

# Copying needed resources to the binary directory
add_custom_command(TARGET CocktailProResource COMMAND cp ${COCKTAIL_PRO_RESOURCES_ABSOLUTE} ${CMAKE_BINARY_DIR})

install(FILES ${COCKTAIL_PRO_RESOURCES_ABSOLUTE} TYPE BIN)
