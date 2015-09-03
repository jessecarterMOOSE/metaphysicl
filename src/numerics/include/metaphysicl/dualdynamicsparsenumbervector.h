//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
// 
// MetaPhysicL - A metaprogramming library for physics calculations
//
// Copyright (C) 2013 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-
//
// $Id: core.h 37197 2013-02-21 05:49:09Z roystgnr $
//
//--------------------------------------------------------------------------

#ifndef METAPHYSICL_DUALDYNAMICSPARSENUMBERVECTOR_H
#define METAPHYSICL_DUALDYNAMICSPARSENUMBERVECTOR_H


#include "metaphysicl/dualnumber.h"
#include "metaphysicl/dynamicsparsenumbervector.h"


namespace MetaPhysicL {

template <typename T, typename I>
struct DerivativeType<DynamicSparseNumberVector<T, I> >
{
  typedef DynamicSparseNumberVector<typename DerivativeType<T>::type, I> type;
};


template <typename T, typename I>
struct DerivativesType<DynamicSparseNumberVector<T, I> >
{
  typedef DynamicSparseNumberVector<typename DerivativesType<T>::type, I> type;
};


template <typename T, typename I>
inline
typename DerivativeType<DynamicSparseNumberVector<T, I> >::type
derivative (const DynamicSparseNumberVector<T, I>& a,
            unsigned int derivativeindex)
{
  std::size_t index_size = a.size();

  typename DerivativeType<DynamicSparseNumberVector<T, I> >::type returnval;
  returnval.nude_indices() = a.nude_indices();
  returnval.nude_data().resize(index_size);

  for (unsigned int i=0; i != index_size; ++i)
    returnval.raw_at(i) = derivative(a.raw_at(i),derivativeindex);
  return returnval;
}


template <typename T, typename I>
inline
typename DerivativesType<DynamicSparseNumberVector<T, I> >::type
derivatives (const DynamicSparseNumberVector<T, I>& a)
{
  std::size_t index_size = a.size();

  typename DerivativesType<DynamicSparseNumberVector<T, I> >::type returnval;

  returnval.nude_indices() = a.nude_indices();
  returnval.resize(index_size);

  for (unsigned int i=0; i != index_size; ++i)
    returnval.raw_at(i) = derivatives(a.raw_at(i));
  return returnval;
}


template <typename T, typename I, unsigned int derivativeindex>
struct DerivativeOf<DynamicSparseNumberVector<T, I>, derivativeindex>
{
  static
  typename DerivativeType<DynamicSparseNumberVector<T, I> >::type
  derivative (const DynamicSparseNumberVector<T, I>& a)
  {
    std::size_t index_size = a.size();

    typename DerivativeType<DynamicSparseNumberVector<T, I> >::type returnval;

    returnval.nude_indices() = a.nude_indices();
    returnval.resize(index_size);

    for (unsigned int i=0; i != index_size; ++i)
      returnval.raw_at(i) = DerivativeOf<T,derivativeindex>::derivative(a.raw_at(i));
    return returnval;
  }
};



// For a vector of values a[i] each of which has a defined gradient,
// the divergence is the sum of derivative_wrt_xi(a[i])

// For a tensor of values, we take the divergence with respect to the
// first index.
template <typename T, typename I>
inline
typename DerivativeType<T>::type
divergence(const DynamicSparseNumberVector<T, I>& a)
{
  typename DerivativeType<T>::type returnval = 0;

  std::size_t size = a.size();
  for (unsigned int i=0; i != size; ++i)
    returnval += derivative(a.raw_at(i), a.raw_index(i));

  return returnval;
}


// For a vector of values, the gradient is going to be a tensor
template <typename T, typename I>
inline
DynamicSparseNumberVector<typename T::derivatives_type, I>
gradient(const DynamicSparseNumberVector<T, I>& a)
{
  static const unsigned int index_size = a.size();

  DynamicSparseNumberVector<typename T::derivatives_type, I> returnval;

  returnval.nude_indices() = a.nude_indices();
  returnval.nude_data().resize(index_size);

  for (unsigned int i=0; i != index_size; ++i)
    returnval.raw_at(i) = gradient(a.raw_at(i));

  return returnval;
}

// DualNumber is subordinate to DynamicSparseNumberVector

#define DualDynamicSparseNumberVector_comparisons(templatename) \
template<typename T, typename T2, typename D, typename I, bool reverseorder> \
struct templatename<DynamicSparseNumberVector<T2, I>, DualNumber<T, D>, reverseorder> { \
  typedef DynamicSparseNumberVector<typename Symmetric##templatename<T2,DualNumber<T, D>,reverseorder>::supertype, I> supertype; \
}

DualDynamicSparseNumberVector_comparisons(CompareTypes);
DualDynamicSparseNumberVector_comparisons(PlusType);
DualDynamicSparseNumberVector_comparisons(MinusType);
DualDynamicSparseNumberVector_comparisons(MultipliesType);
DualDynamicSparseNumberVector_comparisons(DividesType);
DualDynamicSparseNumberVector_comparisons(AndType);
DualDynamicSparseNumberVector_comparisons(OrType);

} // namespace MetaPhysicL

#endif // METAPHYSICL_DUALDYNAMICSPARSENUMBERVECTOR_H
