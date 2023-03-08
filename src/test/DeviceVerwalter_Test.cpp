#include "gtest/gtest.h"

#define protected public
#define private public
#include "DeviceVerwalter.h"
#undef protected
#undef private

class DeviceVerwalterTest: public::testing::Test{
protected:
    DeviceVerwalter* deviceVerwalter;
    AvailableIngredients* availableIngredients;

    void SetUp() {
        std::cout<<"Start of DeviceVerwalterTest"<<std::endl;
        availableIngredients=new AvailableIngredients();
        deviceVerwalter=new DeviceVerwalter(availableIngredients);
    }

    void TearDown() {
        delete deviceVerwalter;
        deviceVerwalter= nullptr;
        std::cout<<"End of DeviceVerwalterTest"<<std::endl;
    }
};

TEST_F(DeviceVerwalterTest, setZutatenVerwalter){
    AvailableIngredients* test_AI=(new AvailableIngredients());
    deviceVerwalter->setZutatenVerwalter(test_AI);

    EXPECT_EQ(test_AI, deviceVerwalter->myZutatenVerwalter);
}

TEST_F(DeviceVerwalterTest, rezeptSchrittVorbereiten ){
    deviceVerwalter->createDevices();
    float menge = 30;

    for(const auto& it: *deviceVerwalter->myDevices){
        std::string zutat= it.first;
        std::cout<<"ZUTAT: "<<zutat<<std::endl;
        if(zutat == "Limettenstuecke"){
            auto theDispenser = reinterpret_cast<Dispenser*>(deviceVerwalter->myDevices->at(zutat));
            theDispenser->zeiteinheit = 1;
            int stckProZeit = theDispenser->getStueckProZeit();
            std::cout<<"STCK/ZEIT = "<<stckProZeit<<std::endl;
            deviceVerwalter->myDevices->at(zutat)->doIt(menge * stckProZeit);
            EXPECT_EQ(menge * stckProZeit, theDispenser->myWaage->getDelta());
        }
        else{
            deviceVerwalter->myDevices->at(zutat)->zeiteinheit = 1;
            if(typeid(*(deviceVerwalter->myDevices->at(zutat))) == typeid(Dispenser)){
                deviceVerwalter->myDevices->at(zutat)->doIt(menge);
                if(zutat == "Eis") {
                    if (static_cast<int>(menge) % static_cast<int>(deviceVerwalter->theWaage->getDelta()) == 0) {
                        EXPECT_EQ(menge, deviceVerwalter->theWaage->getDelta());
                    } else EXPECT_NE(menge, deviceVerwalter->theWaage->getDelta());
                }
                else {
                    EXPECT_EQ(menge, deviceVerwalter->theWaage->getDelta());
                }
            }
            else if (typeid(*(deviceVerwalter->myDevices->at(zutat))) == typeid(Drainer)){
                deviceVerwalter->myDevices->at(zutat)->doIt(menge);
                EXPECT_GE(menge, deviceVerwalter->theWaage->getWeight());
            }

        }

    }
}


TEST_F(DeviceVerwalterTest, createDevices){
    deviceVerwalter->createDevices();

    EXPECT_EQ(deviceVerwalter->myEntleerer, deviceVerwalter->myDevices->at("Entleeren"));
    EXPECT_EQ(deviceVerwalter->mySchuettler, deviceVerwalter->myDevices->at("Schuetteln"));
    EXPECT_EQ(deviceVerwalter->myStampfer, deviceVerwalter->myDevices->at("Stampfen"));
    EXPECT_EQ(deviceVerwalter->myMixer, deviceVerwalter->myDevices->at("Mischen"));
}