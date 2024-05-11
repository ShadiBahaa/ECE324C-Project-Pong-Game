#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(Reg, bitnum)       (Reg |=1<<bitnum)
#define CLR_BIT(Reg, bitnum)       (Reg &=~(1<<bitnum))
#define TOG_BIT(REG, BIT)		   ( (REG) ^=  (1<<(BIT)) )
#define GET_BIT(Reg, bitnum)       ((Reg>>bitnum)&1)
#define WRT_BIT(REG, BIT, VAL) ( (REG) = ( ( (REG) & (~(1<<(BIT))) ) | ( (VAL) << (BIT)  ) ) )

#endif /* LIB_BIT_MATH_H_ */
