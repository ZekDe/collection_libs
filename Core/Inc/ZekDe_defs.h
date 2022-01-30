#ifndef ZEKDE_DEFS_H
#define ZEKDE_DEFS_H

#include "stdint.h"

#define SET_BIT_POS(reg, pos)		((reg) |= 1UL << (pos))
#define RESET_BIT_POS(reg, pos)	((reg) &= ~(1UL << (pos)))
#define READ_BIT_POS(reg, pos)		(((reg) >> (pos)) & 1UL)
#define TOGGLE_BIT_POS(reg, pos)	((reg) ^= 1UL << (pos))
#define MODIFY_BIT_POS(reg, pos, _0_1)	((reg) ^= (-_0_1 ^ (reg)) & (1UL << (pos)))
//#define MODIFY_BIT_POS(reg, pos, _0_1)	((reg) & ~(1UL << (pos)) | (_0_1 << (pos)))

#define PERCENT_ERROR(goal, actual)		(100 * ((goal) - (actual)) / (goal))
/**
 * \def __SIGNUM
 * \brief
 * if x < 0 -> -1
 * if x = 0 -> 0
 * if x > 0 -> 1
 * \return -1, 0, 1
 */
#define SIGNUM(x)				((x) > 0) - ((x) < 0)
#define IS_ODD_NUMBER(x)		(((x) & 1) != 0)
#define SWAP_BYTE(x)			(x) = ( (((x) & 0x0F) << 4) | (((x) & 0xF0) >> 4) )

/**
 * \def MOVE(en, out, in)
 * \brief To transfer the content of the in to the out in accordance the en
 * en state '1' is active
 */
#define MOVE(en, out, in)		(en) ? ((out) = (in)): 0

typedef struct
{
	uint32_t bit0:1U;
	uint32_t bit1:1U;
	uint32_t bit2:1U;
	uint32_t bit3:1U;
	uint32_t bit4:1U;
	uint32_t bit5:1U;
	uint32_t bit6:1U;
	uint32_t bit7:1U;
}byte_t;


#endif /* MYDEF_H */
