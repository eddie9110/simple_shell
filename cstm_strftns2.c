#include "main.h"

/**
 * cstmstr_reverser - a ftn to reverse string
 * @stng: parameter reps string of interest
 * Return: void()
 */

void cstmstr_reverser(char *stng)
{
	int th, on = 0;
	char *str, cstmptr;
	int cnt = 0;

	while(cnt >= 0) /*while lloop for determining str length*/
	{
		if (stng[cnt] == '\0')
			break;
		cnt++;
	}

	str = stng;

	for (th = 0; th < (cnt - 1); th++)
	{
		for (on = th + 1; on > 0; on--)
		{
			cstmptr = *(str + on);
			*(str + on) = *(str + (on - 1));
			*(str + (on - 1)) = cstmptr;
		}
	}
}
