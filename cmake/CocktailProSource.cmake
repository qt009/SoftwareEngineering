# Add all main sources excluding the file holding the main function
add_library(CocktailProSource STATIC
        ../src/main/CocktailPro.cpp
        ../src/main/CocktailPro.h
        ../src/main/BarTender.cpp
        ../src/main/BarTender.h
        ../src/main/DeviceVerwalter.cpp
        ../src/main/DeviceVerwalter.h
        ../src/main/Dispenser.cpp
        ../src/main/Dispenser.h
        ../src/main/Drainer.cpp
        ../src/main/Drainer.h
        ../src/main/InternalDevice.cpp
        ../src/main/InternalDevice.h
        ../src/main/MixableRecipeBook.cpp
        ../src/main/MixableRecipeBook.h
        ../src/main/Mixer.cpp
        ../src/main/Mixer.h
        ../src/main/Observer.h
        ../src/main/Recipe.cpp
        ../src/main/Recipe.h
        ../src/main/RecipeBook.cpp
        ../src/main/RecipeBook.h
        ../src/main/RecipeStep.cpp
        ../src/main/RecipeStep.h
        ../src/main/Shaker.cpp
        ../src/main/Shaker.h
        ../src/main/Masher.cpp
        ../src/main/Masher.h
        ../src/main/Subject.cpp
        ../src/main/Subject.h
        ../src/main/Timer.cpp
        ../src/main/Timer.h
        ../src/main/AvailableIngredients.cpp
        ../src/main/AvailableIngredients.h
        ../src/main/Waage.cpp
        ../src/main/Waage.h
        )

# Adds a bunch of flags, enabling some compiler warnings
addCompilerWarningFlags(CocktailProSource)
# Link CocktailProSource against TinyXML2
# linkTinyXML2(CocktailProSource)

# Resources will be copied before building CocktailProSource
add_dependencies(CocktailProSource CocktailProResource)
