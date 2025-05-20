/************************************************************************
 *                MODBUS TCP CLIENT IMPLEMENTATION                     *
 ************************************************************************/

 #include <modbus.h>
 #include <string.h>
 #include <stdio.h>
 #include <errno.h>
 
 #include "ladder.h"
 
 // Static context for managing single connection
 static modbus_t *modbus_ctx = NULL;
 
 /************************************************************************
 * FUNCTION: modbus_tcp_connect                                        *
 *                                                                    *
 * Connects to a Modbus TCP server at the specified broker address and *
 * port with a given slave ID.                                        *
 *                                                                    *
 * Parameters:                                                        *
 *   broker: IP address of the Modbus server (null-terminated string)  *
 *   port: TCP port (typically 502)                                   *
 *   slave_id: Modbus slave ID (1-247)                                *
 * Returns:                                                           *
 *   0 on success, negative value on failure                          *
 ************************************************************************/
 int modbus_tcp_connect(uint8_t *broker, uint16_t port, uint16_t slave_id)
 {
   char log_msg[1000];
 
   // Check if already connected
   if (modbus_ctx != NULL)
   {
     modbus_close(modbus_ctx);
     modbus_free(modbus_ctx);
     modbus_ctx = NULL;
   }
 
   // Create new Modbus context
   modbus_ctx = modbus_new_tcp((char *)broker, port);
   if (modbus_ctx == NULL)
   {
     sprintf(log_msg, "Modbus Client: error creating Modbus context => %s\n",
             strerror(errno));
     log(log_msg);
     return -1;
   }
 
   // Set slave ID
   if (modbus_set_slave(modbus_ctx, slave_id) < 0)
   {
     sprintf(log_msg, "Modbus Client: error setting slave ID => %s\n",
             strerror(errno));
     log(log_msg);
     modbus_free(modbus_ctx);
     modbus_ctx = NULL;
     return -2;
   }
 
   // Establish connection
   if (modbus_connect(modbus_ctx) < 0)
   {
     sprintf(log_msg, "Modbus Client: error connecting to server => %s\n",
             strerror(errno));
     log(log_msg);
     modbus_free(modbus_ctx);
     modbus_ctx = NULL;
     return -3;
   }
 
   return 0;
 }
 
 /************************************************************************
 * FUNCTION: modbus_disconnect                                         *
 *                                                                    *
 * Disconnects from the current Modbus TCP server.                    *
 *                                                                    *
 * Parameters:                                                        *
 *   connection_id: Ignored (managed internally)                      *
 * Returns:                                                           *
 *   0 on success, negative value on failure                          *
 ************************************************************************/
 int modbus_disconnect(int connection_id)
 {
   char log_msg[1000];
 
   if (modbus_ctx == NULL)
   {
     sprintf(log_msg, "Modbus Client: no active connection\n");
     log(log_msg);
     return -1;
   }
 
   modbus_close(modbus_ctx);
   modbus_free(modbus_ctx);
   modbus_ctx = NULL;
 
   return 0;
 }
 
 /************************************************************************
 * FUNCTION: modbus_read_holding_registers                             *
 *                                                                    *
 * Reads a specified number of holding registers from the Modbus       *
 * server.                                                            *
 *                                                                    *
 * Parameters:                                                        *
 *   connection_id: Ignored (managed internally)                      *
 *   start_address: Starting address of registers (0-65535)           *
 *   quantity: Number of registers to read (1-125)                    *
 *   values: Buffer to store read values                              *
 * Returns:                                                           *
 *   Number of registers read on success, negative value on failure   *
 ************************************************************************/
 int modbus_read_holding_registers(int connection_id, uint16_t start_address,
                                   uint16_t quantity, uint16_t *values)
 {
   char log_msg[1000];
   int result;
 
   if (modbus_ctx == NULL)
   {
     sprintf(log_msg, "Modbus Client: no active connection for reading "
                     "registers\n");
     log(log_msg);
     return -1;
   }
 
   if (quantity < 1 || quantity > 125)
   {
     sprintf(log_msg, "Modbus Client: invalid quantity for reading registers "
                     "(%d)\n", quantity);
     log(log_msg);
     return -2;
   }
 
   result = modbus_read_registers(modbus_ctx, start_address, quantity, values);
   if (result < 0)
   {
     sprintf(log_msg, "Modbus Client: error reading registers => %s\n",
             strerror(errno));
     log(log_msg);
     return -3;
   }
 
   return result;
 }
 
 /************************************************************************
 * FUNCTION: modbus_write_single_register                              *
 *                                                                    *
 * Writes a single value to a holding register on the Modbus server.   *
 *                                                                    *
 * Parameters:                                                        *
 *   connection_id: Ignored (managed internally)                      *
 *   address: Register address (0-65535)                              *
 *   value: Value to write (0-65535)                                  *
 * Returns:                                                           *
 *   0 on success, negative value on failure                          *
 ************************************************************************/
 int modbus_write_single_register(int connection_id, uint16_t address,
                                 uint16_t value)
 {
   char log_msg[1000];
   int result;
 
   if (modbus_ctx == NULL)
   {
     sprintf(log_msg, "Modbus Client: no active connection for writing "
                     "register\n");
     log(log_msg);
     return -1;
   }
 
   result = modbus_write_register(modbus_ctx, address, value);
   if (result < 0)
   {
     sprintf(log_msg, "Modbus Client: error writing register => %s\n",
             strerror(errno));
     log(log_msg);
     return -2;
   }
 
   return 0;
 }
 
 /************************************************************************
 * FUNCTION: modbus_read_coils                                         *
 *                                                                    *
 * Reads a specified number of coils from the Modbus server.           *
 *                                                                    *
 * Parameters:                                                        *
 *   connection_id: Ignored (managed internally)                      *
 *   start_address: Starting address of coils (0-65535)               *
 *   quantity: Number of coils to read (1-2000)                       *
 *   values: Buffer to store read values (0 or 1)                     *
 * Returns:                                                           *
 *   Number of coils read on success, negative value on failure       *
 ************************************************************************/
 int modbus_read_coils(int connection_id, uint16_t start_address,
                       uint16_t quantity, uint8_t *values)
 {
   char log_msg[1000];
   int result;
 
   if (modbus_ctx == NULL)
   {
     sprintf(log_msg, "Modbus Client: no active connection for reading "
                     "coils\n");
     log(log_msg);
     return -1;
   }
 
   if (quantity < 1 || quantity > 2000)
   {
     sprintf(log_msg, "Modbus Client: invalid quantity for reading coils "
                     "(%d)\n", quantity);
     log(log_msg);
     return -2;
   }
 
   result = modbus_read_bits(modbus_ctx, start_address, quantity, values);
   if (result < 0)
   {
     sprintf(log_msg, "Modbus Client: error reading coils => %s\n",
             strerror(errno));
     log(log_msg);
     return -3;
   }
 
   return result;
 }
 
 /************************************************************************
 * FUNCTION: modbus_write_single_coil                                  *
 *                                                                    *
 * Writes a single value to a coil on the Modbus server.               *
 *                                                                    *
 * Parameters:                                                        *
 *   connection_id: Ignored (managed internally)                      *
 *   address: Coil address (0-65535)                                  *
 *   value: Value to write (0 or 1)                                   *
 * Returns:                                                           *
 *   0 on success, negative value on failure                          *
 ************************************************************************/
 int modbus_write_single_coil(int connection_id, uint16_t address,
                             uint8_t value)
 {
   char log_msg[1000];
   int result;
 
   if (modbus_ctx == NULL)
   {
     sprintf(log_msg, "Modbus Client: no active connection for writing "
                     "coil\n");
     log(log_msg);
     return -1;
   }
 
   result = modbus_write_bit(modbus_ctx, address, value ? 1 : 0);
   if (result < 0)
   {
     sprintf(log_msg, "Modbus Client: error writing coil => %s\n",
             strerror(errno));
     log(log_msg);
     return -2;
   }
 
   return 0;
 }
 
 /************************************************************************
 *                  END OF MODBUS TCP CLIENT                          *
 ************************************************************************/