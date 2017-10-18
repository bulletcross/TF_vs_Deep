//=================================================================================================
/*!
//  \file blaze/math/expressions/DenseMatrix.h
//  \brief Header file for the DenseMatrix base class
//
//  Copyright (C) 2012-2017 Klaus Iglberger - All Rights Reserved
//
//  This file is part of the Blaze library. You can redistribute it and/or modify it under
//  the terms of the New (Revised) BSD License. Redistribution and use in source and binary
//  forms, with or without modification, are permitted provided that the following conditions
//  are met:
//
//  1. Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//  2. Redistributions in binary form must reproduce the above copyright notice, this list
//     of conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//  3. Neither the names of the Blaze development group nor the names of its contributors
//     may be used to endorse or promote products derived from this software without specific
//     prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
//  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
//  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
//  SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
//  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
//  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
*/
//=================================================================================================

#ifndef _BLAZE_MATH_EXPRESSIONS_DENSEMATRIX_H_
#define _BLAZE_MATH_EXPRESSIONS_DENSEMATRIX_H_


//*************************************************************************************************
// Includes
//*************************************************************************************************

#include <blaze/math/expressions/Matrix.h>
#include <blaze/math/shims/Reset.h>
#include <blaze/math/typetraits/IsLower.h>
#include <blaze/math/typetraits/IsUpper.h>
#include <blaze/system/Inline.h>
#include <blaze/util/algorithms/Min.h>
#include <blaze/util/DisableIf.h>
#include <blaze/util/EnableIf.h>
#include <blaze/util/Unused.h>


