#include "main.h"

unsigned int convert_sbase(buffer_t *output, long int num, char *base, unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base, unsigned char flags, int wid, int prec);

/**
 * convert_sbase - Converts a signed long to the specified base and stores
 *                the result in a buffer.
 * @output: A pointer to a buffer_t struct containing a character array.
 * @num: The signed long number to be converted.
 * @base: A pointer to a string representing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int convert_sbase(buffer_t *output, long int num, char *base, unsigned char flags, int wid, int prec)
{
	int size;
	char digit, pad = '0';
	unsigned int ret = 1;

	for (size = 0; base[size]; size++)
		;

	if (num >= size || num <= -size)
		ret += convert_sbase(output, num / size, base, flags, wid - 1, prec - 1);
	else
	{
		for (; prec > 1; prec--, wid--) /* Handle precision */
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
	}

	digit = base[(num < 0 ? -1 : 1) * (num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}

/**
 * convert_ubase - Converts an unsigned long to the specified base and stores
 *                 the result in a buffer.
 * @output: A pointer to a buffer_t struct containing a character array.
 * @num: The unsigned long number to be converted.
 * @base: A pointer to a string representing the base to convert to.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base, unsigned char flags, int wid, int prec)
{
	unsigned int size, ret = 1;
	char digit, pad = '0', *lead = "0x";

	for (size = 0; base[size]; size++)
		;

	if (num >= size)
		ret += convert_ubase(output, num / size, base, flags, wid - 1, prec - 1);
	else
	{
		if (((flags >> 5) & 1) == 1) /* Printing a pointer address */
		{
			wid -= 2;
			prec -= 2;
		}
		for (; prec > 1; prec--, wid--) /* Handle precision */
			ret += _memcpy(output, &pad, 1);

		if (NEG_FLAG == 0) /* Handle width */
		{
			pad = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				ret += _memcpy(output, &pad, 1);
		}
		if (((flags >> 5) & 1) == 1) /* Print '0x' for pointer address */
			ret += _memcpy(output, lead, 2);
	}

	digit = base[(num % size)];
	_memcpy(output, &digit, 1);

	return (ret);
}