#include "BurrowsWheelerTransform.h"

namespace CSE_584A
{
   void ComputeBurrowsWheelerTransform(const char* S, const int* A, char* B, int n)
   {
      for (int i = 0; i < n; ++i)
      {
         B[i] = (A[i] == 0) ? S[n - 1] : S[A[i] - 1];
      }
   }
}