void MAIN_init__(MAIN *data__, BOOL retain) {
  __INIT_LOCATED(INT,__QW0,data__->REG1,retain)
  __INIT_LOCATED_VALUE(data__->REG1,0)
  __INIT_LOCATED(INT,__QW1,data__->REG2,retain)
  __INIT_LOCATED_VALUE(data__->REG2,0)
  __INIT_LOCATED(INT,__QW2,data__->REG3,retain)
  __INIT_LOCATED_VALUE(data__->REG3,0)
  __INIT_VAR(data__->_TMP_ADD5467317_OUT,0,retain)
}

// Code part
void MAIN_body__(MAIN *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,_TMP_ADD5467317_OUT,,ADD__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_LOCATED(data__->REG1,),
    (INT)__GET_LOCATED(data__->REG2,)));
  __SET_LOCATED(data__->,REG3,,__GET_VAR(data__->_TMP_ADD5467317_OUT,));

  goto __end;

__end:
  return;
} // MAIN_body__() 





