/*****************************************************************//**
 * @file   SuperMaximal.cpp
 * @brief  Provides method implementations related to finding the super maximal repeats of a string
 *
 * @author Thomas Gibbons
 * @date   Mar 2022
 *********************************************************************/

#include "SuperMaximal.h"

#include <algorithm>
#include <list>
#include <stack>

namespace CSE_584A
{
   /**
   * \brief Represents a node in a suffix tree.
   *
   * This class stores the left and right most descendants of the suffix tree
   * as indexes into the suffix array. It stores the depth at which the node is from the root.
   * It also stores information on whether it is a right super maximal node.
   */
   struct SuffixTreeNode
   {
      int l = 0; /*!< The index into the suffix array of the leftmost descendant of the node. */
      int r = 0; /*!< The index into the suffix array of the rightmost descendant of the node. */
      int d = 0; /*!< The depth into the suffix array of the node from the root. */
      bool rightSuperMaximal = true; /*!< Whether the node represents a right super maximal instance. */
      SuffixTreeNode() {}
      SuffixTreeNode(int l, int r, int d) : l(l), r(r), d(d) {}
   };

   void PostOrderTraversalSuffixTree(const char* S, const int* A, const int* L, int n, std::function<void(const SuffixTreeNode&)> visitMethod)
   {
      std::stack<SuffixTreeNode> nodes;

      // Add root node
         // Leftmost point is beginning index of suffix array.
         // Rightmost point is known but will be filled out at end regardless.
         // Depth is 0 for root node.
      nodes.emplace(0, -1, 0);

      for (int i = 0; i < n; ++i)
      {
         // If the next LCP array value is less than the current stack's depth, 
         // it is now safe to visit that node because we are currently at it's 
         // right end point. Or if we are at the last character in the array, 
         // we are at the right end point of every node left on the stack
         if (i == n - 1 || L[i + 1] < nodes.top().d)
         {
            do
            {
               // Update the rightmost pointer
               nodes.top().r = i;

               // Visit the node
               visitMethod(nodes.top());

               // Remove node from stack
               nodes.pop();

               if (nodes.size() > 0)
               {
                  nodes.top().rightSuperMaximal = false;
               }
            } while (nodes.size() > 0 && (i == n - 1 || L[i + 1] < nodes.top().d));

            if (i < n - 1 && L[i + 1] > nodes.top().d)
            {
               // Add new node on top of stack
                  // Leftmost point is top node's left index
                  // Rightmost point is unknown.
                  // Depth is next LCP value
               nodes.emplace(nodes.top().l, -1, L[i + 1]);
            }
         }
         else if (L[i + 1] > nodes.top().d)
         {
            // Add new node on top of stack
               // Leftmost point is current spot in suffix array.
               // Rightmost point is unknown.
               // Depth is next LCP value
            nodes.emplace(i, -1, L[i + 1]);
         }
         else
         {
            // Gracefully ignore multiple paths from a single node.
            // Example S = "ABACAD", Leaf "ACAD" has the same LCP as 
            // AD because they share a node with "ABACAD"
         }
      }
   }

   void ComputeSuperMaximalRepeats(const char* S, const int* A, const int* L, int n, int k, std::function<void(const SuperMaximalMatchData&)> outputMethod)
   {
      auto visitFunc = [S,A,k,outputMethod](const SuffixTreeNode& node)
      {
         // Check if the node is right supermaximal of length at least k
         if (node.rightSuperMaximal && node.d >= k)
         {
            // Check if the node is left supermaximal
            std::list<char> pretextCharList; 
            bool superMaximal = true;
            for (int i = node.l; i <= node.r; ++i)
            {
               if (A[i] != 0)
               {
                  auto it = std::find(pretextCharList.begin(), pretextCharList.end(), S[A[i] - 1]);
                  if (it != pretextCharList.end())
                  {
                     superMaximal = false;
                     break;
                  }
                  else
                  {
                     pretextCharList.emplace_back(S[A[i] - 1]);
                  }
               }
            }

            // If supermaximal, output the match
            if (superMaximal)
            {
               SuperMaximalMatchData match(&S[A[node.l]], node.d);
               for (int i = node.l; i <= node.r; ++i)
               {
                  match.instances.emplace_back(A[i]);
               }
               std::sort(match.instances.begin(), match.instances.end());
               outputMethod(match);
            }
         }
      };
      PostOrderTraversalSuffixTree(S,A,L,n, visitFunc);
   }
}