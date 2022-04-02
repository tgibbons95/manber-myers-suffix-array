/*****************************************************************//**
 * @file   BurrowsWheelerTransform.h
 * @brief  Provides method declarations related to the Burrows-Wheeler transform of a string
 *
 * @author Thomas Gibbons
 * @date   Mar 2022
 *********************************************************************/

#ifndef BURROWS_WHEELER_H
#define BURROWS_WHEELER_H

namespace CSE_584A
{
   /**
   * \brief Computes the suffix array for string S.
   *
   * Using the precomputed suffix array, in linear time the burrows wheeler tranform
   * computes the previous character at each suffix array index.
   *
   * \param S (in) The string on which to compute the Burrows-Wheeler transform.
   * \param A (in) The precomputed suffix array of string S.
   * \param B (out) The Burrows-Wheeler transform of string S.
   * \param n (in) The length of string S, suffix array A, and Burrows-Wheeler tranform B.
   */
   void ComputeBurrowsWheelerTransform(const char* S, const int* A, char* B, int n);
}

#endif