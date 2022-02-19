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
void timeoutCheck(timeout_t *s, const uint32_t *pdwNow, void(*cb)(void))
{
	if(s->oIn)
	{
		if(!s->oAux)
 		{
 			s->dwSince = *pdwNow;
 			s->oAux = true;
 		}
		else if(TIME_OVER(*pdwNow, s->dwSince + s->dwInterval))
		{
				s->dwSince = *pdwNow;
				(*cb)();
		}
		else
		{}
	}
	else
	{
		s->oAux = false;
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
_Bool TON(ton_t *s, _Bool oIn, const uint32_t *pdwNow, uint32_t dwPresetTime)
{
	if(oIn)
	{
		if(!s->oAux)
 		{
			s->dwSince = *pdwNow;
			s->oAux = true;
 		}
		else if(TIME_OVER(*pdwNow, s->dwSince + dwPresetTime))
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
		s->oAux = false;
	}

	return false;
}
