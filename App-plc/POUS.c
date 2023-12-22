void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain) {
  __INIT_LOCATED(REAL,__MD1_0,data__->CEL,retain)
  __INIT_LOCATED_VALUE(data__->CEL,0)
  __INIT_LOCATED(REAL,__MD1_1,data__->FAR1,retain)
  __INIT_LOCATED_VALUE(data__->FAR1,0)
  __INIT_VAR(data__->LOCALVAR1,9.0,retain)
  __INIT_VAR(data__->LOCALVAR2,0.2,retain)
  __INIT_VAR(data__->LOCALVAR3,32.0,retain)
  __INIT_LOCATED(REAL,__MD0_1,data__->FAR_FROM_PAIR,retain)
  __INIT_LOCATED_VALUE(data__->FAR_FROM_PAIR,0)
  __INIT_LOCATED(BOOL,__MX1_1,data__->RES,retain)
  __INIT_LOCATED_VALUE(data__->RES,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->_TMP_LE10_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_MUL1_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL2_OUT,0,retain)
  __INIT_VAR(data__->_TMP_ADD3_OUT,0,retain)
}

// Code part
void PROGRAM0_body__(PROGRAM0 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_LE10_OUT,,LE__BOOL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_LOCATED(data__->FAR_FROM_PAIR,),
    (REAL)__GET_LOCATED(data__->FAR1,)));
    printf("FAR_FROM_PAIR  %f\n", __GET_LOCATED(data__->FAR_FROM_PAIR,));
  __SET_LOCATED(data__->,RES,,__GET_VAR(data__->_TMP_LE10_OUT,));
  __SET_VAR(data__->,_TMP_MUL1_OUT,,MUL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_LOCATED(data__->CEL,),
    (REAL)__GET_VAR(data__->LOCALVAR1,)));
  __SET_VAR(data__->,_TMP_MUL2_OUT,,MUL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->_TMP_MUL1_OUT,),
    (REAL)__GET_VAR(data__->LOCALVAR2,)));
  __SET_VAR(data__->,_TMP_ADD3_OUT,,ADD__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->_TMP_MUL2_OUT,),
    (REAL)__GET_VAR(data__->LOCALVAR3,)));
    printf("prog0 add_out %f\n", __GET_VAR(data__->_TMP_ADD3_OUT,));
  __SET_LOCATED(data__->,FAR1,,__GET_VAR(data__->_TMP_ADD3_OUT,));

  goto __end;

__end:
  return;
} // PROGRAM0_body__() 





void PROGRAM1_init__(PROGRAM1 *data__, BOOL retain) {
  __INIT_LOCATED(REAL,__MD0_0,data__->CEL,retain)
  __INIT_LOCATED_VALUE(data__->CEL,0)
  __INIT_VAR(data__->LOCALVAR1,9.0,retain)
  __INIT_VAR(data__->LOCALVAR2,0.2,retain)
  __INIT_VAR(data__->LOCALVAR3,32.0,retain)
  __INIT_LOCATED(REAL,__MD0_1,data__->FAR,retain)
  __INIT_LOCATED_VALUE(data__->FAR,0)
  __INIT_VAR(data__->_TMP_MUL1_OUT,0,retain)
  __INIT_VAR(data__->_TMP_MUL2_OUT,0,retain)
  __INIT_VAR(data__->_TMP_ADD3_OUT,0,retain)
}

// Code part
void PROGRAM1_body__(PROGRAM1 *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_MUL1_OUT,,MUL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_LOCATED(data__->CEL,),
    (REAL)__GET_VAR(data__->LOCALVAR1,)));
    printf("CEL %f\n", __GET_LOCATED(data__->CEL,));
  __SET_VAR(data__->,_TMP_MUL2_OUT,,MUL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->_TMP_MUL1_OUT,),
    (REAL)__GET_VAR(data__->LOCALVAR2,)));
  __SET_VAR(data__->,_TMP_ADD3_OUT,,ADD__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->_TMP_MUL2_OUT,),
    (REAL)__GET_VAR(data__->LOCALVAR3,)));
    printf("prog1 add_out %f\n", __GET_VAR(data__->_TMP_ADD3_OUT,));

  __SET_LOCATED(data__->,FAR,,__GET_VAR(data__->_TMP_ADD3_OUT,));

  goto __end;

__end:
  return;
} // PROGRAM1_body__() 





