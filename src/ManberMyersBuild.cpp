#include "ManberMyersBuild.h"

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <memory>

namespace CSE_584A
{
   void SuperMaximal(const char* textFilePath, std::function<void(const SuperMaximalMatchData&)> outputMethod)
   {
      // Open text file
      std::ifstream textFile(textFilePath);
      if (!textFile.is_open())
      {
         std::cout << "Cannot open text file";
         return;
      }

      
   }
}