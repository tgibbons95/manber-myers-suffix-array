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
      TEST(ManberMyersBuildTest, Banana)
      {
         const int n = 7;
         char S[n + 1] = "BANANA$";
         int A[n] = {};
         int G[n] = {};
         int expectedA[n] = { 6,5,3,1,0,4,2 };
         int expectedG[n] = { 4,3,6,2,5,1,0 };

         ManberMyersBuild(S, A, G, n);

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
         int A[n] = {};
         int G[n] = {};
         int L[n] = {};
         int expectedL[n] = { 0,0,1,3,0,0,2 };

         ManberMyersBuild(S, A, G, n);
         ComputeAdjacentLcp(S, A, G, L, n);

         for (int i = 0; i < n; ++i)
         {
            EXPECT_EQ(expectedL[i], L[i]);
         }
      }
   }
}
