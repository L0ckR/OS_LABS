#include <gtest/gtest.h>

#include <parent.hpp>

#include <memory>
#include <numeric>
#include <filesystem>

namespace fs = std::filesystem;

struct BindTwoStrings
{
    std::string operator()(const std::string & s1, const std::string & s2) const {
        return s1.empty() ? s2 : s1 + "\n" + s2;
    }    
};

void TestParent(std::vector<std::string> input, std::vector<std::string> expectedOutput){
    std::string strSum;
    std::stringstream inFile(std::accumulate(input.begin(), input.end(), strSum, BindTwoStrings()));

    std::stringstream outFile;

    
    if(fs::exists(getenv("PATH_TO_CHILD1")) & fs::exists(getenv("PATH_TO_CHILD2"))){

        ParentProcess(getenv("PATH_TO_CHILD1"), getenv("PATH_TO_CHILD2"), inFile, outFile);

        for(std::string expectation : expectedOutput) {
            std::string result;
            std::getline(outFile, result);
            EXPECT_EQ(result, expectation);
        }
    }else{
        std::cout << "ENV VAR NOT EXIST" << std::endl;
    }

    // не выдает segfault в тестирующей оболочке vscode, если просто скармливать пути
    // ParentProcess("../lab1/child1", "../lab1/child2", inFile, outFile);
    // for(std::string expectation : expectedOutput) {
    //     std::string result;
    //     std::getline(outFile, result);
    //     EXPECT_EQ(result, expectation);
    // }
}


TEST(FirstLabTests, EmptyTest) {
    std::vector<std::string> input = {
            ""
    };

    std::vector<std::string> expectedOutput = {
            ""
    };
    TestParent(input, expectedOutput);
}


TEST(FirstLabTests, SpacesTest) {
    std::vector<std::string> input = {
            "                ",
            "          ",
            "                "
    };

    std::vector<std::string> expectedOutput = {
            " ",
            " ",
            " "
    };
    TestParent(input, expectedOutput);
}

TEST(FirstLabTests, OneCharTest) {
    std::vector<std::string> input = {
            "                H",
            "      H    ",
            "h                "
    };

    std::vector<std::string> expectedOutput = {
            " h",
            " h ",
            "h "
    };
    TestParent(input, expectedOutput);
}



TEST(FirstLabTests, ComplexTest) {
    std::vector<std::string> input = {
            "ALLAH AKBAR    !!!!"                               ,
            "CAN U  F   EEL                 MY heArt   ??"      ,
            "SOmEboDy onCE    tOlD Me...   "                    ,
            "1337 )))   999  898re3  OOO ppp   OSIIII SOsiii"   ,
            "lab is dddone"                                     ,
            "lva OOPPPP"                                        ,
            " "                                                 ,
            ""                                                  ,
            "liue Hi uHIUHi h#IUD H"                            ,
            "lkH WDWi gwd "                                     
    };

    std::vector<std::string> expectedOutput = {
            "allah akbar !!!!"                                  ,
            "can u f eel my heart ??"                           ,
            "somebody once told me... "                         ,
            "1337 ))) 999 898re3 ooo ppp osiiii sosiii"         ,
            "lab is dddone"                                     ,
            "lva oopppp"                                        ,
            " "                                                 ,
            ""                                                  , 
            "liue hi uhiuhi h#iud h"                            ,
            "lkh wdwi gwd "                                     
    };
    TestParent(input, expectedOutput);
}

int main(int argc, char **argv) {
    // std::cout << getenv("PATH_TO_CHILD1") << std::endl;
    // std::cout << getenv("PATH_TO_CHILD2") << std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
