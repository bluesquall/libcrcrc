
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <arpa/inet.h>

#include "libcrcrc.h"

// for sanity's sake
static void crc_printf( uint16_t crc ) {
    printf( "crc: %04" PRIx16 "\n", crc );
}


// Xmodem 0x04 --> 0x4084
// VESC get values: 0x 02 01 *04* =40 84= 03
static int test_crc16xmodem_04( void ) {
    const char data = 0x04;
    uint16_t expected = htons( 0x4084 );
    uint16_t crc = 0;
    crc = crc16xmodem( &data, 1 );
    assert( crc == expected );
    return EXIT_SUCCESS;
}

static int test_crc16xmodem_04_inclusive( void ) {
    const char data[3] = { '\x04' ,'\x40' , '\x84' };
    uint16_t crc = crc16xmodem( data, 3 );
    assert( crc == 0 );
    return EXIT_SUCCESS;
}



static int test_crc16ccitt_false( void ) {
    const char data = 0x03;
    uint16_t expected = htons( 0xD193 );
    uint16_t crc = 0;
    crc = crc16ccitt_false( &data, 1 );
    assert( crc == expected );
    return EXIT_SUCCESS;
}

static int test_crc16ccitt_false_inclusive( void ) {
    const char data[3] = { '\x03' ,'\xD1' , '\x93' };
    uint16_t crc = crc16ccitt_false( data, 3 );
    assert( crc == 0 );
    return EXIT_SUCCESS;
}


int main( void ) {
    int status = EXIT_SUCCESS;
    status &= test_crc16xmodem_04();
    status &= test_crc16xmodem_04_inclusive();
    status &= test_crc16ccitt_false();
    status &= test_crc16ccitt_false_inclusive();
    return status;
}