namespace blaze {

//=================================================================================================
//
//  CLASS DEFINITION
//
//=================================================================================================

//*************************************************************************************************
/*!\defgroup dense_matrix Dense Matrices
// \ingroup matrix
*/
/*!\defgroup dense_matrix_expression Expressions
// \ingroup dense_matrix
*/
/*!\brief Base class for dense matrices.
// \ingroup dense_matrix
//
// The DenseMatrix class is a base class for all dense matrix classes. It provides an
// abstraction from the actual type of the dense matrix, but enables a conversion back
// to this type via the Matrix base class.
*/
template< typename MT  // Type of the dense matrix
        , bool SO >    // Storage order
struct DenseMatrix
   : public Matrix<MT,SO>
{};
//*************************************************************************************************




//=================================================================================================
//
//  GLOBAL FUNCTIONS
//
//=================================================================================================

//*************************************************************************************************
/*!\name DenseMatrix global functions */
//@{
template< typename MT, bool SO >
BLAZE_ALWAYS_INLINE size_t spacing( const DenseMatrix<MT,SO>& dm ) noexcept;
//@}
//*************************************************************************************************


//*************************************************************************************************
/*!\brief Returns the spacing between the beginning of two rows/columns.
// \ingroup dense_matrix
//
// \param dm The given matrix.
// \return The spacing between the beginning of two rows/columns.
*/
template< typename MT  // Type of the matrix
        , bool SO >    // Storage order of the matrix
BLAZE_ALWAYS_INLINE size_t spacing( const DenseMatrix<MT,SO>& dm ) noexcept
{
   return (~dm).spacing();
}
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Backend implementation of the \c resetLower() function for row-major dense matrices.
// \ingroup dense_matrix
//
// \param matrix The given dense matrix.
// \return void
//
// This function resets the lower part (excluding the diagonal) of the given row-major dense
// matrix.
*/
template< typename MT >  // Type of the matrix
inline DisableIf_< IsUpper<MT> > resetLower_backend( DenseMatrix<MT,false>& dm )
{
   const size_t m( (~dm).rows()    );
   const size_t n( (~dm).columns() );

   for( size_t i=1UL; i<m; ++i ) {
      const size_t jend( min( i, n ) );
      for( size_t j=0UL; j<jend; ++j ) {
         reset( (~dm)(i,j) );
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Backend implementation of the \c resetLower() function for column-major dense matrices.
// \ingroup dense_matrix
//
// \param matrix The given dense matrix.
// \return void
//
// This function resets the lower part (excluding the diagonal) of the given column-major dense
// matrix.
*/
template< typename MT >  // Type of the matrix
inline DisableIf_< IsUpper<MT> > resetLower_backend( DenseMatrix<MT,true>& dm )
{
   const size_t m   ( (~dm).rows()    );
   const size_t n   ( (~dm).columns() );
   const size_t jend( min( m, n ) );

   for( size_t j=0UL; j<jend; ++j ) {
      for( size_t i=j+1UL; i<m; ++i ) {
         reset( (~dm)(i,j) );
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Backend implementation of the \c resetLower() function for lower dense matrices.
// \ingroup dense_matrix
//
// \param matrix The given dense matrix.
// \return void
//
// This function resets the lower part (excluding the diagonal) of the given lower dense matrix.
*/
template< typename MT  // Type of the matrix
        , bool SO >    // Storage order of the matrix
inline EnableIf_< IsUpper<MT> > resetLower_backend( DenseMatrix<MT,SO>& dm )
{
   UNUSED_PARAMETER( dm );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Resetting the lower part of the given dense matrix.
// \ingroup dense_matrix
//
// \param matrix The given dense matrix.
// \return void
//
// This function resets the lower part (excluding the diagonal) of the given dense matrix.
*/
template< typename MT  // Type of the matrix
        , bool SO >    // Storage order of the matrix
inline void resetLower( DenseMatrix<MT,SO>& dm )
{
   resetLower_backend( ~dm );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Backend implementation of the \c resetUpper() function for row-major dense matrices.
// \ingroup dense_matrix
//
// \param matrix The given dense matrix.
// \return void
//
// This function resets the upper part (excluding the diagonal) of the given row-major dense
// matrix.
*/
template< typename MT >  // Type of the matrix
inline DisableIf_< IsLower<MT> > resetUpper_backend( DenseMatrix<MT,false>& dm )
{
   const size_t m   ( (~dm).rows()    );
   const size_t n   ( (~dm).columns() );
   const size_t iend( min( m, n ) );

   for( size_t i=0UL; i<iend; ++i ) {
      for( size_t j=i+1UL; j<n; ++j ) {
         reset( (~dm)(i,j) );
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Backend implementation of the \c resetUpper() function for column-major dense matrices.
// \ingroup dense_matrix
//
// \param matrix The given dense matrix.
// \return void
//
// This function resets the upper part (excluding the diagonal) of the given column-major dense
// matrix.
*/
template< typename MT >  // Type of the matrix
inline DisableIf_< IsLower<MT> > resetUpper_backend( DenseMatrix<MT,true>& dm )
{
   const size_t m( (~dm).rows()    );
   const size_t n( (~dm).columns() );

   for( size_t j=1UL; j<n; ++j ) {
      const size_t iend( min( j, m ) );
      for( size_t i=0UL; i<iend; ++i ) {
         reset( (~dm)(i,j) );
      }
   }
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Backend implementation of the \c resetUpper() function for upper dense matrices.
// \ingroup dense_matrix
//
// \param matrix The given dense matrix.
// \return void
//
// This function resets the upper part (excluding the diagonal) of the given upper dense matrix.
*/
template< typename MT  // Type of the matrix
        , bool SO >    // Storage order of the matrix
inline EnableIf_< IsLower<MT> > resetUpper_backend( DenseMatrix<MT,SO>& dm )
{
   UNUSED_PARAMETER( dm );
}
/*! \endcond */
//*************************************************************************************************


//*************************************************************************************************
/*! \cond BLAZE_INTERNAL */
/*!\brief Resetting the upper part of the given dense matrix.
// \ingroup dense_matrix
//
// \param matrix The given dense matrix.
// \return void
//
// This function resets the upper part (excluding the diagonal) of the given dense matrix.
*/
template< typename MT  // Type of the matrix
        , bool SO >    // Storage order of the matrix
inline void resetUpper( DenseMatrix<MT,SO>& dm )
{
   resetUpper_backend( ~dm );
}
/*! \endcond */
//*************************************************************************************************

} // namespace blaze

#endif