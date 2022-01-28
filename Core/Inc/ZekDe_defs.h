#ifndef MYDEF_H
#define MYDEF_H

#include "stdint.h"

#define kbit0 	0x1UL
#define kbit1 	0x2UL
#define kbit2	0x4UL
#define kbit3	0x8UL
#define kbit4	0x10UL
#define	kbit5	0x20UL
#define	kbit6	0x40UL
#define	kbit7	0x80UL
#define	kbit8	0x100UL
#define	kbit9	0x200UL
#define	kbit10 	0x400UL
#define	kbit11 	0x800UL
#define	kbit12  0x1000UL
#define	kbit13  0x2000UL
#define	kbit14  0x4000UL
#define	kbit15  0x8000UL
#define	kbit16 	0x10000UL
#define	kbit17 	0x20000UL
#define	kbit18 	0x40000UL
#define	kbit19 	0x80000UL
#define	kbit20 	0x100000UL
#define	kbit21 	0x200000UL
#define	kbit22 	0x400000UL
#define	kbit23 	0x800000UL
#define	kbit24 	0x1000000UL
#define	kbit25 	0x2000000UL
#define	kbit26 	0x4000000UL
#define	kbit27 	0x8000000UL
#define	kbit28 	0x10000000UL
#define	kbit29 	0x20000000UL
#define	kbit30 	0x40000000UL
#define	kbit31 	0x80000000UL

#define SET_BIT_POS(reg, pos)		((reg) |= 1UL << (pos))
#define RESET_BIT_POS(reg, pos)	((reg) &= ~(1UL << (pos)))
#define READ_BIT_POS(reg, pos)		(((reg) >> (pos)) & 1)
#define TOGGLE_BIT_POS(reg, pos)	((reg) ^= 1UL << (pos))
#define MODIFY_BIT_POS(reg, pos, _0_1)	((reg) ^= (-_0_1 ^ (reg)) & (1UL << (pos)))
//#define MODIFY_BIT_POS(reg, pos, _0_1)	((reg) & ~(1UL << (pos)) | (_0_1 << (pos)))

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
/**,
 * \def MODIFY_REG
 * \brief
 * \example MODIFY_REG(reg, kbit24, kbit24) 24. bit in reg set to '1'
 * MODIFY_REG(reg, kbit24, 0) 24. bit in reg set to '0'
 *
 */
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


#define IS_BIT(reg, _n)		(READ_BIT(reg, _n) == _n)
#define PERCENT_ERROR(goal, actual)		(100 * ((goal) - (actual)) / (goal))
#define TIME_OVER(time, target) (uint32_t)((time) - (target) < 0x80000000U)
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
