#include "sppbtp.h"
#include <string.h>

void sppbtp_encode_packet(sppbtp_packet_t *packet, uint8_t *buffer, uint16_t *buffer_size) {
    buffer[0] = packet->type;
    buffer[1] = (packet->payload_size >> 8) & 0xff;
    buffer[2] = packet->payload_size & 0xff;
    memcpy(&buffer[3], packet->payload, packet->payload_size);
    *buffer_size = packet->payload_size + SPPBTP_HEADER_SIZE;
}

void sppbtp_decode_packet(uint8_t *buffer, uint16_t buffer_size, sppbtp_packet_t *packet) {
    packet->type = buffer[0];
    packet->payload_size = (buffer[1] << 8) | buffer[2];
    memcpy(packet->payload, &buffer[3], packet->payload_size);
}
