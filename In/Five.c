#include <stdio.h>
#include <stdint.h>
#include <string.h>

// -------------------- CRC-12 (Polynomial = 0x180F) --------------------
uint16_t crc12(const uint8_t *data, int len) {
    uint16_t crc = 0x000;      // Initial value
    uint16_t poly = 0x180F;    // CRC-12 polynomial

    for (int i = 0; i < len; i++) {
        crc ^= (data[i] << 4); // Align 8-bit input to 12-bit CRC

        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x800)   // If MSB (12th bit) is 1
                crc = (crc << 1) ^ poly;
            else
                crc <<= 1;

            crc &= 0xFFF;      // Keep CRC to 12 bits
        }
    }
    return crc;
}

// -------------------- CRC-16 (Polynomial = 0x8005) --------------------
uint16_t crc16(const uint8_t *data, int len) {
    uint16_t crc = 0x0000;     // Initial value
    uint16_t poly = 0x8005;    // CRC-16 polynomial

    for (int i = 0; i < len; i++) {
        crc ^= (data[i] << 8); // Align byte to top of CRC

        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x8000)  // Check MSB (16th bit)
                crc = (crc << 1) ^ poly;
            else
                crc <<= 1;
        }
    }
    return crc;
}

// -------------------- CRC-CCITT (Polynomial = 0x1021) --------------------
uint16_t crc_ccitt(const uint8_t *data, int len) {
    uint16_t crc = 0xFFFF;     // Standard initial value for CCITT
    uint16_t poly = 0x1021;    // CRC-CCITT polynomial

    for (int i = 0; i < len; i++) {
        crc ^= (data[i] << 8);

        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x8000)  // Check MSB
                crc = (crc << 1) ^ poly;
            else
                crc <<= 1;
        }
    }
    return crc;
}

// -------------------- MAIN PROGRAM --------------------
int main() {
    char input[128];

    printf("Enter the data string: ");
    fgets(input, sizeof(input), stdin); // Read input including spaces

    // Remove newline character if present
    input[strcspn(input, "\n")] = '\0';

    int length = strlen(input);

    printf("\n--- CRC Results ---\n");
    printf("CRC-12:    0x%03X\n", crc12((uint8_t*)input, length));
    printf("CRC-16:    0x%04X\n", crc16((uint8_t*)input, length));
    printf("CRC-CCITT: 0x%04X\n", crc_ccitt((uint8_t*)input, length));

    return 0;
}
