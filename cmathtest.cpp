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

#ifdef REAL
typedef real_t data_t;
#else
typedef complex_t data_t;
#endif // REAL

#ifndef NOTIME
#include <woo/timer/woo_boostchronotimers.hpp>
#endif
#include <woo/random/woo_mtrandom.hpp>

const int MAX_LEN = 8000000;
const complex_t CMPLX_MINUS_ONE_ = complex_t((real_t) 0., (real_t) -1.);
const real_t REAL_MINUS_ONE_ = real_t(-1.);


int main(int narg, char** args) {
  int max_len = MAX_LEN;
  if(narg == 2) {
    max_len = atoi(args[1]);
  } // if

  std::cout << "MAX_LEN = " << max_len << std::endl;

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

#ifndef NOTIME
  woo::BoostChronoTimer timer;
  timer.start();
#endif
#pragma novector
  for(int i = 0; i < max_len; ++ i) {
    data_t temp = exp(carr[i]);
    outarr[i] = temp * rarr[i];
    #ifdef REAL
    outarr[i] = (REAL_MINUS_ONE_ * temp) * rarr[i];
    #else
    outarr[i] = (CMPLX_MINUS_ONE_ * temp) * rarr[i];
    #endif // REAL
  } // for
#ifndef NOTIME
  timer.stop();
  std::cout << "CMATH: " << timer.elapsed_msec() << " ms" << std::endl;
#endif

  delete[] outarr;
  delete[] carr;
  delete[] rarr;

  return 0;
} // main()

