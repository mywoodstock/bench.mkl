/***
  *  Project:
  *
  *  File: mkltest.cpp
  *  Created: Sep 19, 2015
  *
  *  Author: Abhinav Sarje <asarje@lbl.gov>
  */


#include <iostream>
#include <complex>

#ifdef DOUBLEPRECISION
typedef double real_t;
#else
typedef float real_t;
#endif // DOUBLEPRECISION

typedef std::complex<real_t> complex_t;

#ifdef DOUBLEPRECISION
#define MKL_Complex16 complex_t
#else
#define MKL_Complex8 complex_t
#endif // DOUBLEPRECISION

#ifdef REAL
typedef real_t data_t;
#else
typedef complex_t data_t;
#endif // REAL

#include <mkl.h>
#include <mkl_cblas.h>

#ifndef NOTIME
#include <woo/timer/woo_boostchronotimers.hpp>
#endif
#include <woo/random/woo_mtrandom.hpp>


const int MAX_LEN = 8000000;
const int VEC_LEN = 400;
const complex_t CMPLX_MINUS_ONE_ = complex_t((real_t) 0., (real_t) -1.);
const real_t REAL_MINUS_ONE_ = real_t(-1.);


int main(int narg, char** args) {
  int max_len = MAX_LEN;
  int vec_len = VEC_LEN;
  if(narg == 3) {
    max_len = atoi(args[1]);
    vec_len = atoi(args[2]);
  } // if

  std::cout << "MAX_LEN = " << max_len << " VEC_LEN = " << vec_len << std::endl;

  data_t *rarr = new (std::nothrow) data_t[max_len];
  data_t *carr = new (std::nothrow) data_t[max_len];
  data_t *outarr = new (std::nothrow) data_t[max_len];

  woo::MTRandomNumberGenerator rng;
  for(int i = 0; i < max_len; ++ i) {
    #ifdef REAL
    rarr[i] = data_t(rng.rand());
    carr[i] = data_t(rng.rand());
    #else
    rarr[i] = data_t(rng.rand(), rng.rand());
    carr[i] = data_t(rng.rand(), rng.rand());
    #endif // REAL
  } // for

  int loop_limit = max_len / vec_len;
  int loop_rem = max_len % vec_len;

  data_t *temp = new (std::nothrow) data_t[vec_len];
#ifndef NOTIME
  woo::BoostChronoTimer timer;
  timer.start();
#endif
  for(int l = 0; l < loop_limit; ++ l) {
    #ifdef REAL
    #ifdef DOUBLEPRECISION
    vdExp(vec_len, carr + vec_len * l, temp);
    cblas_dscal(vec_len, REAL_MINUS_ONE_, temp, 1);
    vdMul(vec_len, rarr, temp, outarr + vec_len * l);
    #else
    vsExp(vec_len, carr + vec_len * l, temp);
    cblas_sscal(vec_len, REAL_MINUS_ONE_, temp, 1);
    vsMul(vec_len, rarr, temp, outarr + vec_len * l);
    #endif // DOUBLEPRECISION
    #else
    #ifdef DOUBLEPRECISION
    vzExp(vec_len, carr + vec_len * l, temp);
    cblas_zscal(vec_len, &CMPLX_MINUS_ONE_, temp, 1);
    vzMul(vec_len, rarr, temp, outarr + vec_len * l);
    #else
    vcExp(vec_len, carr + vec_len * l, temp);
    cblas_cscal(vec_len, &CMPLX_MINUS_ONE_, temp, 1);
    vcMul(vec_len, rarr, temp, outarr + vec_len * l);
    #endif // DOUBLEPRECISION
    #endif // REAL
  } // for
#ifndef NOTIME
  timer.stop();
  std::cout << "MKL: " << timer.elapsed_msec() << " ms" << std::endl;
#endif
  delete[] temp;

  delete[] outarr;
  delete[] carr;
  delete[] rarr;

  return 0;
} // main()

