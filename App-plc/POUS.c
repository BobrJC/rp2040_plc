void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void PROGRAM0_init__(PROGRAM0 *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__MX0_0_2_13,data__->LOCALVAR0,retain)
  __INIT_LOCATED_VALUE(data__->LOCALVAR0,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->T_1S,__time_to_timespec(1, 0, 1, 0, 0, 0),retain)
  TON_init__(&data__->TON0,retain);
  TOF_init__(&data__->TOF0,retain);
  __INIT_VAR(data__->_TMP_NOT1_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PROGRAM0_body__(PROGRAM0 *data__) {
  // Initialise TEMP variables
  printf("LOCALVARE0 %i", __GET_LOCATED(data__->LOCALVAR0,));

  __SET_VAR(data__->,_TMP_NOT1_OUT,,!(__GET_LOCATED(data__->LOCALVAR0,)));
  __SET_VAR(data__->TON0.,IN,,__GET_VAR(data__->_TMP_NOT1_OUT,));
  __SET_VAR(data__->TON0.,PT,,__GET_VAR(data__->T_1S,));
  TON_body__(&data__->TON0);
  __SET_VAR(data__->TOF0.,IN,,__GET_VAR(data__->TON0.Q,));
  __SET_VAR(data__->TOF0.,PT,,__GET_VAR(data__->T_1S,));
  TOF_body__(&data__->TOF0);
  __SET_LOCATED(data__->,LOCALVAR0,,__GET_VAR(data__->TOF0.Q,));

  goto __end;

__end:
  return;
} // PROGRAM0_body__() 





