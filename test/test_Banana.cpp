// Test
#include "gtest/gtest.h"

#include "AdjacentLcp.h"
#include "BurrowsWheelerTransform.h"
#include "SuffixArray.h"
#include "SuperMaximal.h"

#include <queue>

namespace CSE_584A
{
   namespace Testing
   {
      TEST(SuffixArrayTest, Banana)
      {
         const int n = 7;
         char S[n + 1] = "BANANA$";
         int A[n] = {};
         int G[n] = {};
         int expectedA[n] = { 6,5,3,1,0,4,2 };
         int expectedG[n] = { 4,3,6,2,5,1,0 };

         ComputeSuffixArray(S, A, G, n);

         for (int i = 0; i < n; ++i)
         {
            EXPECT_EQ(expectedA[i], A[i]);
            EXPECT_EQ(expectedG[i], G[i]);
         }
      }

      TEST(AdjacentLcpTest, Banana)
      {
         const int n = 7;
         char S[n + 1] = "BANANA$";
         int A[n] = { 6,5,3,1,0,4,2 };
         int G[n] = { 4,3,6,2,5,1,0 };
         int L[n] = {};
         int expectedL[n] = { 0,0,1,3,0,0,2 };

         ComputeAdjacentLcp(S, A, G, L, n);

         for (int i = 0; i < n; ++i)
         {
            EXPECT_EQ(expectedL[i], L[i]);
         }
      }

      TEST(BurrowsWheelerTransformTest, Banana)
      {
         const int n = 7;
         char S[n + 1] = "BANANA$";
         char B[n + 1] = {};
         int A[n] = { 6,5,3,1,0,4,2 };
         char expectedB[n + 1] = "ANNB$AA";

         ComputeBurrowsWheelerTransform(S, A, B, n);

         for (int i = 0; i < n; ++i)
         {
            EXPECT_EQ(expectedB[i], B[i]);
         }
      }

      TEST(SuperMaximalRepeatsTest, Banana)
      {
         const int n = 7;
         char S[n + 1] = "BANANA$";
         int A[n] = { 6,5,3,1,0,4,2 };
         int L[n] = { 0,0,1,3,0,0,2 };

         std::queue<SuperMaximalMatchData> expectedResults;
         expectedResults.emplace("ANA", 3);
         expectedResults.back().instances.emplace_back(1);
         expectedResults.back().instances.emplace_back(3);

         auto output = [&expectedResults](const SuperMaximalMatchData& match)
         {
            if (expectedResults.size() > 0)
            {
               auto expectedMatch = expectedResults.front();
               EXPECT_TRUE(memcmp(expectedMatch.repeat, match.repeat, 3) == 0) << "Repeat Failed";
               EXPECT_EQ(expectedMatch.instances.size(), match.instances.size()) << "Number of instances failed";
               if (expectedMatch.instances.size() == match.instances.size())
               {
                  for (size_t i = 0; i < expectedMatch.instances.size(); ++i)
                  {
                     EXPECT_EQ(expectedMatch.instances[i], match.instances[i]) << "Instance " << i << " Failed";
                  }
               }
               expectedResults.pop();
            }
            else
            {
               FAIL() << "Too many matches";
            }
         };
         ComputeSuperMaximalRepeats(S, A, L, n, 0, output);
      }
   }
}
