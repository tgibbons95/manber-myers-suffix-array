/*****************************************************************//**
 * @file   AdjacentLcp.cpp
 * @brief  Provides method implementations related to the adjacent LCP array of a string
 *
 * @author Thomas Gibbons
 * @date   Mar 2022
 *********************************************************************/

#include "AdjacentLcp.h"

namespace CSE_584A
{
   void ComputeAdjacentLcp(const char* S, const int* A, const int* G, int* L, int n)
   {
      int h = 0;
      for (int i = 0; i < n; ++i)
      {
         int k = G[i];
         if (k == 0)
         {
            L[k] = 0;
         }
         else
         {
            int j = A[k - 1];
            while (i + h < n && j + h < n && S[i + h] == S[j + h])
            {
               h++;
            }
            L[k] = h;
         }
         if (h > 0)
         {
            h--;
         }
      }
   }
}