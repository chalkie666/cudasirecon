#ifndef UCSF_MSG_ISP_H
#define UCSF_MSG_ISP_H

/*
 * Declare functions, structures, and constants for utility routines
 * for working with signal processing algorithms.
 *
 * Available functions are:
 *
 *   Size for FFT
 *     isp_nicesize
 *     isp_nicesmallsize
 *
 *   Trend removal
 *     isp_avgslope_*
 *     isp_polyfit_* and isp_polysub_*
 *
 *   Padding
 *     isp_pad_*
 *     isp_padramp_*
 *
 *   Multiplying two arrays
 *     isp_mul_*
 *
 * The functions handle either 1, 2, 3, or 4 dimensional arrays as indicated
 * by the last digit in the function name.  The array data type handled by a
 * function is indicated by the character (characters, one per array for the
 * functions that take multiple arrays) after the digit for the number of
 * dimensions handled.  The types are:
 *
 *   c     Operates on a single-precision complex-valued array.
 *   s     Operates on a single-precision real-valued array.
 *   h     Operates on a single-precision halfcomplex array (the real
 *         real parts are in the elements 0 to n1/2 the imaginary components
 *         components appear in reverse order in the remainder of the
 *         elements.  This form is generated by FFTW's 1D real-to-complex
 *         FFT.
 *   u     Operates on the typical single-precision unpacked format used
 *         for real to complex FFTs (the fastest varying dimension has
 *         floor(n1/2) + 1 complex values).
 */

