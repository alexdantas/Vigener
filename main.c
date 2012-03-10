/* vigener - An implementation of the Vigener Cipher cryptography algorithm.
 *
 * Note: In C, we can freely convert between the integer type (int) and the
 *       character type (char). The textual result from an integer sum
 *       depends on the ASCII char table.
 *       On the ASCII table, the letter 'a' equals the integer 97. 'b' is
 *       98 and so far untill 'z' that is 122.
 *       So when i sum 'a' with 'e', for example, i must subtract 97 from
 *       both, sum the resulting numbers, and then add 97 again for the
 *       ASCII equivalent.
 *
 *
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_ALPHABET_LETTERS 26

int verbose_mode = 0;


/** Sums #a + #b respecting #mod
 *
 *  For example, if #mod is 26, #a is 25 and #b is 5, it will
 *  return 4.
 */
int sum_mod(int mod, int a, int b)
{
	int sum = a + b;

	if (sum > mod)
		sum -= mod;

	else if (sum < 1)
		sum += mod;

	return sum;
}

/** Converts a number between 1 and 26 to the ASCII character equivalent
 */
int convert_ascii(int number)
{
	return number + 96;
}


/** Does the whole job, receiving the key and the message as parameters
 */
int main (int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Usage: vigener 'key' 'message'\n");
		printf("Note that you should escape with \" multiple-word key/message\n");
		exit(1);
	}

	if (argc == 4)
		if (strcmp(argv[3], "-v") == 0)
			verbose_mode = 1;

	char* key          = NULL; /* Will contain repetitions of the key */
	char* message      = NULL; /* The whole message */
	int   key_size     = strlen(argv[1]);
	int   message_size = strlen(argv[2]);

	/* Initializing stuff */
	message = malloc(message_size + 1); /* +1 because of the NULL char */
	key     = malloc(message_size + 1);
	if ((message == NULL) || (key == NULL))
	{
		printf("Memory error\n");
		exit(1);
	}

	/* Pairing message with key */
	int i = 0;
	int j = 0;

	while (i < message_size)
	{
		message[i] = argv[2][i];
		key[i]     = argv[1][j];

		i++;
		j++;

		if (j == key_size)
			j = 0;
	}

	message[i] = '\0';
	key[i]     = '\0';

	/* The main loop - cryptographing and outputting */

	i = 0;

	while (i < message_size)
	{
		/* Special case of non-alphabetic characters (like space) */
		if ((message[i] < 'a') || (message[i] > 'z'))
		{
			printf("%c", message[i]);

			if (verbose_mode)
				printf("\n");

			i++;

			continue;
		}

		if (verbose_mode)
			printf("%c + %c = ", message[i], key[i]);

		int message_char = message[i] - 96;
		int key_char = key[i] - 96;

		char tmp = sum_mod(NUMBER_OF_ALPHABET_LETTERS, message_char, key_char);

		tmp = convert_ascii(tmp);

		printf("%c", tmp);
		i++;

		if (verbose_mode)
			printf("\n");
	}

	return 0;
}

