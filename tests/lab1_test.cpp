#include <gtest/gtest.h>

#include <parent.hpp>

#include <memory>
#include <numeric>


struct BindTwoStrings
{
    std::string operator()(const std::string& s1, const std::string& s2) const {
        return s1.empty() ? s2 : s1 + "\n" + s2;
    }    
};

void TestParent(std::vector<std::string> input, std::vector<std::string> expectedOutput){

    std::stringstream inFile(std::accumulate(input.begin(), input.end(), std::string(""), BindTwoStrings()));

    std::string out = "";

    std::stringstream outFile(out);

    ParentProcess(getenv("PATH_TO_CHILD1"), getenv("PATH_TO_CHILD2"), inFile, outFile);

    for(std::string expectation : expectedOutput) {
        std::string result;
        std::getline(outFile, result);
        EXPECT_EQ(result, expectation);
    }
    
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
            " f 3 fkjh iu2 7 8e7 3e i g328 72e"
    };
    TestParent(input, expectedOutput);
}