#ifdef __cplusplus
extern "C" {
#endif


typedef struct IspComplex {
  float re;
  float im;
} IspComplex;


/*
 * Given an integer target, returns the smallest positive integer which
 * is greater than or equal to target and is the product of 2^m and odd primes
 * where m is greater than or equal to the maximum of 0 and min_exp2 and
 * the odd primes are each less than or equal to the minimum of
 * 19 and max_odd_prime.
 *
 * If target is greater than INT_MAX / 2 or 2^(min_exp2) is greater than
 * INT_MAX / 2, than -1 is returned.2^(sizeof(int) * CHAR_BIT - 2) or
 */

/*
 * integer function isp_nicesize(target, min_exp2, max_odd_prime)
 * integer target, min_exp2, max_odd_prime
 */
int isp_nicesize(int target, int min_exp2, int max_odd_prime);


/*
 * Given an integer target, returns the largest positive integer which
 * is less than or equal to target and is the product of 2^m and odd primes
 * where m is greater than or equal to the maximum of 0 and min_exp2 and
 * the odd primes are each less than or equal to the minimum of
 * 19 and max_odd_prime.
 *
 * If target is greater than INT_MAX / 2 or 2^(min_exp2) is greater than
 * target, than -1 is returned.
 */

/*
 * integer function isp_nicesmallsize(target, min_power2, max_odd_prime)
 * integer target, min_power2, max_odd_prime
 */
int isp_nicesmallsize(int target, int min_power2, int max_odd_prime);


/*
 * These functions use the average slope method (see Random Data:  Analysis
 * and Measurment, Julius S. Bendat and Allan G. Piersol, 1st Edition, 1971,
 * pg 288) to remove a linear trend from an array.  The characteristics of
 * the trend are (mean value and slope) are returned.
 */

/*
 * subroutine isp_avgslope_1c(n1, inout, mean, slope)
 * integer n1
 * complex out(*), mean, slope
 */
void isp_avgslope_1c
(
 int n1, IspComplex* inout, IspComplex* p_mean, IspComplex* p_slope
);

/*
 * subroutine isp_avgslope_1s(n1, inout, mean, slope)
 * integer n1
 * real inout(*), mean, slope
 */
void isp_avgslope_1s(int n1, float* inout, float* p_mean, float* p_slope);

/*
 * subroutine isp_avgslope_2c(n1, n2, w1, inout, mean, slope_parts)
 * integer n1, n2, w1
 * complex inout(w1,*), mean, slope_parts(2)
 */
void isp_avgslope_2c
(
 int n1,
 int n2,
 int w1,
 IspComplex* inout,
 IspComplex* p_mean,
 IspComplex slope_parts[2]
);

/*
 * subroutine isp_avgslope_2s(n1, n2, w1, inout, mean, slope_parts)
 * integer n1, n2, w1
 * real inout(w1,*), mean, slope_parts(2)
 */
void isp_avgslope_2s
(
 int n1, int n2, int w1, float* inout, float* p_mean, float slope_parts[2]
);

/*
 * subroutine isp_avgslope_3c(
 *      n1, n2, n3, w1, w2, inout, mean, slope_parts)
 * integer n1, n2, n3, w1, w2
 * complex inout(w1,w2,*), mean, slope_parts(3)
 */
void isp_avgslope_3c
(
 int n1,
 int n2,
 int n3,
 int w1,
 int w2,
 IspComplex* inout,
 IspComplex* p_mean,
 IspComplex slope_parts[3]
);

/*
 * subroutine isp_avgslope_3s(
 *      n1, n2, n3, w1, w2, inout, mean, slope_parts)
 * integer n1, n2, n3, w1, w2
 * real out(w1,w2,*), mean, slope_parts(3)
 */
void isp_avgslope_3s
(
 int n1,
 int n2,
 int n3,
 int w1,
 int w2,
 float* inout,
 float* p_mean,
 float slope_parts[3]
);

/*
 * subroutine isp_avgslope_4c(
 *      n1, n2, n3, n4, w1, w2, w3, inout, mean, slope_parts)
 * integer n1, n2, n3, n4, w1, w2, w3
 * complex inout(w1,w2,w3,*), mean, slope_parts(4)
 */
void isp_avgslope_4c
(
 int n1,
 int n2,
 int n3,
 int n4,
 int w1,
 int w2,
 int w3,
 IspComplex* inout,
 IspComplex* p_mean,
 IspComplex slope_parts[4]
);

/*
 * subroutine isp_avgslope_4s(
 *      n1, n2, n3, n4, w1, w2, w3, inout, mean, slope_parts)
 * integer n1, n2, n3, n4, w1, w2, w3
 * real out(w1,w2,w3,*), mean, slope_parts(4)
 */
void isp_avgslope_4s
(
 int n1,
 int n2,
 int n3,
 int n4,
 int w1,
 int w2,
 int w3,
 float* inout,
 float* p_mean,
 float slope_parts[4]
);


/*
 * Construct the coefficient matrix, cfmat, and pivot factors, ipiv,
 * needed by the isp_polyfit_* routines.  The *p_isbad (for C) or isbad
 * (for Fortran) is set to 0 if the operation is successful; otherwise
 * it will be set to a non-zero value.
 *
 * Requires linking with the NAG routines f07adf, f07aef, and f07mdf or
 * the LAPACK routines dgetrf, dgetrs, and dsytrf.
 */

/*
 * subroutine isp_polyfit_init_1(n1, order, cfmat, ipiv, isbad, iwork, rwork)
 * integer n1, order
 * double precision cfmat((order + 1) * (order + 1))
 * integer isbad, ipiv(order + 1)
 * double precision rwork((2 * order + 1) * (2 * order + 3))
 * integer iwork(2 * order + 1)
 */
void isp_polyfit_init_1
(
 int n1,
 int order,
 double* cfmat,
 int* ipiv,
 int* p_isbad,
 int* iwork,
 double* rwork
);

/*
 * subroutine isp_polyfit_init_2
 *      (n1, n2, order, cfmat, ipiv, isbad, iwork, rwork)
 * integer n1, n2, order
 * double precision cfmat((((order+1)*(order+2))/2)*
 *      (((order+1)*(order+2))/2))
 * integer isbad, ipiv(((order+1)*(order+2))/2)
 * double precision rwork((2 * order + 1) * (2 * order + 4))
 * integer iwork(2 * order + 1)
 */
void isp_polyfit_init_2
(
 int n1,
 int n2,
 int order,
 double* cfmat,
 int* ipiv,
 int* p_isbad,
 int* iwork,
 double* rwork
);

/*
 * subroutine isp_polyfit_init_3
 *      (n1, n2, n3, order, cfmat, ipiv, isbad, iwork, rwork)
 * integer n1, n2, n3, order
 * double precision cfmat((((order+1)*(order+2)*(order+3))/6)*
 *      (((order+1)*(order+2)*(order+3))/6))
 * integer isbad, ipiv(((order+1)*(order+2)*(order+3))/6)
 * double precision rwork((2 * order + 1) * (2 * order + 5))
 * integer iwork(2 * order + 1)
 */
void isp_polyfit_init_3
(
 int n1,
 int n2,
 int n3,
 int order,
 double* cfmat,
 int* ipiv,
 int* p_isbad,
 int* iwork,
 double* rwork
);

/*
 * subroutine isp_polyfit_init_4
 *      (n1, n2, n3, n4, order, cfmat, ipiv, isbad, iwork, rwork)
 * integer n1, n2, n3, n4, order
 * double precision cfmat((((order+1)*(order+2)*(order+3)*(order+4))/24)*
 *      (((order+1)*(order+2)*(order+3)*(order+4))/24))
 * integer isbad, ipiv(((order+1)*(order+2)*(order+3)*(order+4))/24)
 * double precision rwork((2 * order + 1) * (2 * order + 6))
 * integer iwork(2 * order + 1)
 */
void isp_polyfit_init_4
(
 int n1,
 int n2,
 int n3,
 int n4,
 int order,
 double* cfmat,
 int* ipiv,
 int* p_isbad,
 int* iwork,
 double* rwork
);


/*
 * Fit a polynomial to an array.  The polynomial expansion is of the
 * order, order, and the coordinates used in the expansion are:
 *
 *   x1 = (i1 - (n1+1)/2.0)/n1
 *   x2 = (i2 - (n2+1)/2.0)/n2
 *   x3 = (i3 - (n3+1)/2.0)/n3
 *   x4 = (i4 - (n4+1)/2.0)/n4
 *
 * where i1, i2, i3, i4 are the 1-based indices into the array.
 * coeff(a(k1,k2,k3,k4)) contains the coefficient for the
 * x1^k1 * x2^k2 * x3^k3 * x4^k4 term in the polynomial where a(k1,k2,k3)
 * is
 *
 * 1D:  a(k1,k2,k3,k4) = k1 + 1
 * 2D:  a(k1,k2,k3,k4) = k1 + 1 + (k2 * (2 * order + 3 - k2)) / 2
 * 3D:  a(k1,k2,k3,k4) = k1 + 1 + (k2 * (2 * order + 3 - k2 - 2 * k3)) / 2 +
 *      (k3 * (11 + order * (12 + order * 3) + k3 * (-3 * order - 6 + k3))) / 6
 * 4D:  a(k1,k2,k3,k4) = k1 + 1 + (k2 * (2 * order + 3 - k2 -
 *      2 * (k3 + k4))) / 2 + (k3 * (11 + 3 * k4 * (k4 - 4) + 3 * order *
 *      (4 - 2 * k4 + order) + k3 * (k3 - 3 * (order - k4 + 2)))) / 6 +
 *      (k4 * (2 * order - k4 + 5) * (10 + k4 * (k4 - 5 - 2 * order) +
 *      order * (2 * order + 10))) / 24
 *
 * For the functions that take a complex input array, the complex parts
 * of the coefficients are stored in the second half of the coeff array
 * since a DOUBLE COMPLEX type isn't standard.
 *
 * To initialize the cfmat and ipiv inputs, use the same dimensions and
 * order in a call to the corresponding isp_polyfit_init_* routine.
 *
 * *p_isbad (C) or isbad (Fortran) is set to be 0 when the fit is sucessful;
 * otherwise it is set to a non-zero value.
 *
 * Requires linking with the NAG routine f07mef or the LAPACK routine
 * dsytrs.
 */

/*
 * subroutine isp_polyfit_1c(n1, order, cfmat, ipiv, in, coeff, isbad)
 * integer n1, order
 * double precision cfmat((order + 1) * (order + 1))
 * integer ipiv(order + 1)
 * complex in(n1)
 *
 * integer isbad
 * double precision coeff(2*(order + 1))
 */
void isp_polyfit_1c
(
 int n1,
 int order,
 const double* cfmat,
 const int* ipiv,
 const IspComplex* in,
 double* coeff,
 int* p_isbad
);

/*
 * subroutine isp_polyfit_2c(n1, n2, w1, order, cfmat, ipiv, in, coeff, isbad)
 * integer n1, n2, w1, order
 * double precision cfmat((((order+1)*(order+2))/2)*
 *     (((order+1)*(order+2))/2))
 * integer ipiv(((order+1)*(order+2))/2)
 * complex in(w1,n2)
 *
 * integer isbad
 * double precision coeff((order + 1) * (order + 2))
 */
void isp_polyfit_2c
(
 int n1,
 int n2,
 int w1,
 int order,
 const double* cfmat,
 const int* ipiv,
 const IspComplex* in,
 double* coeff,
 int* p_isbad
);

/*
 * subroutine isp_polyfit_3c
 * (
 *  n1, n2, n3, w1, w2, order, cfmat, ipiv, in, coeff, isbad
 * )
 * integer n1, n2, n3, w1, w2, order
 * double precision cfmat((((order+1)*(order+2)*(order+3))/6)*
 *     (((order+1)*(order+2)*(order+3))/6))
 * integer ipiv(((order+1)*(order+2)*(order+3))/6)
 * complex in(w1,w2,n3)
 *
 * integer isbad
 * double precision coeff(((order + 1) * (order + 2) * (order+3)) / 3)
 */
void isp_polyfit_3c
(
 int n1,
 int n2,
 int n3,
 int w1,
 int w2,
 int order,
 const double* cfmat,
 const int* ipiv,
 const IspComplex* in,
 double* coeff,
 int* p_isbad
);

/*
 * subroutine isp_polyfit_4c
 * (
 *  n1, n2, n3, n4, w1, w2, w3, order, cfmat, ipiv, in, coeff, isbad
 * )
 * integer n1, n2, n3, n4, w1, w2, w3, order
 * double precision cfmat((((order+1)*(order+2)*(order+3)*(order+4))/24) *
 *     (((order+1)*(order+2)*(order+3)*(order+4))/24))
 * integer ipiv(((order+1)*(order+2)*(order+3)*(order+4))/24)
 * complex in(w1,w2,w3,n4)
 *
 * integer isbad
 * double precision coeff(((order + 1) * (order + 2) * (order+3) *
 *     (order+4)) / 12)
 */
void isp_polyfit_4c
(
 int n1,
 int n2,
 int n3,
 int n4,
 int w1,
 int w2,
 int w3,
 int order,
 const double* cfmat,
 const int* ipiv,
 const IspComplex* in,
 double* coeff,
 int* p_isbad
);

/*
 * subroutine isp_polyfit_1s(n1, order, cfmat, ipiv, in, coeff, isbad)
 * integer n1, order
 * double precision cfmat((order + 1) * (order + 1))
 * integer ipiv(order + 1)
 * real in(n1)
 *
 * integer isbad
 * double precision coeff(order + 1)
 */
void isp_polyfit_1s
(
 int n1,
 int order,
 const double* cfmat,
 const int* ipiv,
 const float* in,
 double* coeff,
 int* p_isbad
);

/*
 * subroutine isp_polyfit_2s(n1, n2, w1, order, cfmat, ipiv, in, coeff, isbad)
 * integer n1, n2, w1, order
 * double precision cfmat((((order+1)*(order+2))/2)*
 *     (((order+1)*(order+2))/2))
 * integer ipiv(((order+1)*(order+2))/2)
 * real in(w1,n2)
 *
 * integer isbad
 * double precision coeff(((order+1)*(order+2))/2)
 */
void isp_polyfit_2s
(
 int n1,
 int n2,
 int w1,
 int order,
 const double* cfmat,
 const int* ipiv,
 const float* in,
 double* coeff,
 int* p_isbad
);

/*
 * subroutine isp_polyfit_3s
 * (
 *  n1, n2, n3, w1, w2, order, cfmat, ipiv, in, coeff, isbad
 * )
 * integer n1, n2, n3, w1, w2, order
 * double precision cfmat((((order+1)*(order+2)*(order+3))/6)*
 *     (((order+1)*(order+2)*(order+3))/6))
 * integer ipiv(((order+1)*(order+2)*(order+3))/6)
 * real in(w1,w2,n3)
 *
 * integer isbad
 * double precision coeff(((order+1)*(order+2)*(order+3))/6)
 */
void isp_polyfit_3s
(
 int n1,
 int n2,
 int n3,
 int w1,
 int w2,
 int order,
 const double* cfmat,
 const int* ipiv,
 const float* in,
 double* coeff,
 int* p_isbad
);

/*
 * subroutine isp_polyfit_4s
 * (
 *  n1, n2, n3, n4, w1, w2, w3, order, cfmat, ipiv, in, coeff, isbad
 * )
 * integer n1, n2, n3, n4, w1, w2, w3, order
 * double precision cfmat((((order+1)*(order+2)*(order+3)*(order+4))/24)*
 *     (((order+1)*(order+2)*(order+3)*(order+4))/24))
 * integer ipiv(((order+1)*(order+2)*(order+3)*(order+4))/24)
 * real in(w1,w2,w3,n4)
 *
 * integer isbad
 * double precision coeff(((order+1)*(order+2)*(order+3)*(order+4))/24)
 */
void isp_polyfit_4s
(
 int n1,
 int n2,
 int n3,
 int n4,
 int w1,
 int w2,
 int w3,
 int order,
 const double* cfmat,
 const int* ipiv,
 const float* in,
 double* coeff,
 int* p_isbad
);

/*
 * These routines subtract a polynomial from an array.  The coordinate
 * system used to evaluate the polynomial and the ordering of the polynomial
 * coefficients in coeff is the same as used in the isp_polyfit_* calls.
 */

/*
 * subroutine isp_polysub_1c(n1, order, coeff, inout)
 * integer n1, order
 * double precision coeff(2 * (order+1))
 *
 * complex inout(n1)
 */
void isp_polysub_1c(int n1, int order, const double* coeff, IspComplex* inout);

/*
 * subroutine isp_polysub_2c(n1, n2, w1, order, coeff, inout)
 * integer n1, n2, w1, order
 * double precision coeff((order+1) * (order+2))
 *
 * complex inout(w1,n2)
 */
void isp_polysub_2c
(
 int n1, int n2, int w1, int order, const double* coeff, IspComplex* inout
);

/*
 * subroutine isp_polysub_3c(n1, n2, n3, w1, w2, order, coeff, inout)
 * integer n1, n2, n3, w1, w2, order
 * double precision coeff(((order+1) * (order+2) * (order+3)) / 3)
 *
 * complex inout(w1,w2,n3)
 */
void isp_polysub_3c
(
 int n1,
 int n2,
 int n3,
 int w1,
 int w2,
 int order,
 const double* coeff,
 IspComplex* inout
);

/*
 * subroutine isp_polysub_4c(n1, n2, n3, n4, w1, w2, w3, order, coeff, inout)
 * integer n1, n2, n3, n4, w1, w2, w3, order
 * double precision coeff(((order+1) * (order+2) * (order+3) *
 *     (order + 4)) / 12)
 *
 * complex inout(w1,w2,w3,n4)
 */
void isp_polysub_4c
(
 int n1,
 int n2,
 int n3,
 int n4,
 int w1,
 int w2,
 int w3,
 int order,
 const double* coeff,
 IspComplex* inout
);

/*
 * subroutine isp_polysub_1s(n1, order, coeff, inout)
 * integer n1, order
 * double precision coeff(order+1)
 *
 * real inout(n1)
 */
void isp_polysub_1s(int n1, int order, const double* coeff, float* inout);

/*
 * subroutine isp_polysub_2s(n1, n2, w1, order, coeff, inout)
 * integer n1, n2, w1, order
 * double precision coeff(((order+1)*(order+2))/2)
 *
 * real inout(w1,n2)
 */
void isp_polysub_2s
(
 int n1, int n2, int w1, int order, const double* coeff, float* inout
);

/*
 * subroutine isp_polysub_3s(n1, n2, n3, w1, w2, order, coeff, inout)
 * integer n1, n2, n3, w1, w2, order
 * double precision coeff(((order+1)*(order+2)*(order+3))/6)
 *
 * real inout(w1,w2,n3)
 */
void isp_polysub_3s
(
 int n1,
 int n2,
 int n3,
 int w1,
 int w2,
 int order,
 const double* coeff,
 float* inout
);

/*
 * subroutine isp_polysub_4s(n1, n2, n3, n4, w1, w2, w3, order, coeff, inout)
 * integer n1, n2, n3, n4, w1, w2, w3, order
 * double precision coeff(((order+1)*(order+2)*(order+3)*(order+4))/24)
 *
 * real inout(w1,w2,w3,n4)
 */
void isp_polysub_4s
(
 int n1,
 int n2,
 int n3,
 int n4,
 int w1,
 int w2,
 int w3,
 int order,
 const double* coeff,
 float* inout
);

/*
 * These routines fill the end of an array, inout, with a fixed value, pad.
 * inout is dimensioned n1 + np1 by n2 + np2 by n3 + np3 by n4 + np4
 * (fastest varying first, slowest varying last) and is embedded in a larger
 * array of dimensioned w1 by w2 by w3 by *.  np1 elements are appended after
 * the initial n1 elements in the first dimension, np2 elements are appended
 * after the initial n2 elements in the second dimension, np3 elements are
 * appended after the initial n3 elements in the third dimension, and
 * np4 elements are appended after the initial n4 elements in the fourth
 * dimension.
 */

/*
 * subroutine isp_pad_1c(n1, np1, pad, inout)
 * integer n1, np1
 * complex pad, inout(*)
 */
void isp_pad_1c(int n1, int np1, IspComplex pad, IspComplex* inout);

/*
 * subroutine isp_pad1s(n1, np1, pad, inout)
 * integer n1, np1
 * real pad, inout(*)
 */
void isp_pad_1s(int n1, int np1, float pad, float* inout);

/*
 * subroutine isp_pad_2c(n1, n2, np1, np2, w1, pad, inout)
 * integer n1, n2, np1, np2, w1
 * complex pad, inout(w1, *)
 */
void isp_pad_2c
(
 int n1, int n2, int np1, int np2, int w1, IspComplex pad, IspComplex* inout
);

/*
 * subroutine isp_pad_2s(n1, n2, np1, np2, w1, pad, inout)
 * integer n1, n2, np1, np2, w1
 * real pad, inout(w1, *)
 */
void isp_pad_2s
(
 int n1, int n2, int np1, int np2, int w1, float pad, float* inout
);

/*
 * subroutine isp_pad_3c(n1, n2, n3, np1, np2, np3, w1, w2, pad, inout)
 * integer n1, n2, n3, np1, np2, np3, w1, w2
 * complex pad, inout(w1, w2, *)
 */
void isp_pad_3c
(
 int n1, 
 int n2,
 int n3,
 int np1,
 int np2,
 int np3,
 int w1,
 int w2,
 IspComplex pad,
 IspComplex* inout
);

/*
 * subroutine isp_pad_3s(n1, n2, n3, np1, np2, np3, w1, w2, pad, inout)
 * integer n1, n2, n3, np1, np2, np3, w1, w2
 * real pad, inout(w1, w2, *)
 */
void isp_pad_3s
(
 int n1,
 int n2,
 int n3,
 int np1,
 int np2,
 int np3,
 int w1,
 int w2,
 float pad,
 float* inout
);

/*
 * subroutine isp_pad_4c(n1, n2, n3, n4, np1, np2, np3, np4, w1, w2, w3, pad,
 *     inout)
 * integer n1, n2, n3, n4, np1, np2, np3, np4, w1, w2, w3
 * complex pad, inout(w1, w2, w3, *)
 */
void isp_pad_4c
(
 int n1, 
 int n2,
 int n3,
 int n4,
 int np1,
 int np2,
 int np3,
 int np4,
 int w1,
 int w2,
 int w3,
 IspComplex pad,
 IspComplex* inout
);

/*
 * subroutine isp_pad_4s(n1, n2, n3, n4, np1, np2, np3, n4, w1, w2, w3, pad,
 *     inout)
 * integer n1, n2, n3, n4, np1, np2, np3, np4, w1, w2, w3
 * real pad, inout(w1, w2, w3, *)
 */
void isp_pad_4s
(
 int n1,
 int n2,
 int n3,
 int n4,
 int np1,
 int np2,
 int np3,
 int np4,
 int w1,
 int w2,
 int w3,
 float pad,
 float* inout
);


/*
 * These routines fill the an of the array, inout, with values using
 * linear ramps.  This emulates the padding done in decon and Maria Vieira's
 * software.  inout is dimensioned n1 + np1 by n2 + np2 by n3 + np3 by
 * n4 + np4 (fastest varying first, slowest varying last) and is embedded
 * in a larger array of dimensioned w1 by w2 by w3 by *.  np1 elements are
 * appended after the initial n1 elements in the first dimension, np2
 * elements are appended after the initial n2 elements in the second
 * dimension, np3 elements are appended after the initial n3 elements in the
 * third dimension, and np4 elements are appended after the initial n4
 * elements in the fourth dimension.
 */

/*
 * subroutine isp_padramp_1c(n1, np1,inout)
 * integer n1, np1
 * complex inout(*)
 */
void isp_padramp_1c(int n1, int np1, IspComplex* inout);

/*
 * subroutine isp_padramp_1s(n1, np1,inout)
 * integer n1, np1
 * real inout(*)
 */
void isp_padramp_1s(int n1, int np1, float* inout);

/*
 * subroutine isp_padramp_2c(n1, n2, np1, np2, w1, inout)
 * integer n1, n2, np1, np2, w1
 * complex inout(w1, *)
 */
void isp_padramp_2c
(
 int n1, int n2, int np1, int np2, int w1, IspComplex* inout
);

/*
 * subroutine isp_padramp_2s(n1, n2, np1, np2, w1, inout)
 * integer n1, n2, np1, np2, w1
 * real inout(w1, *)
 */
void isp_padramp_2s
(
 int n1, int n2, int np1, int np2, int w1, float* inout
);

/*
 * subroutine isp_padramp_3c(n1, n2, n3, np1, np2, np3, w1, w2, inout)
 * integer n1, n2, n3, np1, np2, np3, w1, w2
 * complex inout(w1, w2, *)
 */
void isp_padramp_3c
(
 int n1,
 int n2,
 int n3,
 int np1,
 int np2,
 int np3,
 int w1,
 int w2,
 IspComplex* inout
);

/*
 * subroutine isp_padramp_3s(n1, n2, n3, np1, np2, np3, w1, w2, inout)
 * integer n1, n2, n3, np1, np2, np3, w1, w2
 * real inout(w1, w2, *)
 */
void isp_padramp_3s
(
 int n1,
 int n2,
 int n3,
 int np1,
 int np2,
 int np3,
 int w1,
 int w2,
 float* inout
);

/*
 * subroutine isp_padramp_4c(n1, n2, n3, n4, np1, np2, np3, np4, w1, w2, w3,
 *     inout)
 * integer n1, n2, n3, n4, np1, np2, np3, np4, w1, w2, w3
 * complex inout(w1, w2, w3, *)
 */
void isp_padramp_4c
(
 int n1,
 int n2,
 int n3,
 int n4,
 int np1,
 int np2,
 int np3,
 int np4,
 int w1,
 int w2,
 int w3,
 IspComplex* inout
);

/*
 * subroutine isp_padramp_4s(n1, n2, n3, n4, np1, np2, np3, np4, w1, w2, w3,
 *     inout)
 * integer n1, n2, n3, n4, np1, np2, np3, np4, w1, w2, w3
 * real inout(w1, w2, w3, *)
 */
void isp_padramp_4s
(
 int n1,
 int n2,
 int n3,
 int n4,
 int np1,
 int np2,
 int np3,
 int np4,
 int w1,
 int w2,
 int w3,
 float* inout
);


/*
 * Computes the simplified Wiener filter (scale * A* / (A A* + k), where k and
 * scale are constants) for a filter represented by an array.  The computation
 * is done in place.  inout can be a subset of a larger array whose dimensions
 * are wio1 by wio2 by wio3 by * (wio1 should be at least as large as n1, wio2
 * should be at least as large as n2, and wio3 should be at least as large as
 * n3).
 *
 * For the halfcomplex and unpacked types, n1 refers to the dimension in the
 * spatial domain.  For the unpacked types, the arrays are declared as real
 * so wio1 is the number of reals (not complex values; i.e. wio1 is at least
 * 2 * (n1 / 2 + 1)) in the first dimension.
 */

/*
 * subroutine isp_simple_wiener_1c(n1, k, scale, inout)
 * integer n1
 * real k, scale
 * complex inout(*)
 */
void isp_simple_wiener_1c(int n1, float k, float scale, IspComplex* inout);

/*
 * subroutine isp_simple_wiener_1h(n1, k, scale, inout)
 * integer n1
 * real k, scale, inout(*)
 */
void isp_simple_wiener_1h(int n1, float k, float scale, float* inout);

/*
 * subroutine isp_simple_wiener_1s(n1, k, scale, inout)
 * integer n1
 * real k, scale, inout(*)
 */
void isp_simple_wiener_1s(int n1, float k, float scale, float* inout);

/*
 * subroutine isp_simple_wiener_1u(n1, k, scale, inout)
 * integer n1
 * real k, scale, inout(*)
 */
void isp_simple_wiener_1u(int n1, float k, float scale, float* inout);

/*
 * subroutine isp_simple_wiener_2c(n1, n2, wio1, k, scale, inout)
 * integer n1, n2, wio1
 * real k, scale
 * complex inout(wio1,*)
 */
void isp_simple_wiener_2c(
    int n1, int n2, int wio1, float k, float scale, IspComplex* inout
);

/*
 * subroutine isp_simple_wiener_2s(n1, n2, wio1, k, scale, inout)
 * integer n1, n2, wio1
 * real k, scale, inout(wio1,*)
 */
void isp_simple_wiener_2s(
    int n1, int n2, int wio1, float k, float scale, float* inout
);

/*
 * subroutine isp_simple_wiener_2u(n1, n2, wio1, k, scale, inout)
 * integer n1, n2, wio1
 * real k, scale, inout(wio1,*)
 */
void isp_simple_wiener_2u(
    int n1, int n2, int wio1, float k, float scale, float* inout
);

/*
 * subroutine isp_simple_wiener_3s(n1, n2,n3, wio1, wio2, k, scale, inout)
 * integer n1, n2, n3, wio1, wio2
 * real k, scale
 * complex inout(wio1,wio2,*)
 */
void isp_simple_wiener_3c(
    int n1,
    int n2,
    int n3,
    int wio1,
    int wio2,
    float k,
    float scale,
    IspComplex* inout
);

/*
 * subroutine isp_simple_wiener_3s(n1, n2,n3, wio1, wio2, k, scale, inout)
 * integer n1, n2, n3, wio1, wio2
 * real k, scale, inout(wio1,wio2,*)
 */
void isp_simple_wiener_3s(
    int n1,
    int n2,
    int n3,
    int wio1,
    int wio2,
    float k,
    float scale,
    float* inout
);

/*
 * subroutine isp_simple_wiener_3u(n1, n2,n3, wio1, wio2, k, scale, inout)
 * integer n1, n2, n3, wio1, wio2
 * real k, scale, inout(wio1,wio2,*)
 */
void isp_simple_wiener_3u(
    int n1,
    int n2,
    int n3,
    int wio1,
    int wio2,
    float k,
    float scale,
    float* inout
);


/*
 * These functions perform an element by element multiplication of
 * two arrays (in and inout) with the same dimensions (n1 by n2 by
 * n3 by n4 where n1 is the size of the fastest varying dimension and n4
 * is the size of the slowest varying dimension).  The result
 * overwrites the contents of inout.  in can be a subset of a
 * larger array whose dimensions are wi1 by wi2 by wi3 by * (wi1 should be
 * at least as large as n1, wi2 should be at least as large as n2, and
 * wi3 should be at least as large as n3).  Similarly inout can be drawn
 * from a larger array whose dimensions are wio1 by wio2 by wio3 by *.
 *
 * For the halfcomplex and unpacked types, n1 refers to the dimension in
 * the spatial domain.  For the unpacked types, the arrays are declared
 * as real so wi1 or wio1 are the number of reals (not complex values;
 * i.e. wi1 is at least 2 * (n1 / 2 + 1)) in the first dimension.
 */

/*
 * subroutine isp_mul_1cc(n1, in, inout)
 * integer n1
 * complex in(*), inout(*)
 */
void isp_mul_1cc(int n1, const IspComplex* in, IspComplex* inout);

/*
 * subroutine isp_mul_1hh(n1, in, inout)
 * integer n1
 * real in(*), inout(*)
 */
void isp_mul_1hh(int n1, const float* in, float* inout);

/*
 * subroutine isp_mul_1sc(n1, in, inout)
 * integer n1
 * real in(*)
 * complex inout(*)
 */
void isp_mul_1sc(int n1, const float* in, IspComplex* inout);

/*
 * subroutine isp_mul_1ss(n1, in, inout)
 * integer n1
 * real in(*), inout(*)
 */
void isp_mul_1ss(int n1, const float* in, float* inout);

/*
 * subroutine isp_mul_1uc(n1, in, inout)
 * integer n1
 * real in(*)
 * complex inout(*)
 */
void isp_mul_1uc(int n1, const float* in, IspComplex* inout);

/*
 * subroutine isp_mul_1uu(n1, in, inout)
 * integer n1
 * real in(*), inout(*)
 */
void isp_mul_1uu(int n1, const float* in, float* inout);

/*
 * subroutine isp_mul_2cc(n1, n2, wi1, in, wio1, inout)
 * integer n1, n2, wi1, wio1
 * complex in(wi1, *), inout(wio1, *)
 */
void isp_mul_2cc
(
 int n1, int n2, int wi1, const IspComplex* in, int wio1, IspComplex* inout
);

/*
 * subroutine isp_mul_2sc(n1, n2, wi1, in, wio1, inout)
 * integer n1, n2, wi1, wio1
 * real in(wi1, *)
 * complex inout(wio1, *)
 */
void isp_mul_2sc
(
 int n1, int n2, int wi1, const float* in, int wio1, IspComplex* inout
);

/*
 * subroutine isp_mul_2ss(n1, n2, wi1, in, wio1, inout)
 * integer n1, n2, wi1, wio1
 * real in(wi1, *), inout(wio1, *)
 */
void isp_mul_2ss
(
 int n1, int n2, int wi1, const float* in, int wio1, float* inout
);

/*
 * subroutine isp_mul_2uc(n1, n2, wi1, in, wio1, inout)
 * integer n1, n2, wi1, wio1
 * real in(wi1, *)
 * complex inout(wio1, *)
 */
void isp_mul_2uc
(
 int n1, int n2, int wi1, const float* in, int wio1, IspComplex* inout
);

/*
 * subroutine isp_mul_2uu(n1, n2, wi1, in, wio1, inout)
 * integer n1, n2, wi1, wio1
 * real in(wi1, *), inout(wio1, *)
 */
void isp_mul_2uu
(
 int n1, int n2, int wi1, const float* in, int wio1, float* inout
);

/*
 * subroutine isp_mul_3cc(n1, n2, n3, wi1, wi2, in, wio1, wio2, inout)
 * integer n1, n2, n3, wi1, wi2, wio1, wio2
 * complex in(wi1,wi2,*), inout(wio1,wio2,*)
 */
void isp_mul_3cc
(
 int n1,
 int n2,
 int n3,
 int wi1,
 int wi2,
 const IspComplex* in,
 int wio1,
 int wio2,
 IspComplex* inout
);

/*
 * subroutine isp_mul_3ss(n1, n2, n3, wi1, wi2, in, wio1, wio2, inout)
 * integer n1, n2, n3, wi1, wi2, wio1, wio2
 * real in(wi1,wi2,*), inout(wio1,wio2,*)
 */
void isp_mul_3ss
(
 int n1,
 int n2,
 int n3,
 int wi1,
 int wi2,
 const float* in,
 int wio1,
 int wio2,
 float* inout
);

/*
 * subroutine isp_mul_3sc(n1, n2, n3, wi1, wi2, in, wio1, wio2, inout)
 * integer n1, n2, n3, wi1, wi2, wio1, wio2
 * real in(wi1,wi2,*)
 * complex inout(wio1,wio2,*)
 */
void isp_mul_3sc
(
 int n1,
 int n2,
 int n3,
 int wi1,
 int wi2,
 const float* in,
 int wio1,
 int wio2,
 IspComplex* inout
);

/*
 * subroutine isp_mul_3uc(n1, n2, n3, wi1, wi2, in, wio1, wio2, inout)
 * integer n1, n2, n3, wi1, wi2, wio1, wio2
 * real in(wi1,wi2,*)
 * complex inout(wio1,wio2,*)
 */
void isp_mul_3uc
(
 int n1,
 int n2,
 int n3,
 int wi1,
 int wi2,
 const float* in,
 int wio1,
 int wio2,
 IspComplex* inout
);

/*
 * subroutine isp_mul_3uu(n1, n2, n3, wi1, wi2, in, wio1, wio2, inout)
 * integer n1, n2, n3, wi1, wi2, wio1, wio2
 * real in(wi1,wi2,*), inout(wio1,wio2,*)
 */
void isp_mul_3uu
(
 int n1,
 int n2,
 int n3,
 int wi1,
 int wi2,
 const float* in,
 int wio1,
 int wio2,
 float* inout
);

/*
 * subroutine isp_mul_4cc(n1, n2, n3, n4, wi1, wi2, wi3, in, wio1, wio2, wio3,
 *     inout)
 * integer n1, n2, n3, n4, wi1, wi2, wi3, wio1, wio2, wio3
 * complex in(wi1,wi2,w3,*), inout(wio1,wio2,wio3,*)
 */
void isp_mul_4cc
(
 int n1,
 int n2,
 int n3,
 int n4,
 int wi1,
 int wi2,
 int wi3,
 const IspComplex* in,
 int wio1,
 int wio2,
 int wio3,
 IspComplex* inout
);

/*
 * subroutine isp_mul_4sc(n1, n2, n3, n4, wi1, wi2, wi3, in, wio1, wio2, wio3,
 *     inout)
 * integer n1, n2, n3, n4, wi1, wi2, wi3, wio1, wio2, wio3
 * real in(wi1,wi2,wi3,*)
 * complex inout(wio1,wio2,wio3,*)
 */
void isp_mul_4sc
(
 int n1,
 int n2,
 int n3,
 int n4,
 int wi1,
 int wi2,
 int wi3,
 const float* in,
 int wio1,
 int wio2,
 int wio3,
 IspComplex* inout
);

/*
 * subroutine isp_mul_4ss(n1, n2, n3, n4, wi1, wi2, wi3, in, wio1, wio2, wio3,
 *     inout)
 * integer n1, n2, n3, n4, wi1, wi2, wi3, wio1, wio2, wio3
 * real in(wi1,wi2,wi3,*), inout(wio1,wio2,wio3,*)
 */
void isp_mul_4ss
(
 int n1,
 int n2,
 int n3,
 int n4,
 int wi1,
 int wi2,
 int wi3,
 const float* in,
 int wio1,
 int wio2,
 int wio3,
 float* inout
);

/*
 * subroutine isp_mul_4uc(n1, n2, n3, n4, wi1, wi2, wi3, in, wio1, wio2, wio3,
 *     inout)
 * integer n1, n2, n3, n4, wi1, wi2, wi3, wio1, wio2, wio3
 * real in(wi1,wi2,wi3,*)
 * complex inout(wio1,wio2,wio3,*)
 */
void isp_mul_4uc
(
 int n1,
 int n2,
 int n3,
 int n4,
 int wi1,
 int wi2,
 int wi3,
 const float* in,
 int wio1,
 int wio2,
 int wio3,
 IspComplex* inout
);

/*
 * subroutine isp_mul_4uu(n1, n2, n3, n4, wi1, wi2, wi3, in, wio1, wio2, wio3,
 *     inout)
 * integer n1, n2, n3, n4, wi1, wi2, wi3, wio1, wio2, wio3
 * real in(wi1,wi2,wi3,*), inout(wio1,wio2,wio3,*)
 */
void isp_mul_4uu
(
 int n1,
 int n2,
 int n3,
 int n4,
 int wi1,
 int wi2,
 int wi3,
 const float* in,
 int wio1,
 int wio2,
 int wio3,
 float* inout
);


/*
 * These functions perform an element by element multiplication of
 * two arrays with the same dimensions.  One of the arrays is represented
 * as an outer product of two, three, or four one dimensional arrays, i.e.
 * in Fortran indexing notation,
 *   a(i,j,k,l) = s1(i) * s2(j) * s3(k) * s4(l)
 * where s1 has n1 elements (2 * (n1/2 + 1) elements for the unpacked
 * case), s2 has n2 elements (2 * (n2/2 + 1) for the unpacked case), s3 has
 * n3 elements (2 * (n3/2 + 1) for the unpacked case), and s4 has
 * n4 elements (2 * (n4/2 + 1) for the unpacked case).  The other array,
 * inout, is a full two, three, or four dimensional array which can be a
 * subset of a larger array whose dimensions are wio1 by wio2 by wio3 by *
 * (wio1 should be at least as large as n1, wio2 should be at least as
 * large as n2, and wio3 should be at least as large as n3).  The result
 * overwrites the contents of inout.
 *
 * For the halfcomplex and unpacked types, n1 refers to the dimension in
 * the spatial domain.  For the unpacked types, the arrays are declared
 * as real so wio1 is the number of reals (not complex values;
 * i.e. wio1 is at least 2 * (n1 / 2 + 1)) in the first dimension.
 */

/*
 * subroutine isp_mul_sep_2ccc(n1, n2, s1, s2, wio1, inout)
 * integer n1, n2, wio1
 * complex s1(*), s2(*), inout(wio1,*)
 */
void isp_mul_sep_2ccc
(
 int n1,
 int n2,
 const IspComplex* s1,
 const IspComplex* s2,
 int wio1,
 IspComplex* inout
);

/*
 * subroutine isp_mul_sep_2ssc(n1, n2, s1, s2, wio1, inout)
 * integer n1, n2, wio1
 * real s1(*), s2(*)
 * complex inout(wio1,*)
 */
void isp_mul_sep_2ssc
(
 int n1, int n2, const float* s1, const float* s2, int wio1, IspComplex* inout
);

/*
 * subroutine isp_mul_sep_2sss(n1, n2, s1, s2, wio1, inout)
 * integer n1, n2, wio1
 * real s1(*), s2(*), inout(wio1,*)
 */
void isp_mul_sep_2sss
(
 int n1, int n2, const float* s1, const float* s2, int wio1, float* inout
);

/*
 * subroutine isp_mul_sep_2uuu(n1, n2, s1, s2, wio1, inout)
 * integer n1, n2, wio1
 * real s1(*), s2(*), inout(wio1,*)
 */
void isp_mul_sep_2uuu
(
 int n1, int n2, const float* s1, const float* s2, int wio1, float* inout
);

/*
 * subroutine isp_mul_sep_3cccc(n1, n2, n3, s1, s2, s3, wio1, wio2, inout)
 * integer n1, n2, n3, wio1, wio2
 * complex s1(*), s2(*), s3(*), inout(wio1,wio2,*)
 */
void isp_mul_sep_3cccc
(
 int n1,
 int n2,
 int n3,
 const IspComplex* s1,
 const IspComplex* s2,
 const IspComplex* s3,
 int wio1,
 int wio2,
 IspComplex* inout
);

/*
 * subroutine isp_mul_sep_3sssc(n1, n2, n3, s1, s2, s3, wio1, wio2, inout)
 * integer n1, n2, n3, wio1, wio2
 * real s1(*), s2(*), s3(*)
 * complex inout(wio1,wio2,*)
 */
void isp_mul_sep_3sssc
(
 int n1,
 int n2,
 int n3,
 const float* s1,
 const float* s2,
 const float* s3,
 int wio1,
 int wio2,
 IspComplex* inout
);

/*
 * subroutine isp_mul_sep_3ssss(n1, n2, n3, s1, s2, s3, wio1, wio2, inout)
 * integer n1, n2, n3, wio1, wio2
 * real s1(*), s2(*), s3(*), inout(wio1,wio2,*)
 */
void isp_mul_sep_3ssss
(
 int n1,
 int n2,
 int n3,
 const float* s1,
 const float* s2,
 const float* s3,
 int wio1,
 int wio2,
 float* inout
);

/*
 * subroutine isp_mul_sep_3uuuu(n1, n2, n3, s1, s2, s3, wio1, wio2, inout)
 * integer n1, n2, n3, wio1, wio2
 * real s1(*), s2(*), s3(*), inout(wio1,wio2,*)
 */
void isp_mul_sep_3uuuu
(
 int n1,
 int n2,
 int n3,
 const float* s1,
 const float* s2,
 const float* s3,
 int wio1,
 int wio2,
 float* inout
);


/*
 * subroutine isp_mul_sep_4ccccc(n1, n2, n3, n4, s1, s2, s3, s4, wio1, wio2,
 *     wio3, inout)
 * integer n1, n2, n3, n4, wio1, wio2, wio3
 * complex s1(*), s2(*), s3(*), s4(*), inout(wio1,wio2,wio3,*)
 */
void isp_mul_sep_4ccccc
(
 int n1,
 int n2,
 int n3,
 int n4,
 const IspComplex* s1,
 const IspComplex* s2,
 const IspComplex* s3,
 const IspComplex* s4,
 int wio1,
 int wio2,
 int wio3,
 IspComplex* inout
);

/*
 * subroutine isp_mul_sep_4ssssc(n1, n2, n3, n4, s1, s2, s3, s4, wio1, wio2,
 *     wio3, inout)
 * integer n1, n2, n3, n4, wio1, wio2, wio3
 * real s1(*), s2(*), s3(*), s4(*)
 * complex inout(wio1,wio2,wio3,*)
 */
void isp_mul_sep_4ssssc
(
 int n1,
 int n2,
 int n3,
 int n4,
 const float* s1,
 const float* s2,
 const float* s3,
 const float* s4,
 int wio1,
 int wio2,
 int wio3,
 IspComplex* inout
);

/*
 * subroutine isp_mul_sep_4sssss(n1, n2, n3, n4, s1, s2, s3, s4, wio1, wio2,
 *     wio3, inout)
 * integer n1, n2, n3, n4, wio1, wio2, wio3,
 * real s1(*), s2(*), s3(*), s4, inout(wio1,wio2,wio3,*)
 */
void isp_mul_sep_4sssss
(
 int n1,
 int n2,
 int n3,
 int n4,
 const float* s1,
 const float* s2,
 const float* s3,
 const float* s4,
 int wio1,
 int wio2,
 int wio3,
 float* inout
);

/*
 * subroutine isp_mul_sep_4uuuuu(n1, n2, n3, n4, s1, s2, s3, s4, wio1, wio2,
 *     wio3, inout)
 * integer n1, n2, n3, n4, wio1, wio2, wio3
 * real s1(*), s2(*), s3(*), s4(*), inout(wio1,wio2,wio3,*)
 */
void isp_mul_sep_4uuuuu
(
 int n1,
 int n2,
 int n3,
 int n4,
 const float* s1,
 const float* s2,
 const float* s3,
 const float* s4,
 int wio1,
 int wio2,
 int wio3,
 float* inout
);


/*
 * These functions perform an element by element multiplication of
 * two arrays with the same dimensions.  One of the arrays is represented
 * as an outer product of a two-dimensional array and a one-dimensional
 * array, i.e. in Fortran indexing notation
 *   a(i,j,k) = s12(i,j) * s3(k)          (the isp_mul_sep_12_* functions)
 *   a(i,j,k) = s13(i,k) * s2(j)          (the isp_mul_sep_13_* functions)
 *   a(i,j,k) = s23(j,k) * s1(i)          (the isp_mul_sep_23_* functions)
 * The other array, inout, is a full three dimensional array
 * which can be a subset of a larger array whose dimensions are
 * wio1 by wio2 by * (wio1 should be at least as large as n1 and wio2
 * should be at least as large as n2).  The result overwrites the
 * contents of inout.
 *
 * For the halfcomplex and unpacked types, n1 refers to the dimension in
 * the spatial domain.  For the unpacked types, the arrays are declared
 * as real so the first dimension width is the number of reals (not complex
 * values; i.e. the first dimension width must be at least 2 * (n1 / 2 + 1))
 * in the first dimension.
 */

/*
 * subroutine isp_mul_sep_12_3sss(n1, n2, n3, ws, s12, s3, wio1, wio2, inout)
 * integer n1, n2, n3, ws, wio1, wio2
 * real s12(ws,*), s3(*), inout(wio1,wio2,*)
 */
void isp_mul_sep_12_3sss
(
 int n1,
 int n2,
 int n3,
 int ws,
 const float* s12,
 const float* s3,
 int wio1,
 int wio2,
 float* inout
);

/*
 * subroutine isp_mul_sep_12_3uuu(n1, n2, n3, ws, s12, s3, wio1, wio2, inout)
 * integer n1, n2, n3, ws, wio1, wio2
 * real s12(ws,*), s3(*), inout(wio1,wio2,*)
 */
void isp_mul_sep_12_3uuu
(
 int n1,
 int n2,
 int n3,
 int ws,
 const float* s12,
 const float* s3,
 int wio1,
 int wio2,
 float* inout
);

/*
 * subroutine isp_mul_sep_13_3sss(n1, n2, n3, ws, s13, s2, wio1, wio2, inout)
 * integer n1, n2, n3, ws, wio1, wio2
 * real s13(ws,*), s2(*), inout(wio1,wio2,*)
 */
void isp_mul_sep_13_3sss
(
 int n1,
 int n2,
 int n3,
 int ws,
 const float* s13,
 const float* s2,
 int wio1,
 int wio2,
 float* inout
);

/*
 * subroutine isp_mul_sep_13_3uuu(n1, n2, n3, ws, s13, s2, wio1, wio2, inout)
 * integer n1, n2, n3, ws, wio1, wio2
 * real s13(ws,*), s2(*), inout(wio1,wio2,*)
 */
void isp_mul_sep_13_3uuu
(
 int n1,
 int n2,
 int n3,
 int ws,
 const float* s13,
 const float* s2,
 int wio1,
 int wio2,
 float* inout
);

/*
 * subroutine isp_mul_sep_23_3sss(n1, n2, n3, ws, s23, s1, wio1, wio2, inout)
 * integer n1, n2, n3, ws, wio1, wio2
 * real s23(ws,*), s1(*), inout(wio1,wio2,*)
 */
void isp_mul_sep_23_3sss
(
 int n1,
 int n2,
 int n3,
 int ws,
 const float* s23,
 const float* s1,
 int wio1,
 int wio2,
 float* inout
);

/*
 * subroutine isp_mul_sep_23_3uuu(n1, n2, n3, ws, s23, s1, wio1, wio2, inout)
 * integer n1, n2, n3, ws, wio1, wio2
 * real s23(ws,*), s1(*), inout(wio1,wio2,*)
 */
void isp_mul_sep_23_3uuu
(
 int n1,
 int n2,
 int n3,
 int ws,
 const float* s23,
 const float* s1,
 int wio1,
 int wio2,
 float* inout
);


#ifdef __cplusplus
}
#endif /* close extern "C" */

#endif /* include guard */
