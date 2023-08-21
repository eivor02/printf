#include <unistd.h>

/**
 * _write - Writes the character 'c' to stdout.
 * @c: The character to be printed.
 *
 * Return: On success, returns 1.
 * On error, returns -1 and sets errno appropriately.
 */
int _write(char c)
{
	return write(1, &c, 1);
}
