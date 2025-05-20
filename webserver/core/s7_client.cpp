
/*=============================================================================|
|  PROJECT OpenPLC S7 Communication                                      1.0.0 |
|==============================================================================|
|  Copyright (C) 2025                                                  |
|  All rights reserved.                                                        |
|==============================================================================|
|  This file implements the S7 communication functions for OpenPLC using Snap7. |
|  It provides functionality to connect, disconnect, and read data from an S7 PLC. |
|==============================================================================*/

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "ladder.h"
#include "oplc_snap7.h"

// initialize logging system
const int log_msg_max_size = 1000;
char log_msg[log_msg_max_size];
char *p = log_msg;

//------------------------------------------------------------------------------
// Connect to an S7 PLC
//------------------------------------------------------------------------------
int s7_connect(const char* ip_address, int rack, int slot, TS7Client* client) {
    if (client == NULL || ip_address == NULL) {
        return errCliInvalidParams;
    }
    if (client->Connected()) {
        return errCliAlreadyRun;
    }

    // Use default PDU size (let Snap7 negotiate)
    printf("Attempting connection with default PDU size\n");
    int result = client->ConnectTo(ip_address, rack, slot);
    if (result != 0) {
        printf("ConnectTo failed: %d\n", result);
        return result;
    }
    result = client->SetConnectionType(CONNTYPE_BASIC);
    if (result != 0) {
        printf("SetConnectionType failed: %d\n", result);
        return result;
    }

    sprintf(log_msg, "S7: Try Connect\n");
    log(log_msg);

    // Log negotiated PDU size for debugging
    int requested, negotiated;
    negotiated = client->PDULength();
    printf("Requested PDU: %d, Negotiated PDU: %d\n", requested, negotiated);

    sprintf(log_msg, "" + negotiated);
    log(log_msg);

    return 0;
}

//------------------------------------------------------------------------------
// Disconnect from an S7 PLC
//------------------------------------------------------------------------------
int s7_disconnect(TS7Client* client) {
    if (client == NULL) {
        return errCliInvalidParams;
    }
    return client->Disconnect();
}

//------------------------------------------------------------------------------
// Read a single BOOL (bit) from a PLC Data Block (DB)
//------------------------------------------------------------------------------
int s7_read_bit(TS7Client* client, int db_number, int address, int bit_offset, bool* value, bool* success, int* error_code) {
    if (client == NULL || value == NULL || success == NULL || error_code == NULL) {
        *success = false;
        *error_code = errCliInvalidParams;
        return errCliInvalidParams;
    }
    if (!client->Connected()) {
        *success = false;
        *error_code = errIsoConnect;
        return errIsoConnect;
    }
    if (bit_offset < 0 || bit_offset > 7) {
        *success = false;
        *error_code = errCliInvalidParams;
        return errCliInvalidParams;
    }

    byte buffer;
    int result = client->DBRead(db_number, address, 1, &buffer); // Read 1 byte
    if (result == 0) {
        *value = (buffer & (1 << bit_offset)) != 0; // Extract bit
        *success = true;
        *error_code = 0;
    } else {
        *value = false;
        *success = false;
        *error_code = result;
    }
    return result;
}

//------------------------------------------------------------------------------
// Read a single BYTE from a PLC Data Block (DB)
//------------------------------------------------------------------------------
int s7_read_byte(TS7Client* client, int db_number, int address, byte* value, bool* success, int* error_code) {
    if (client == NULL || value == NULL || success == NULL || error_code == NULL) {
        *success = false;
        *error_code = errCliInvalidParams;
        return errCliInvalidParams;
    }
    if (!client->Connected()) {
        *success = false;
        *error_code = errIsoConnect;
        return errIsoConnect;
    }

    int result = client->DBRead(db_number, address, 1, value); // Read 1 byte
    if (result == 0) {
        *success = true;
        *error_code = 0;
    } else {
        *value = 0;
        *success = false;
        *error_code = result;
    }
    return result;  
}

//------------------------------------------------------------------------------
// Read a single WORD from a PLC Data Block (DB)
//------------------------------------------------------------------------------
int s7_read_word(TS7Client* client, int db_number, int address, word* value, bool* success, int* error_code) {
    
    sprintf(log_msg, "S7: Try Read\n");
    log(log_msg);
    
    if (client == NULL || value == NULL || success == NULL || error_code == NULL) {
        *success = false;
        *error_code = errCliInvalidParams;

        return errCliInvalidParams;
    }
    if (!client->Connected()) {
        *success = false;
        *error_code = errIsoConnect;

        sprintf(log_msg, "Error Code: " + *error_code);
        log(log_msg);

        return errIsoConnect;
    }


    sprintf(log_msg, "Start Read\n");
    log(log_msg);


    int result = client->DBRead(db_number, address, 2, value); // Read 2 bytes (WORD)
    if (result == 0) {
        *success = true;
        *error_code = 0;
    } else {
        *value = 0;
        *success = false;
        *error_code = result;
    }
    return result;
}
