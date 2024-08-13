/* ========================================================================== */
/*                                                                            */
/*  dhry.h                                                                    */
/*  (c) 2012 Author                                                           */
/*                                                                            */
/*  Description: Header file for Dhrystone benchmark                          */
/*   references:https://github.com/sifive/benchmark-dhrystone                 */
/*                                                                            */
/* ========================================================================== */

#ifndef _DHRY_H
#define _DHRY_H

// Define the number of loops to be executed
#define LOOPS   512

#ifdef __cplusplus
extern "C" {
#endif

// Declaration of the main function
extern void Proc0(void);

#ifdef __cplusplus
}
#endif

#endif
