
PROGRAM program1
  VAR
    cel : REAL;
  END_VAR
  VAR CONSTANT
    LocalVar1 : REAL := 9.0;
    LocalVar2 : REAL := 0.2;
    LocalVar3 : REAL := 32.0;
  END_VAR
  VAR
    far_from_pair AT %MD0.1 : REAL;
    res AT %MX0.0 : BOOL;
  END_VAR
  VAR
    _TMP_MUL1_OUT : REAL;
    _TMP_MUL2_OUT : REAL;
    _TMP_ADD3_OUT : REAL;
    _TMP_LE10_OUT : BOOL;
  END_VAR

  _TMP_MUL1_OUT := MUL(cel, LocalVar1);
  _TMP_MUL2_OUT := MUL(_TMP_MUL1_OUT, LocalVar2);
  _TMP_ADD3_OUT := ADD(_TMP_MUL2_OUT, LocalVar3);
  _TMP_LE10_OUT := LE(far_from_pair, _TMP_ADD3_OUT);
  res := _TMP_LE10_OUT;
END_PROGRAM


CONFIGURATION config

  RESOURCE resource2 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task1 : program1;
  END_RESOURCE
END_CONFIGURATION
