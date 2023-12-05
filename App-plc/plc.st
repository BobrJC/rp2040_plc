TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  TRIG0:=TRIG;
END_FUNCTION_BLOCK


PROGRAM program0
  VAR
    LocalVar0 AT %MX0.0.2.13 : BOOL;
  END_VAR
  VAR CONSTANT
    t_1s : TIME := t#1s;
  END_VAR
  VAR
    TON0 : TON;
    TOF0 : TOF;
    _TMP_NOT1_OUT : BOOL;
  END_VAR

  _TMP_NOT1_OUT := NOT(LocalVar0);
  TON0(IN := _TMP_NOT1_OUT, PT := t_1s);
  TOF0(IN := TON0.Q, PT := t_1s);
  LocalVar0 := TOF0.Q;
END_PROGRAM


CONFIGURATION config

  RESOURCE resource1 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION