#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"
#include <stdio.h>
// PROGRAM PROGRAM0
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_LOCATED(REAL,CEL)
  __DECLARE_LOCATED(REAL,FAR1)
  __DECLARE_VAR(REAL,LOCALVAR1)
  __DECLARE_VAR(REAL,LOCALVAR2)
  __DECLARE_VAR(REAL,LOCALVAR3)
  __DECLARE_LOCATED(REAL,FAR_FROM_PAIR)
  __DECLARE_LOCATED(BOOL,RES)
  __DECLARE_VAR(BOOL,_TMP_LE10_OUT)
  __DECLARE_VAR(REAL,_TMP_MUL1_OUT)
  __DECLARE_VAR(REAL,_TMP_MUL2_OUT)
  __DECLARE_VAR(REAL,_TMP_ADD3_OUT)

} PROGRAM0;

void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain);
// Code part
void PROGRAM0_body__(PROGRAM0 *data__);
// PROGRAM PROGRAM1
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_LOCATED(REAL,CEL)
  __DECLARE_VAR(REAL,LOCALVAR1)
  __DECLARE_VAR(REAL,LOCALVAR2)
  __DECLARE_VAR(REAL,LOCALVAR3)
  __DECLARE_LOCATED(REAL,FAR)
  __DECLARE_VAR(REAL,_TMP_MUL1_OUT)
  __DECLARE_VAR(REAL,_TMP_MUL2_OUT)
  __DECLARE_VAR(REAL,_TMP_ADD3_OUT)

} PROGRAM1;

void PROGRAM1_init__(PROGRAM1 *data__, BOOL retain);
// Code part
void PROGRAM1_body__(PROGRAM1 *data__);
#endif //__POUS_H
