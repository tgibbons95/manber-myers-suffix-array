/*****************************************************************//**
 * @file   SuperMaximal.h
 * @brief  Provides method declarations related to finding the super maximal repeats of a string
 *
 * @author Thomas Gibbons
 * @date   Mar 2022
 *********************************************************************/

#ifndef SUPER_MAXIMAL_H
#define SUPER_MAXIMAL_H

#include <functional>
#include <vector>

namespace CSE_584A
{
   /**
   * \brief Represents a super maximal repeat within a text.
   *
   * This class keeps track of the a super maximal repeat found with a string.
   * It stores the repeat string and each of the positions at which that string
   * is found within the text.
   */
   struct SuperMaximalMatchData
   {
      const char* repeat = nullptr; /*!< A pointer to the beginning of the repeat string. No terminating character. */
      int length = 0; /*!< The length of the repeat string. */
      std::vector<int> instances; /*!< A vector of all the starting positions within the string that repeat occurs. 0 indexed. */
      SuperMaximalMatchData() = default;
      SuperMaximalMatchData(const char* repeat, int length) : repeat(repeat), length(length) {}
   };

   /**
   * \brief Finds all super maximal repeats within string S.
   *
   * Finds all super maximal repeats using the suffix array and adjacent LCP array of a string.
   * It utilizes a post order traversal of a simulated suffix tree to find all matches within
   * linear time.
   *
   * \param S The string on which to find the super maximal repeats.
   * \param A The precomputed suffix array of string S.
   * \param L The precomputed adjacent LCP array of string S.
   * \param n The length of string S, suffix array A, and adjacent LCP L.
   * \param k The minimum length of super maximal repeats to consider.
   * \param outputMethod A callback function to output any repeats that are found as they are found.
   */
   void ComputeSuperMaximalRepeats(const char* S, const int* A, const int* L, int n, int k, std::function<void(const SuperMaximalMatchData&)> outputMethod);
}

#endif