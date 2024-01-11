PROGRAM program0
  VAR
    cel_0 AT %MD1.0 : REAL;
    far1 AT %MD1.1 : REAL;
  END_VAR
  VAR CONSTANT
    LocalVar1 : REAL := 9.0;
    LocalVar2 : REAL := 0.2;
    LocalVar3 : REAL := 32.0;
  END_VAR
  VAR
    far_from_pair AT %MD0.1 : REAL;
    res AT %MX1.1 : BOOL;
  END_VAR
  VAR
    _TMP_LE10_OUT : BOOL;
    _TMP_MUL1_OUT : REAL;
    _TMP_MUL2_OUT : REAL;
    _TMP_ADD3_OUT : REAL;
  END_VAR

  _TMP_LE10_OUT := LE(far_from_pair, far1);
  res := _TMP_LE10_OUT;
  _TMP_MUL1_OUT := MUL(cel_0, LocalVar1);
  _TMP_MUL2_OUT := MUL(_TMP_MUL1_OUT, LocalVar2);
  _TMP_ADD3_OUT := ADD(_TMP_MUL2_OUT, LocalVar3);
  far1 := _TMP_ADD3_OUT;
END_PROGRAM

PROGRAM program1
  VAR
    cel_1 AT %MD0.0 : REAL;
  END_VAR
  VAR CONSTANT
    LocalVar1 : REAL := 9.0;
    LocalVar2 : REAL := 0.2;
    LocalVar3 : REAL := 32.0;
  END_VAR
  VAR
    far AT %MD0.1 : REAL;
  END_VAR
  VAR
    _TMP_MUL1_OUT : REAL;
    _TMP_MUL2_OUT : REAL;
    _TMP_ADD3_OUT : REAL;
  END_VAR

  _TMP_MUL1_OUT := MUL(cel_1, LocalVar1);
  _TMP_MUL2_OUT := MUL(_TMP_MUL1_OUT, LocalVar2);
  _TMP_ADD3_OUT := ADD(_TMP_MUL2_OUT, LocalVar3);
  far := _TMP_ADD3_OUT;
END_PROGRAM


CONFIGURATION config

  RESOURCE resource1 ON PLC
    TASK task1(INTERVAL := T#20ms,PRIORITY := 7);
    PROGRAM instance1 WITH task1 : program1;
  END_RESOURCE

  RESOURCE resource0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 7);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
