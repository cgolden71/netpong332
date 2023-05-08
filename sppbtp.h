#ifndef SPPBTP_H
#define SPPBTP_H

#include <stdint.h>

#define SPPBTP_HEADER_SIZE 3
#define SPPBTP_MAX_PAYLOAD_SIZE 256
#define SPPBTP_MAX_PACKET_SIZE (SPPBTP_HEADER_SIZE + SPPBTP_MAX_PAYLOAD_SIZE)

typedef struct {
    uint8_t type;
    uint16_t payload_size;
    uint8_t payload[SPPBTP_MAX_PAYLOAD_SIZE];
} sppbtp_packet_t;

void sppbtp_encode_packet(sppbtp_packet_t *packet, uint8_t *buffer, uint16_t *buffer_size);

void sppbtp_decode_packet(uint8_t *buffer, uint16_t buffer_size, sppbtp_packet_t *packet);

#endif
