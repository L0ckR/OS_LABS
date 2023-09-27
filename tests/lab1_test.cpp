#include <gtest/gtest.h>

#include <parent.hpp>

#include <filesystem>
#include <fstream>
#include <memory>

namespace fs = std::filesystem;


TEST(FirstLabTests, SimpleTest) {
    std::string fileWithInput = "input.txt";
    std::string fileWithOutput = "output.txt";

    std::vector<std::string> input = {
            "ALLAH AKBAR    !!!!",
            "CAN U  F   EEL                 MY heArt   ??",
            "SOmEboDy onCE    tOlD Me...   ",
            "1337 )))   999  898re3  OOO ppp   OSIIII SOsiii",
            "lab is dddone",
            "lva OOPPPP",
            " ",
            "",
            "liue Hi uHIUHi h#IUD H",
            "lkH WDWi gwd ",
            "brgtrfsfs a J wfe f a WHWDu 3d3d  ",
            " ef ef se rf3 ra d",
            " f 3  fkjh iu2 7      8e7 3e i g328 72E"
    };

    std::vector<std::string> expectedOutput = {
            "allah akbar !!!!",
            "can u f eel my heart ??",
            "somebody once told me... ",
            "1337 ))) 999 898re3 ooo ppp osiiii sosiii",
            "lab is dddone",
            "lva oopppp",
            " ",
            "",
            "liue hi uhiuhi h#iud h",
            "lkh wdwi gwd ",
            "brgtrfsfs a j wfe f a whwdu 3d3d ",
            " ef ef se rf3 ra d",
            " f 3 fkjh iu2 7 8e7 3e i g328 72e",
    };

    auto toInputFile = std::ofstream(fileWithInput);

    for(std::string line : input) {
        toInputFile << line + '\n';
    }
    toInputFile.close();


    std::ifstream inFile;
    inFile.open(fileWithInput);

    auto outFile = std::ofstream(fileWithOutput);



    parentProcess("../lab1/child", inFile, outFile);


    ASSERT_TRUE(outFile.good());

    inFile.close();
    outFile.close();
    
    auto fromOutFile = std::ifstream(fileWithOutput);

    std::string result;

    for(std::string expectation : expectedOutput) {
        std::getline(fromOutFile, result);
        EXPECT_EQ(result, expectation);
    }
    fromOutFile.close();

    auto removeIfExists = [](std::string path) {
        if(fs::exists(path)) {
            fs::remove(path);
        }
    };

    removeIfExists(fileWithInput);
    removeIfExists(fileWithOutput);
}