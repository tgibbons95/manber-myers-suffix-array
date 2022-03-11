// Test
#include "gtest/gtest.h"

#include "AdjacentLcp.h"
#include "BurrowsWheelerTransform.h"
#include "SuffixArray.h"
#include "SuperMaximal.h"

#include <iostream>
#include <fstream>
#include <new>
#include <queue>

#define SAFE_DELETE_ARRAY(x) if(x) { delete[] x; x = nullptr; }

namespace CSE_584A
{
   namespace Testing
   {
      void AppendReverseComplement(std::string& S)
      {
         S.push_back('&');
         for (int i = S.size() - 2; i >= 0; --i)
         {
            char c = 'a';
            switch (S[i])
            {
            case 'a':
            case 'A':
               c = S[i] - 'a' + 't';
               break;
            case 'c':
            case 'C':
               c = S[i] - 'c' + 'g';
               break;
            case 'g':
            case 'G':
               c = S[i] - 'g' + 'c';
               break;
            case 't':
            case 'T':
            default:
               c = S[i] - 't' + 'a';
               break;
            }
            S.push_back(c);
         }
         S.push_back('$');
      }

      TEST(Assignment, AppendReverseComplement)
      {
         const int n = 32;
         char S[n + 1] = "acgtcacgtgacgtc&gacgtcacgtgacgt$";
         std::string str = "acgtcacgtgacgtc";
         AppendReverseComplement(str);
         EXPECT_STREQ(S, str.c_str());
      }

      TEST(Assignment, Example)
      {
         const int n = 32;
         char S[n + 1] = "acgtcacgtgacgtc&gacgtcacgtgacgt$";
         int A[n] = {};
         int G[n] = {};
         int L[n] = {};
         char B[n] = {};

         std::queue<std::string> expectedResults;
         expectedResults.emplace("acgtcacgtgacgt 1 1 2 1");
         expectedResults.emplace("gacgtc 1 10 2 10");

         auto output = [n, &expectedResults](const SuperMaximalMatchData& match)
         {
            int halfN = (n - 1) / 2;
            if (expectedResults.size() > 0)
            {
               auto expectedMatchStr = expectedResults.front();
               std::string matchStr(match.repeat, match.length);
               for (auto& occurrence : match.instances)
               {
                  matchStr.push_back(' ');
                  matchStr.append(std::to_string((occurrence > halfN ? 2 : 1)));
                  matchStr.push_back(' ');
                  matchStr.append(std::to_string(occurrence > halfN ? n - (occurrence + match.length) : occurrence + 1));
               }
               EXPECT_EQ(expectedMatchStr, matchStr) << "Mismatch in match";
               expectedResults.pop();
            }
            else
            {
               FAIL() << "Too many matches";
            }
         };

         ComputeSuffixArray(S, A, G, n);
         ComputeAdjacentLcp(S, A, G, L, n);
         ComputeBurrowsWheelerTransform(S, A, B, n);
         ComputeSuperMaximalRepeats(S, A, L, n, 6, output);
      }

      TEST(Assignment, HumanSeq)
      {
         std::ifstream humanSeq("human-seq.txt");
         if (humanSeq.is_open())
         {
            std::string S;
            S.reserve(100000256);
            std::getline(humanSeq, S);
            
            // We will append the reverse complement of the DNA strand to the string.
            // This is supplemental to the algorithm and any indexes between strands
            // will be computed when examining matches.
            AppendReverseComplement(S);
            int n = S.size();

            // Save off matches.
            std::vector<SuperMaximalMatchData> matches;
            auto output = [&matches](const SuperMaximalMatchData& match)
            {
               matches.emplace_back(match);
            };

            int* A = new (std::nothrow) int[n];
            int* G = new (std::nothrow) int[n];
            int* L = new (std::nothrow) int[n];

            if (A && G && L)
            {
               std::cout << "Started Computing Suffix Array" << std::endl;
               ComputeSuffixArray(S.c_str(), A, G, n);
               std::cout << "Finished Computing Suffix Array" << std::endl;

               std::cout << "Started Computing Adjacent Lcp" << std::endl;
               ComputeAdjacentLcp(S.c_str(), A, G, L, n);
               std::cout << "Finished Computing Adjacent Lcp" << std::endl;
            }
            else
            {
               // Delete any arrays that were allocated.
               SAFE_DELETE_ARRAY(A);
               SAFE_DELETE_ARRAY(G);
               SAFE_DELETE_ARRAY(L);
               ASSERT_FALSE(true);
            }

            SAFE_DELETE_ARRAY(G);

            char* B = new (std::nothrow) char[n];
            if (B)
            {
               std::cout << "Started Computing BWT" << std::endl;
               ComputeBurrowsWheelerTransform(S.c_str(), A, B, n);
               std::cout << "Finished Computing BWT" << std::endl;

               // Output BWT Results
               std::ofstream bwtOutput("BurrowsWheelerTransformOutput.txt");

               for (int i = 0; i < n; ++i)
               {
                  if (B[i] == '$')
                  {
                     bwtOutput << "$ at: " << i + 1 << std::endl;;
                  }
               }

               bwtOutput << "First 50 chars of BWT: ";
               bwtOutput.write(B, 50);
               bwtOutput << std::endl;
               
               bwtOutput << "Last 50 chars of BWT: ";
               bwtOutput.write(B + n - 50, 50);
               bwtOutput << std::endl;
            }
            SAFE_DELETE_ARRAY(B);

            std::cout << "Started Computing Super Maximal Repeats" << std::endl;
            ComputeSuperMaximalRepeats(S.c_str(), A, L, n, 1000, output);
            std::cout << "Finished Computing Super Maximal Repeats" << std::endl;

            SAFE_DELETE_ARRAY(A);
            SAFE_DELETE_ARRAY(L);

            // Sort lexicographically by repeat (algorithm already sorted instances by position)
            auto compare = [](const SuperMaximalMatchData& lhs, const SuperMaximalMatchData& rhs)
            {
               int length = std::min(lhs.length, rhs.length);
               int cmp = strncmp(lhs.repeat, rhs.repeat, length);
               return cmp < 0 || (cmp == 0 && lhs.length < rhs.length);
            };
            std::sort(matches.begin(), matches.end(), compare);

            // Output matches to file
            std::ofstream superMaximalOutput("SuperMaximalMatches.txt");
            int halfN = (n - 1) / 2;
            for (const auto& match : matches)
            {
               superMaximalOutput.write(match.repeat, match.length);
               for (auto& occurrence : match.instances)
               {
                  // If the occurence is on the right side of the string, then it is part of the complement.
                  // Compute location of where the reverse complement's smallest index in the forward strand is.
                  superMaximalOutput << " " << (occurrence > halfN ? 2 : 1) << " " << (occurrence > halfN ? n - (occurrence + match.length) : occurrence + 1);
               }
               superMaximalOutput << std::endl;
            }
            superMaximalOutput.close();
         }
         else
         {
            std::cout << "Did not run on human-seq.txt" << std::endl;
         }
      }
   }
}
