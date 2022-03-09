#include <functional>

namespace CSE_584A
{
   struct SuperMaximalInstance
   {
      int t = 0; // Position in text that matches. Starts at 1.
      int s = 0; // Forward or reverse complement
   };

   struct SuperMaximalMatchData
   {
      char* repeat = nullptr;
      int length = 0;
      std::vector<SuperMaximalInstance> instances;
      SuperMaximalMatchData() = default;
      SuperMaximalMatchData(char* repeat, int length) : repeat(repeat), length(length) {}
   };

   void SuperMaximal(const char* textFile, std::function<void(const SuperMaximalMatchData&)> outputMethod);

}