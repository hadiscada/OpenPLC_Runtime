
/************************************************************************
 *                DECLARATION OF S7 BLOCKS                              *
 ************************************************************************/

 #ifndef S7_H
 #define S7_H
 
 #ifndef __cplusplus
 #error "This file must be compiled with a C++ compiler"
 #endif
 
 #include "../../core/oplc_snap7.h"
 
 // S7_CONNECT
 typedef struct {
     __DECLARE_VAR(BOOL, EN)
     __DECLARE_VAR(BOOL, ENO)
     __DECLARE_VAR(BOOL, CONNECT)
     __DECLARE_VAR(STRING, IP_ADDRESS)
     __DECLARE_VAR(INT, RACK)
     __DECLARE_VAR(INT, SLOT)
     __DECLARE_VAR(BOOL, SUCCESS)
     __DECLARE_VAR(INT, ERROR_CODE)
     TS7Client* client;
 } S7_CONNECT;
 
 // S7_DISCONNECT
 typedef struct {
     __DECLARE_VAR(BOOL, EN)
     __DECLARE_VAR(BOOL, ENO)
     __DECLARE_VAR(BOOL, DISCONNECT)
     __DECLARE_VAR(BOOL, SUCCESS)
     __DECLARE_VAR(INT, ERROR_CODE)
     TS7Client* client;
 } S7_DISCONNECT;
 
 // S7_READ_BIT
 typedef struct {
     __DECLARE_VAR(BOOL, EN)
     __DECLARE_VAR(BOOL, ENO)
     __DECLARE_VAR(BOOL, READ)
     __DECLARE_VAR(INT, DB_NUMBER)
     __DECLARE_VAR(INT, ADDRESS)
     __DECLARE_VAR(INT, BIT_OFFSET)
     __DECLARE_VAR(BOOL, VALUE)
     __DECLARE_VAR(BOOL, SUCCESS)
     __DECLARE_VAR(INT, ERROR_CODE)
     TS7Client* client;
 } S7_READ_BIT;
 
 // S7_READ_BYTE
 typedef struct {
     __DECLARE_VAR(BOOL, EN)
     __DECLARE_VAR(BOOL, ENO)
     __DECLARE_VAR(BOOL, READ)
     __DECLARE_VAR(INT, DB_NUMBER)
     __DECLARE_VAR(INT, ADDRESS)
     __DECLARE_VAR(BYTE, VALUE)
     __DECLARE_VAR(BOOL, SUCCESS)
     __DECLARE_VAR(INT, ERROR_CODE)
     TS7Client* client;
 } S7_READ_BYTE;
 
 // S7_READ_WORD
 typedef struct {
     __DECLARE_VAR(BOOL, EN)
     __DECLARE_VAR(BOOL, ENO)
     __DECLARE_VAR(BOOL, READ)
     __DECLARE_VAR(INT, DB_NUMBER)
     __DECLARE_VAR(INT, ADDRESS)
     __DECLARE_VAR(WORD, VALUE)
     __DECLARE_VAR(BOOL, SUCCESS)
     __DECLARE_VAR(INT, ERROR_CODE)
     TS7Client* client;
 } S7_READ_WORD;
 
 /************************************************************************
  *                 END OF S7 BLOCKS                                    *
  ************************************************************************/
 
 /************************************************************************
  *              DECLARATION OF S7 LIB FUNCTIONS                        *
  ************************************************************************/
 
 int s7_connect(const char* ip_address, int rack, int slot, TS7Client* client);
 int s7_disconnect(TS7Client* client);
 int s7_read_bit(TS7Client* client, int db_number, int address, int bit_offset, bool* value, bool* success, int* error_code);
 int s7_read_byte(TS7Client* client, int db_number, int address, byte* value, bool* success, int* error_code);
 int s7_read_word(TS7Client* client, int db_number, int address, word* value, bool* success, int* error_code);
 
 /************************************************************************
  *              IMPLEMENTATION OF S7 BLOCKS                            *
  ************************************************************************/
 
 // S7_CONNECT
 static void S7_CONNECT_init__(S7_CONNECT *data__, BOOL retain) {
     __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->CONNECT, 0, retain)
     __INIT_VAR(data__->IP_ADDRESS, __STRING_LITERAL(0, ""), retain)
     __INIT_VAR(data__->RACK, 0, retain)
     __INIT_VAR(data__->SLOT, 0, retain)
     __INIT_VAR(data__->SUCCESS, 0, retain)
     __INIT_VAR(data__->ERROR_CODE, 0, retain)
     data__->client = NULL;
 }
 
 static void S7_CONNECT_body__(S7_CONNECT *data__) {
     if (!__GET_VAR(data__->EN)) {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(FALSE));
         return;
     } else {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(TRUE));
     }
     if (__GET_VAR(data__->CONNECT)) {
         #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
         #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
 
         IEC_STRING ip_addr = GetFbVar(IP_ADDRESS);
         int rack = GetFbVar(RACK);
         int slot = GetFbVar(SLOT);
 
         if (data__->client == NULL) {
             data__->client = new TS7Client();
         }
 
         int result = s7_connect(reinterpret_cast<const char*>(ip_addr.body), rack, slot, data__->client);
         SetFbVar(SUCCESS, result == 0);
         SetFbVar(ERROR_CODE, result);
         if (result != 0) {
             SetFbVar(ENO, __BOOL_LITERAL(FALSE));
         }
 
         #undef GetFbVar
         #undef SetFbVar
     }
 
     goto __end;
 
 __end:
     return;
 }
 
 // S7_DISCONNECT
 static void S7_DISCONNECT_init__(S7_DISCONNECT *data__, BOOL retain) {
     __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->DISCONNECT, 0, retain)
     __INIT_VAR(data__->SUCCESS, 0, retain)
     __INIT_VAR(data__->ERROR_CODE, 0, retain)
     data__->client = NULL;
 }
 
 static void S7_DISCONNECT_body__(S7_DISCONNECT *data__) {
     if (!__GET_VAR(data__->EN)) {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(FALSE));
         return;
     } else {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(TRUE));
     }
     if (__GET_VAR(data__->DISCONNECT)) {
         #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
         #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
 
         int result = s7_disconnect(data__->client);
         SetFbVar(SUCCESS, result == 0);
         SetFbVar(ERROR_CODE, result);
         if (result != 0) {
             SetFbVar(ENO, __BOOL_LITERAL(FALSE));
         }
         if (data__->client != NULL) {
             delete data__->client;
             data__->client = NULL;
         }
 
         #undef GetFbVar
         #undef SetFbVar
     }
 
     goto __end;
 
 __end:
     return;
 }
 
 // S7_READ_BIT
 static void S7_READ_BIT_init__(S7_READ_BIT *data__, BOOL retain) {
     __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->READ, 0, retain)
     __INIT_VAR(data__->DB_NUMBER, 0, retain)
     __INIT_VAR(data__->ADDRESS, 0, retain)
     __INIT_VAR(data__->BIT_OFFSET, 0, retain)
     __INIT_VAR(data__->VALUE, 0, retain)
     __INIT_VAR(data__->SUCCESS, 0, retain)
     __INIT_VAR(data__->ERROR_CODE, 0, retain)
     data__->client = NULL;
 }
 
 static void S7_READ_BIT_body__(S7_READ_BIT *data__) {
     if (!__GET_VAR(data__->EN)) {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(FALSE));
         return;
     } else {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(TRUE));
     }
     if (__GET_VAR(data__->READ)) {
         #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
         #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
 
         int db_num = GetFbVar(DB_NUMBER);
         int address = GetFbVar(ADDRESS);
         int bit_offset = GetFbVar(BIT_OFFSET);
         if (bit_offset < 0 || bit_offset > 7) {
             SetFbVar(SUCCESS, 0);
             SetFbVar(ERROR_CODE, errCliInvalidParams);
             SetFbVar(ENO, __BOOL_LITERAL(FALSE));
             return;
         }
 
         bool value;
         bool success;
         int error_code;
         int result = s7_read_bit(data__->client, db_num, address, bit_offset, &value, &success, &error_code);
         SetFbVar(VALUE, value);
         SetFbVar(SUCCESS, success);
         SetFbVar(ERROR_CODE, error_code);
         if (result != 0) {
             SetFbVar(ENO, __BOOL_LITERAL(FALSE));
         }
 
         #undef GetFbVar
         #undef SetFbVar
     }
 
     goto __end;
 
 __end:
     return;
 }
 
 // S7_READ_BYTE
 static void S7_READ_BYTE_init__(S7_READ_BYTE *data__, BOOL retain) {
     __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->READ, 0, retain)
     __INIT_VAR(data__->DB_NUMBER, 0, retain)
     __INIT_VAR(data__->ADDRESS, 0, retain)
     __INIT_VAR(data__->VALUE, 0, retain)
     __INIT_VAR(data__->SUCCESS, 0, retain)
     __INIT_VAR(data__->ERROR_CODE, 0, retain)
     data__->client = NULL;
 }
 
 static void S7_READ_BYTE_body__(S7_READ_BYTE *data__) {
     if (!__GET_VAR(data__->EN)) {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(FALSE));
         return;
     } else {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(TRUE));
     }
     if (__GET_VAR(data__->READ)) {
         #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
         #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
 
         int db_num = GetFbVar(DB_NUMBER);
         int address = GetFbVar(ADDRESS);
 
         byte value;
         bool success;
         int error_code;
         int result = s7_read_byte(data__->client, db_num, address, &value, &success, &error_code);
         SetFbVar(VALUE, value);
         SetFbVar(SUCCESS, success);
         SetFbVar(ERROR_CODE, error_code);
         if (result != 0) {
             SetFbVar(ENO, __BOOL_LITERAL(FALSE));
         }
 
         #undef GetFbVar
         #undef SetFbVar
     }
 
     goto __end;
 
 __end:
     return;
 }
 
 // S7_READ_WORD
 static void S7_READ_WORD_init__(S7_READ_WORD *data__, BOOL retain) {
     __INIT_VAR(data__->EN, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->ENO, __BOOL_LITERAL(TRUE), retain)
     __INIT_VAR(data__->READ, 0, retain)
     __INIT_VAR(data__->DB_NUMBER, 0, retain)
     __INIT_VAR(data__->ADDRESS, 0, retain)
     __INIT_VAR(data__->VALUE, 0, retain)
     __INIT_VAR(data__->SUCCESS, 0, retain)
     __INIT_VAR(data__->ERROR_CODE, 0, retain)
     data__->client = NULL;
 }
 
 static void S7_READ_WORD_body__(S7_READ_WORD *data__) {
     if (!__GET_VAR(data__->EN)) {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(FALSE));
         return;
     } else {
         __SET_VAR(data__->, ENO, , __BOOL_LITERAL(TRUE));
     }
     if (__GET_VAR(data__->READ)) {
         #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
         #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
 
         int db_num = GetFbVar(DB_NUMBER);
         int address = GetFbVar(ADDRESS);
 
         word value;
         bool success;
         int error_code;
         int result = s7_read_word(data__->client, db_num, address, &value, &success, &error_code);
         SetFbVar(VALUE, value);
         SetFbVar(SUCCESS, success);
         SetFbVar(ERROR_CODE, error_code);
         if (result != 0) {
             SetFbVar(ENO, __BOOL_LITERAL(FALSE));
         }
 
         #undef GetFbVar
         #undef SetFbVar
     }
 
     goto __end;
 
 __end:
     return;
 }
 
 /************************************************************************
  *                  END OF S7 LIB BLOCK                                *
  ************************************************************************/
 
 #endif // S7_H
 