#include "main.h"

/************************* WRITE HANDLE *************************/

/**
 * handle_write_char - Prints a character
 * @c: The character to print
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int handle_write_char(char c, char buffer[],
                      int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/

/**
 * write_number - Prints a number
 * @is_negative: Indicates if the number is negative
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters printed
 */
int write_number(int is_negative, int ind, char buffer[],
                 int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
	                  length, padd, extra_ch));
}

/**
 * write_num - Writes a number using a buffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer array to handle print
 * @flags: Flags specifier
 * @width: Width specifier
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Padding character
 * @extra_c: Extra character
 *
 * Return: Number of characters printed
 */
int write_num(int ind, char buffer[],
              int flags, int width, int prec,
              int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length
