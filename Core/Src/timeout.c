#include "timeout.h"

#define TIME_PASSED(now, since)	(now >= since) ? (now - since) : (now + (UINT32_MAX - since))

/**
 * \fn void vTimeoutCheck(timeout_t*, const uint32_t*, void(*)(void))
 * \brief Start a periodic timer with a specified duration .
 *
 * \param t - variables are stored which function needs
 * \param now - system tick continuously running
 * \param cb - callback function is called when the timer expired
 */
void vTimeoutCheck(timeout_t *t, const uint32_t *now, void(*cb)(void))
{
	if(t->in)
	{
		if(!t->aux)
 		{
 			t->since = *now;
 			t->aux = true;
 		}
		else if(TIME_OVER(*now, t->since + t->interval))
		{
				t->since = *now;
				(*cb)();
		}
		else
		{}
	}
	else
	{
		t->aux = false;
	}
}

/**
 * \fn uint8_t oTON(timeout_t*, uint32_t, uint32_t, uint32_t)
 * \brief Start a timer with a specified duration as on-delay.
 * \param t - variables are stored which function needs
 * \param in - timer is executed when the "in" state changes from 0 to 1
 * \param now - system tick continuously running
 * \param presetTime - timer is started for the time stored in
 * \return if time is over , return value is 1
 */
_Bool oTON(ton_t *t, _Bool in, const uint32_t *now, uint32_t presetTime)
{
	if(in)
	{
		if(!t->aux)
 		{
			t->since = *now;
			t->aux = true;
 		}
		else if(TIME_OVER(*now, t->since + presetTime))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		t->aux = false;
	}

	return false;
}
