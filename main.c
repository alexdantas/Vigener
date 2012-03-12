/* vigener - An implementation of the Vigener Cipher cryptography algorithm.
 *
 *  In this program, i use the printable characters from the ASCII table
 *  to cryptograph/decryptograph messages.
 *
 *  I simply replace characters in the ASCII table according to a key
 *  specified by the user. If the same key is used to cryptograph and
 *  decryptograph, the result is the original message.
 *
 *  The input is received via STDIN and if none is specified, it waits.
 *
 *	TODO: Non-blocking sockets!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "arguments.h"

// They specify a range in the ASCII table where the characters can
// be replaced without breaking the document structure.
// (without generating strange characters, like DEL, NULL or EOF)
#define ASCII_START 32 // The ' ' (space) character
#define ASCII_DELTA 94 // How many characters until the '~' (tilde)

int verbose_mode = 0;
int extra_verbose_mode = 0;
int encrypt_mode = 1;
int decrypt_mode = 0;

int get_key(int argc, char* argv[], char** key)
{
	int i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			*key = argv[i];
			return 0;
		}
		i++;
	}
	return -1;
}

int sum_mod(int mod, int a, int b)
{
	int sum = a + b;

	if (sum > mod)
		sum -= mod;

	else if (sum < 1)
		sum += mod;

	return sum;
}


int sub_mod(int mod, int a, int b)
{
	int sub = a - b;

	if (sub > mod)
		sub -= mod;

	else if (sub < 1)
		sub += mod;

	return sub;
}

int main (int argc, char* argv[])
{
	char*  key      = NULL;
	char*  msg      = NULL;
	size_t key_size = 0;
	int    count    = 0;

	args_handle(argc, argv);
	get_key(argc, argv, &key);
	// check for errors in case there's no key

	key_size = strlen(key);

	msg = malloc(key_size + 1);
	if (msg == NULL)
	{
		// how should i hand memory errors?
		printf("Memory Error\n");
		exit(EXIT_FAILURE);
	}

	//if (stdin_is_ready())

	//else (open_file(argv))

	memset(msg, '\0', key_size + 1);
	count = read(STDIN_FILENO, msg, key_size);
	while (count != 0)
	// i gotta make sure that this loop keeps going
	// while there's still data to read on STDIN
	{
		// check for errors in case i don't read exactly key_size
		int i = 0;
		while (i < key_size)
		{
			if ((msg[i] < ASCII_START) || (msg[i] > ASCII_START + ASCII_DELTA))
			{
				i++;
				continue;
			}

			if (verbose_mode)
				fprintf(stdout, "%c + %c = ", msg[i], key[i]);

			char a = msg[i] - (ASCII_START - 1);
			char b = key[i] - (ASCII_START - 1);
			char c = 0;
			if (encrypt_mode)
				c = sum_mod(ASCII_DELTA, a, b);

			else if (decrypt_mode)
				c = sub_mod(ASCII_DELTA, a, b);

			c += (ASCII_START - 1);

			//write(STDOUT_FILENO, &c, 1);
				fprintf(stdout, "%c", c);

			// check for errors in case i don't send it

			if (verbose_mode)
				fprintf(stdout, "\n");

			i++;
		}
		memset(msg, '\0', key_size + 1);
		count = read(STDIN_FILENO, msg, key_size);
	}
	return 0;
}
