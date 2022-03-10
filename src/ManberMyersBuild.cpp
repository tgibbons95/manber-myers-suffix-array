#include "ManberMyersBuild.h"

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <memory>
#include <algorithm>

namespace CSE_584A
{
   void ManberMyersBuild(const char* S, int* A, int* G, int n)
   {
      // Create initial, unsorted suffix array A from S
      for (int i = 0; i < n; ++i)
      {
         A[i] = i;
      }

      // Sort suffixes in A by first character only.
      auto compareFirstChar = [S](int lhs, int rhs){ return S[lhs] < S[rhs];};
      std::sort(A, A + n, compareFirstChar);

      // Assign group array to index of leftmost entry in A with same 1st char as A[i]
      std::queue<std::pair<int, int>> groupIntervals;
      int lastStart = 0;
      for (int i = 0; i < n; ++i)
      {
         G[A[i]] = static_cast<int>(std::lower_bound(A, A + n, A[i], compareFirstChar) - A);
         if (G[A[i]] != G[A[lastStart]])
         {
            if (i - lastStart > 1)
            {
               groupIntervals.emplace(lastStart, i - 1);
            }
            lastStart = i;
         }
      }
      if (G[A[n - 1]] == G[A[lastStart]] && n - lastStart > 1)
      {
         groupIntervals.emplace(lastStart, n - 1);
      }

      int h = 1;
      while (groupIntervals.size() > 0)
      {
         size_t numGroupIntervals = groupIntervals.size();

         // Iterate through groups
         for (size_t i = 0; i < numGroupIntervals; ++i)
         {
            // Get current interval
            auto groupInterval = groupIntervals.front();
            groupIntervals.pop();

            // Sort the interval
            auto compareGroup = [G, A, h](int lhs, int rhs) 
            { 
               return G[lhs + h] < G[rhs + h]; 
            };
            std::sort(A + groupInterval.first, A + groupInterval.second + 1, compareGroup);
            lastStart = groupInterval.first;
            for (size_t j = groupInterval.first; j <= groupInterval.second; ++j)
            {
               G[A[j]] = static_cast<int>(std::lower_bound(A + groupInterval.first, A + groupInterval.second + 1, A[j], compareGroup) - A);
               if (G[A[j]] != G[A[lastStart]])
               {
                  if (j - lastStart > 1)
                  {
                     groupIntervals.emplace(lastStart, static_cast<int>(j - 1));
                  }
                  lastStart = j;
               }
            }
            if (G[A[groupInterval.second]] == G[A[lastStart]] && groupInterval.second - lastStart > 0)
            {
               groupIntervals.emplace(lastStart, groupInterval.second);
            }
         }
         h <<= 1;
      }
   }

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
            while (i + h <= n && j + h <= n && S[i + h] == S[j + h])
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

   void FindSuperMaximalRepeats(const char* S, const int* A, const int* L, int n, std::function<void(const SuperMaximalMatchData&)> outputMethod)
   {
      
   }
}