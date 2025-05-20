/************************************************************************
 *                DECLARATION OF MODBUS TCP BLOCKS                      *
 ************************************************************************/
// MODBUS_CONNECT
// Data part
typedef struct {
    // FB Interface - IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL,EN)
    __DECLARE_VAR(BOOL,ENO)
    __DECLARE_VAR(BOOL,CONNECT)
    __DECLARE_VAR(STRING,BROKER)
    __DECLARE_VAR(UINT,PORT)
    __DECLARE_VAR(UINT,SLAVE_ID)
    __DECLARE_VAR(BOOL,SUCCESS)
    __DECLARE_VAR(INT,ERROR_CODE)
    
    // FB private variables - TEMP, private and located variables
    
  } MODBUS_CONNECT;
    
  // MODBUS_DISCONNECT
  // Data part
  typedef struct {
    // FB Interface - IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL,EN)
    __DECLARE_VAR(BOOL,ENO)
    __DECLARE_VAR(BOOL,DISCONNECT)
    __DECLARE_VAR(BOOL,SUCCESS)
    __DECLARE_VAR(INT,ERROR_CODE)
  
    // FB private variables - TEMP, private and located variables
  
  } MODBUS_DISCONNECT;
  
  // MODBUS_READ_HOLDING
  // Data part
  typedef struct {
    // FB Interface - IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL,EN)
    __DECLARE_VAR(BOOL,ENO)
    __DECLARE_VAR(BOOL,READ)
    __DECLARE_VAR(UINT,START_ADDRESS)
    __DECLARE_VAR(UINT,QUANTITY)
    __DECLARE_VAR(INT,VALUES)
    __DECLARE_VAR(BOOL,SUCCESS)
    __DECLARE_VAR(INT,ERROR_CODE)
  
    // FB private variables - TEMP, private and located variables
  
  } MODBUS_READ_HOLDING;
  
  // MODBUS_WRITE_REGISTER
  // Data part
  typedef struct {
    // FB Interface - IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL,EN)
    __DECLARE_VAR(BOOL,ENO)
    __DECLARE_VAR(BOOL,WRITE)
    __DECLARE_VAR(UINT,ADDRESS)
    __DECLARE_VAR(INT,VALUE)
    __DECLARE_VAR(BOOL,SUCCESS)
    __DECLARE_VAR(INT,ERROR_CODE)
  
    // FB private variables - TEMP, private and located variables
  
  } MODBUS_WRITE_REGISTER;
  
  // MODBUS_READ_COILS
  // Data part
  typedef struct {
    // FB Interface - IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL,EN)
    __DECLARE_VAR(BOOL,ENO)
    __DECLARE_VAR(BOOL,READ)
    __DECLARE_VAR(UINT,START_ADDRESS)
    __DECLARE_VAR(UINT,QUANTITY)
    __DECLARE_VAR(BOOL,VALUES)
    __DECLARE_VAR(BOOL,SUCCESS)
    __DECLARE_VAR(INT,ERROR_CODE)
  
    // FB private variables - TEMP, private and located variables
  
  } MODBUS_READ_COILS;
  
  // MODBUS_WRITE_COIL
  // Data part
  typedef struct {
    // FB Interface - IN, OUT, IN_OUT variables
    __DECLARE_VAR(BOOL,EN)
    __DECLARE_VAR(BOOL,ENO)
    __DECLARE_VAR(BOOL,WRITE)
    __DECLARE_VAR(UINT,ADDRESS)
    __DECLARE_VAR(BOOL,VALUE)
    __DECLARE_VAR(BOOL,SUCCESS)
    __DECLARE_VAR(INT,ERROR_CODE)
  
    // FB private variables - TEMP, private and located variables
  
  } MODBUS_WRITE_COIL;
  
  
  /************************************************************************
   *                 END OF MODBUS TCP BLOCKS                            *
   ************************************************************************/
  
  /************************************************************************
   *              DECLARATION OF MODBUS TCP LIB FUNCTIONS                *
   ************************************************************************/
  
  // modbus_client.cpp
  int modbus_tcp_connect(uint8_t *broker, uint16_t port, uint16_t slave_id);
  int modbus_disconnect(int connection_id);
  int modbus_read_holding_registers(int connection_id, uint16_t start_address, uint16_t quantity, uint16_t *values);
  int modbus_write_single_register(int connection_id, uint16_t address, uint16_t value);
  int modbus_read_coils(int connection_id, uint16_t start_address, uint16_t quantity, uint8_t *values);
  int modbus_write_single_coil(int connection_id, uint16_t address, uint8_t value);
  
  /************************************************************************
   *              IMPLEMENTATION OF MODBUS TCP BLOCKS                    *
   ************************************************************************/
  
  // MODBUS_CONNECT
  static void MODBUS_CONNECT_init__(MODBUS_CONNECT *data__, BOOL retain) {
    __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->CONNECT,0,retain)
    __INIT_VAR(data__->BROKER,__STRING_LITERAL(0,""),retain)
    __INIT_VAR(data__->PORT,0,retain)
    __INIT_VAR(data__->SLAVE_ID,0,retain)
    __INIT_VAR(data__->SUCCESS,0,retain)
    __INIT_VAR(data__->ERROR_CODE,0,retain)
  }
  
  // Code part
  static void MODBUS_CONNECT_body__(MODBUS_CONNECT *data__) {
    // Control execution
    if (!__GET_VAR(data__->EN)) {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
      return;
    }
    else {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
    }
    // Block code
    if (__GET_VAR(data__->CONNECT)) {
      #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
      #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
  
      IEC_STRING broker = GetFbVar(BROKER);
      uint16_t port = GetFbVar(PORT);
      uint16_t slave_id = GetFbVar(SLAVE_ID);
  
      int result = modbus_tcp_connect(broker.body, port, slave_id);
      SetFbVar(SUCCESS, result >= 0);
      SetFbVar(ERROR_CODE, result < 0 ? result : 0);
      if (result < 0) {
        SetFbVar(ENO, __BOOL_LITERAL(FALSE));
      }
  
      #undef GetFbVar
      #undef SetFbVar
    }
  
    goto __end;
  
  __end:
    return;
  } // MODBUS_CONNECT_body__()
  
  // MODBUS_DISCONNECT
  static void MODBUS_DISCONNECT_init__(MODBUS_DISCONNECT *data__, BOOL retain) {
    __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->DISCONNECT,0,retain)
    __INIT_VAR(data__->SUCCESS,0,retain)
    __INIT_VAR(data__->ERROR_CODE,0,retain)
  }
  
  // Code part
  static void MODBUS_DISCONNECT_body__(MODBUS_DISCONNECT *data__) {
    // Control execution
    if (!__GET_VAR(data__->EN)) {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
      return;
    }
    else {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
    }
    // Block code
    if (__GET_VAR(data__->DISCONNECT)) {
      #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
      #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
  
      int result = modbus_disconnect(0); // Connection ID managed internally
      SetFbVar(SUCCESS, result >= 0);
      SetFbVar(ERROR_CODE, result < 0 ? result : 0);
      if (result < 0) {
        SetFbVar(ENO, __BOOL_LITERAL(FALSE));
      }
  
      #undef GetFbVar
      #undef SetFbVar
    }
  
    goto __end;
  
  __end:
    return;
  } // MODBUS_DISCONNECT_body__()
  
  // MODBUS_READ_HOLDING
  static void MODBUS_READ_HOLDING_init__(MODBUS_READ_HOLDING *data__, BOOL retain) {
    __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->READ,0,retain)
    __INIT_VAR(data__->START_ADDRESS,0,retain)
    __INIT_VAR(data__->QUANTITY,0,retain)
    __INIT_VAR(data__->VALUES,0,retain)
    __INIT_VAR(data__->SUCCESS,0,retain)
    __INIT_VAR(data__->ERROR_CODE,0,retain)
  }
  
  // Code part
  static void MODBUS_READ_HOLDING_body__(MODBUS_READ_HOLDING *data__) {
    // Control execution
    if (!__GET_VAR(data__->EN)) {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
      return;
    }
    else {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
    }
    // Block code
    if (__GET_VAR(data__->READ)) {
      #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
      #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
  
      uint16_t start_addr = GetFbVar(START_ADDRESS);
      uint16_t quantity = GetFbVar(QUANTITY);
      uint16_t values[125]; // Max 125 registers per Modbus TCP read
  
      int result = modbus_read_holding_registers(0, start_addr, quantity, values);
      if (result >= 0) {
        SetFbVar(VALUES, values[0]); // Simplified: assumes single value
        SetFbVar(SUCCESS, __BOOL_LITERAL(TRUE));
        SetFbVar(ERROR_CODE, 0);
      } else {
        SetFbVar(SUCCESS, __BOOL_LITERAL(FALSE));
        SetFbVar(ERROR_CODE, result);
        SetFbVar(ENO, __BOOL_LITERAL(FALSE));
      }
  
      #undef GetFbVar
      #undef SetFbVar
    }
  
    goto __end;
  
  __end:
    return;
  } // MODBUS_READ_HOLDING_body__()
  
  // MODBUS_WRITE_REGISTER
  static void MODBUS_WRITE_REGISTER_init__(MODBUS_WRITE_REGISTER *data__, BOOL retain) {
    __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->WRITE,0,retain)
    __INIT_VAR(data__->ADDRESS,0,retain)
    __INIT_VAR(data__->VALUE,0,retain)
    __INIT_VAR(data__->SUCCESS,0,retain)
    __INIT_VAR(data__->ERROR_CODE,0,retain)
  }
  
  // Code part
  static void MODBUS_WRITE_REGISTER_body__(MODBUS_WRITE_REGISTER *data__) {
    // Control execution
    if (!__GET_VAR(data__->EN)) {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
      return;
    }
    else {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
    }
    // Block code
    if (__GET_VAR(data__->WRITE)) {
      #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
      #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
  
      uint16_t addr = GetFbVar(ADDRESS);
      uint16_t value = GetFbVar(VALUE);
  
      int result = modbus_write_single_register(0, addr, value);
      SetFbVar(SUCCESS, result >= 0);
      SetFbVar(ERROR_CODE, result < 0 ? result : 0);
      if (result < 0) {
        SetFbVar(ENO, __BOOL_LITERAL(FALSE));
      }
  
      #undef GetFbVar
      #undef SetFbVar
    }
  
    goto __end;
  
  __end:
    return;
  } // MODBUS_WRITE_REGISTER_body__()
  
  // MODBUS_READ_COILS
  static void MODBUS_READ_COILS_init__(MODBUS_READ_COILS *data__, BOOL retain) {
    __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->READ,0,retain)
    __INIT_VAR(data__->START_ADDRESS,0,retain)
    __INIT_VAR(data__->QUANTITY,0,retain)
    __INIT_VAR(data__->VALUES,0,retain)
    __INIT_VAR(data__->SUCCESS,0,retain)
    __INIT_VAR(data__->ERROR_CODE,0,retain)
  }
  
  // Code part
  static void MODBUS_READ_COILS_body__(MODBUS_READ_COILS *data__) {
    // Control execution
    if (!__GET_VAR(data__->EN)) {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
      return;
    }
    else {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
    }
    // Block code
    if (__GET_VAR(data__->READ)) {
      #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
      #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
  
      uint16_t start_addr = GetFbVar(START_ADDRESS);
      uint16_t quantity = GetFbVar(QUANTITY);
      uint8_t values[2000]; // Max 2000 coils per Modbus TCP read
  
      int result = modbus_read_coils(0, start_addr, quantity, values);
      if (result >= 0) {
        SetFbVar(VALUES, values[0]); // Simplified: assumes single value
        SetFbVar(SUCCESS, __BOOL_LITERAL(TRUE));
        SetFbVar(ERROR_CODE, 0);
      } else {
        SetFbVar(SUCCESS, __BOOL_LITERAL(FALSE));
        SetFbVar(ERROR_CODE, result);
        SetFbVar(ENO, __BOOL_LITERAL(FALSE));
      }
  
      #undef GetFbVar
      #undef SetFbVar
    }
  
    goto __end;
  
  __end:
    return;
  } // MODBUS_READ_COILS_body__()
  
  // MODBUS_WRITE_COIL
  static void MODBUS_WRITE_COIL_init__(MODBUS_WRITE_COIL *data__, BOOL retain) {
    __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
    __INIT_VAR(data__->WRITE,0,retain)
    __INIT_VAR(data__->ADDRESS,0,retain)
    __INIT_VAR(data__->VALUE,0,retain)
    __INIT_VAR(data__->SUCCESS,0,retain)
    __INIT_VAR(data__->ERROR_CODE,0,retain)
  }
  
  // Code part
  static void MODBUS_WRITE_COIL_body__(MODBUS_WRITE_COIL *data__) {
    // Control execution
    if (!__GET_VAR(data__->EN)) {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
      return;
    }
    else {
      __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
    }
    // Block code
    if (__GET_VAR(data__->WRITE)) {
      #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
      #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
  
      uint16_t addr = GetFbVar(ADDRESS);
      uint8_t value = GetFbVar(VALUE);
  
      int result = modbus_write_single_coil(0, addr, value);
      SetFbVar(SUCCESS, result >= 0);
      SetFbVar(ERROR_CODE, result < 0 ? result : 0);
      if (result < 0) {
        SetFbVar(ENO, __BOOL_LITERAL(FALSE));
      }
  
      #undef GetFbVar
      #undef SetFbVar
    }
  
    goto __end;
  
  __end:
    return;
  } // MODBUS_WRITE_COIL_body__()
  
  /************************************************************************
   *                  END OF MODBUS TCP LIB BLOCK                       *
   ************************************************************************/