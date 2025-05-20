PROGRAM main
  VAR
    read : BOOL := true;
    rack : INT := 0;
    slot : INT := 1;
    ip : STRING := '192.168.1.10';
    db : INT := 1;
    start : INT := 1;
    qty : INT := 1;
    S7_CONNECT0 : S7_CONNECT;
    S7_READ_WORD0 : S7_READ_WORD;
  END_VAR
  VAR
    con_ok AT %QX0.0 : BOOL;
    read_ok AT %QX0.1 : BOOL;
    read_val AT %QW1 : WORD;
  END_VAR

  S7_CONNECT0(CONNECT := NOT(con_ok), IP_ADDRESS := ip, RACK := rack, SLOT := slot);
  con_ok := S7_CONNECT0.SUCCESS;
  S7_READ_WORD0(EN := con_ok, READ := con_ok, DB_NUMBER := db, ADDRESS := start);
  IF S7_READ_WORD0.ENO THEN
      read_val := S7_READ_WORD0.VALUE;
  END_IF;
  IF S7_READ_WORD0.ENO THEN
      read_ok := S7_READ_WORD0.SUCCESS;
  END_IF;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 1);
    PROGRAM instance0 WITH task0 : main;
  END_RESOURCE
END_CONFIGURATION
