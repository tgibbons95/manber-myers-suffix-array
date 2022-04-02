/*****************************************************************//**
 * @file   AdjacentLcp.h
 * @brief  Provides method declarations related to the adjacent LCP array of a string
 *
 * @author Thomas Gibbons
 * @date   Mar 2022
 *********************************************************************/

#ifndef ADJACENT_LCP_H
#define ADJACENT_LCP_H

namespace CSE_584A
{
   /**
   * \brief Computes the adjacent longest common prefix (LCP) for string S.
   *
   * Using the precomputed suffix array and rank array G, in linear time the adjacent LCP
   * is computed.
   *
   * \param S (in) The string on which to compute the Burrows-Wheeler transform.
   * \param A (in) The precomputed suffix array of string S.
   * \param G (in) The precomputed rank array of string S.
   * \param L (out) The adjacent LCP of string S.
   * \param n (in) The length of string S, suffix array A, rank array G, and adjacent LCP L.
   */
   void ComputeAdjacentLcp(const char* S, const int* A, const int* G, int* L, int n);
}

#endif