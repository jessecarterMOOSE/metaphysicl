
#if __cplusplus >= 201402L
#  include "metaphysicl/dualnamedarray.h"
#endif

#include "metaphysicl/dualnumberarray.h"
#include "metaphysicl/dualshadowsparsestruct.h"
#include "metaphysicl/dualshadowsparsevector.h"
#include "metaphysicl/dualshadowvector.h"
#include "metaphysicl/dynamicsparsenumberarray.h"
#include "metaphysicl/dynamicsparsenumbervector.h"
#include "metaphysicl/semidynamicsparsenumberarray.h"
#include "metaphysicl/sparsenumberarray.h"

#include <ostream>

using namespace MetaPhysicL;

template <typename T1, typename T2>
struct Instantiator {

#if __cplusplus >= 201402L
  DualExpression<T1, T2> test_de;
#endif

  DualNumber<T1, T2> test_dn;
  ShadowNumber<T1, T2> test_shadow;
  NumberArray<5, T1> test_na;
  NumberVector<5, T1> test_nv;
  typename SemiDynamicSparseNumberArrayOf<4, 2, T1, 3, T2, 5, T1, 7, T2>::type
          test_sdsna;
  typename DynamicSparseNumberArrayOf<4, 2, T1, 3, T2, 5, T1, 7, T2>::type
          test_dsna;
  typename DynamicSparseNumberVectorOf<4, 2, T1, 3, T2, 5, T1, 7, T2>::type
          test_dsnv;
  typename SparseNumberArrayOf<4, 2, T1, 3, T2, 5, T1, 7, T2>::type
          test_sna;
  typename SparseNumberVectorOf<4, 2, T1, 3, T2, 5, T1, 7, T2>::type
          test_snv;
  typename SparseNumberStructOf<4, 2, T1, 3, T2, 5, T1, 7, T2>::type
          test_sns;

#if __cplusplus >= 201402L
  NamedIndexArray
    <double,
     SparseNumberVector
       <long unsigned int,
        ULongSetConstructor<2>::type> > indexed_by_two;
#endif
};

template <typename T1, typename T2>
void test_out(std::ostream & output, const Instantiator<T1,T2> & i)
{
#if __cplusplus >= 201402L
  output << i.test_de;
  output << i.indexed_by_two;
#endif
  output << i.test_dn;
  output << i.test_shadow;
  output << i.test_na;
  output << i.test_nv;
  output << i.test_sdsna;
  output << i.test_dsna;
  output << i.test_dsnv;
  output << i.test_sna;
  output << i.test_snv;
  output << i.test_sns;
}

int main (void)
{
  Instantiator<float, float> i1;
  Instantiator<float, double> i2;
  Instantiator<double, double> i3;
  Instantiator<int, int> i4;

  std::ostream output(std::cout.rdbuf());
  test_out(output, i1);
  test_out(output, i2);
  test_out(output, i3);
  test_out(output, i4);
  return 0;
}
