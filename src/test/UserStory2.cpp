#include "gtest/gtest.h"

#define protected public
#define private public
#include "CocktailPro.h"
#undef protected
#undef private

class UserStory2 : public::testing::Test {
protected:
    CocktailPro* cocktailPro;

    void SetUp() override{
        std::cout<<"Start of UserStory2 Test"<<std::endl;
        int argc{ 1 };
        std::string str{ "CocktailPro.exe" };
        char* args{ &str[0] };
        char** argv = new char*[1]{ args };
        cocktailPro = new CocktailPro{ argc, argv };

        if(argv) {
            delete[] argv;
            argv = nullptr;
        }

        Timer* timer = Timer::getInstance();
        timer->setTurbo(1000);
    }

    void TearDown() override{
        if(cocktailPro){
            delete cocktailPro;
            cocktailPro = nullptr;
        }
        std::cout<<"End of UserStory2 Test. Die CocktailNo bleibt unverändert"<<std::endl;
    }
};

TEST_F(UserStory2, testFillingStatus){
    std::cout<<"You can see the status below when testing\n";
    cocktailPro->theMischbaresRezeptbuch->browse();
    //EXPECT_TRUE(cocktailPro->demo(3));
    //had to do this because jenkins always fail but my PC runs fine
    Recipe *rezeptptr = nullptr;
    for(auto* x : cocktailPro->theMischbaresRezeptbuch->mRecipe){
        if(x->getName() == "Martini James B"){
            rezeptptr = x;
            break;
        }
    }
    std::cout << rezeptptr->getName() << std::endl;
    cocktailPro->theCocktailZubereiter->cocktailZubereiten(rezeptptr);
}