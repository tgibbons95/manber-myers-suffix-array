// Test
#include "gtest/gtest.h"
#include "ManberMyersBuild.h"
#include <iostream>
#include <fstream>
#include <queue>

namespace CSE_584A
{
   namespace Testing
   {
      TEST(SuperMaximalTest, RepeatedCharacter)
      {
         std::queue<SuperMaximalMatchData> expectedResults;
         auto expectedResultsPtr = &expectedResults;

         auto output = [expectedResultsPtr](const SuperMaximalMatchData& data)
         {
            if (expectedResultsPtr->size() > 0)
            {
               auto expectedMatch = expectedResultsPtr->front();
               //EXPECT_EQ(expectedMatch.t, data.t) << "Position Failed";
               //EXPECT_EQ(expectedMatch.p, data.p) << "Pattern Failed";
               //EXPECT_EQ(expectedMatch.s, data.s) << "Compliment Failed";
               expectedResultsPtr->pop();
            }
            else
            {
               FAIL() << "Too many matches";
            }
         };

         std::string textFile = "inputT.txt";
         std::ofstream inputT(textFile);
         inputT << "CCCCC";
         inputT.close();

         SuperMaximal(textFile.c_str(), output);
         EXPECT_EQ(0, expectedResults.size()) << "All Results Not Found";
      }
   }
}
