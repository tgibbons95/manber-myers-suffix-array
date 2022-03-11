#ifndef SUPER_MAXIMAL_H
#define SUPER_MAXIMAL_H

#include <functional>
#include <vector>

namespace CSE_584A
{
   struct SuperMaximalMatchData
   {
      const char* repeat = nullptr;
      int length = 0;
      std::vector<int> instances;
      SuperMaximalMatchData() = default;
      SuperMaximalMatchData(const char* repeat, int length) : repeat(repeat), length(length) {}
   };

   void ComputeSuperMaximalRepeats(const char* S, const int* A, const int* L, int n, int k, std::function<void(const SuperMaximalMatchData&)> outputMethod);
}

#endif