PROGRAM program0
  VAR
    LocalVar0 AT %MX0.0 : BOOL;
  END_VAR
  VAR
    LocalVar1 : BOOL;
  END_VAR

  LocalVar1 := LocalVar0;
END_PROGRAM


CONFIGURATION config

  RESOURCE resource1 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : program0;
  END_RESOURCE
END_CONFIGURATION
