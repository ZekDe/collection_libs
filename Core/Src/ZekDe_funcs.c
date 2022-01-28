#include "ZekDe_defs.h"
#include "ZekDe_funcs.h"


/**
 * \def make_sumFunc makes functions of type t
 * \brief example usage: make_func(int) creates a
 * int sum_int(int a, int b) function
 *
 *
 */
#define funcTemplate(t)	t func_##t(t a, t b) \
{\
	return (t)(a + b); \
}


/**
 * \fn void risingEdgeDetection_withCB(uint8_t, void(*)(void))
 * \brief - state of 'catch' changes from 0 to 1
 * callback function is called
 * \param catch - related value to catch
 * \param cb - callback function
 */
void vRisingEdgeDetection_withCB(_Bool catch, void(*cb)(void))
{
	static _Bool aux = false;

	if (catch)
	{
		if (!aux)
		{
			aux = true;
			(*cb)();
		}
	}
	else
	{
		aux = false;
	}
}

/**
 * \fn uint8_t risingEdgeDetection(uint8_t)
 * \brief - state of 'catch' changes from 0 to 1
 * and return value remains 1 until which is read
 * \param catch - related value to catch
 * \return - 1 is caught
 */
_Bool oRisingEdgeDetection(_Bool catch)
{
	static _Bool aux = false;

	if (catch)
	{
		if (!aux)
		{
			aux = true;
			return true;
		}
	}
	else
	{
		aux = false;
	}
	return false;
}

/**
 * @brief to activate the seal, "breakTheSeal" should be 0 and after the "seal" is 1, "out" is going to be 1.
 * To break the seal, "breakTheSeal" should be 1
 * @param seal - variable for sealing
 * @param breakTheSeal - variable that break the sealing
 * @param out - result is 1 or 0
 */
void vSeal(_Bool seal, _Bool breakTheSeal, _Bool *out)
{
	*out = (((seal) || (*out)) && !breakTheSeal);
}

/**
 * @brief Q(t+1) = S + R'Q(t) characteristic equation, reset priority
 * if S and R are 1, Q is 0
 * @param S
 * @param R
 * @param Q
 */
void vSR_FF(_Bool S, _Bool R, _Bool *Q)
{
	if(S && R)
	{
		*Q = false;
	}
	else
	{
		*Q = S || (!R && *Q); //
	}
}


