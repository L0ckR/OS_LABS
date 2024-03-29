#include <gtest/gtest.h>

#include <parent.hpp>

#include <memory>
#include <numeric>
#include <filesystem>

namespace fs = std::filesystem;

void TestParent(const std::vector<std::string> & input, const std::vector<std::string> & expectedOutput){
    std::string strSum;
    std::stringstream inFile(std::accumulate(input.begin(), input.end(), strSum,[&](const std::string & s1, const std::string & s2){
                                                                                    return s1.empty() ? s2 : s1 + "\n" + s2;
                                                                                }));

    std::stringstream outFile;

    if (getenv("PATH_TO_CHILD1") != NULL && getenv("PATH_TO_CHILD2") != NULL){
        if(fs::exists(getenv("PATH_TO_CHILD1")) && fs::exists(getenv("PATH_TO_CHILD2"))){

            ParentProcess(getenv("PATH_TO_CHILD1"), getenv("PATH_TO_CHILD2"), inFile, outFile);

            for(const std::string & expectation : expectedOutput) {
                std::string result;
                std::getline(outFile, result);
                EXPECT_EQ(result, expectation);
            }
        }else{
            std::cout << "PATH DOES NOT EXIST" << std::endl;
        }
    }else{
        std::cout << "ENV VAR DOES NOT EXIST" << std::endl;
    }
}


TEST(FirstLabTests, EmptyTest) {
    const std::vector<std::string> input = {
            ""
    };

    const std::vector<std::string> expectedOutput = {
            ""
    };
    TestParent(input, expectedOutput);
}


TEST(FirstLabTests, SpacesTest) {
    const std::vector<std::string> input = {
            "                ",
            "          ",
            "                "
    };

    const std::vector<std::string> expectedOutput = {
            " ",
            " ",
            " "
    };
    TestParent(input, expectedOutput);
}

TEST(FirstLabTests, OneCharTest) {
    const std::vector<std::string> input = {
            "                H",
            "      H    ",
            "h                "
    };

    const std::vector<std::string> expectedOutput = {
            " h",
            " h ",
            "h "
    };
    TestParent(input, expectedOutput);
}



TEST(FirstLabTests, ComplexTest) {
    const std::vector<std::string> input = {
            "ALLAH AKBAR    !!!!"                               ,
            "CAN U  F   EEL                 MY heArt   ??"      ,
            "SOmEboDy onCE    tOlD Me...   "                    ,
            "1337 )))   999  898re3  OOO ppp   OSIIII SOsiii"   ,
            "lab is dddone"                                     ,
            "lva OOPPPP"                                        ,
            " "                                                 ,
            ""                                                  ,
            "liue Hi uHIUHi h#IUD H"                            ,
            "lkH WDWi gwd "                                     ,     
            "yyyyyy yyyy"                                       ,  
            "yyyyyy yyyy"                                       ,   
            "yyyyyy yyyy"                                       ,   
            "yyyyyy yyyy"                                       ,   
            "yyyyyy yyyy"                                       ,                        
    };

    const std::vector<std::string> expectedOutput = {
            "allah akbar !!!!"                                  ,
            "can u f eel my heart ??"                           ,
            "somebody once told me... "                         ,
            "1337 ))) 999 898re3 ooo ppp osiiii sosiii"         ,
            "lab is dddone"                                     ,
            "lva oopppp"                                        ,
            " "                                                 ,
            ""                                                  , 
            "liue hi uhiuhi h#iud h"                            ,
            "lkh wdwi gwd "                                     ,
            "yyyyyy yyyy"                                       ,  
            "yyyyyy yyyy"                                       ,   
            "yyyyyy yyyy"                                       ,   
            "yyyyyy yyyy"                                       ,   
            "yyyyyy yyyy"                                       , 
    };
    TestParent(input, expectedOutput);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
