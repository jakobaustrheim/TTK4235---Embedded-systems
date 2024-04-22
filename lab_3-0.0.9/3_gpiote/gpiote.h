#ifndef GPIOTE_H
#define GPIOTE_H
#include <stdint.h>

#define GPIOTE ((NRF_GPIOTE_REG*)0x40006000)

typedef struct {
	// Tasks
	volatile uint32_t OUT[8];
	// Events
	volatile uint32_t RESERVED0[56];
	volatile uint32_t EVENTS_IN[8];
	volatile uint32_t RESERVED1[23];
	volatile uint32_t PORT;
	// Registers
	volatile uint32_t RESERVED2[97];
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RESERVED3[129];
	volatile uint32_t CONFIG[8];
} NRF_GPIOTE_REG;

#endif
