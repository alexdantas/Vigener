/** @file arguments.c
 *  Definition of the argument functions.
 *
 */

#include <stdio.h>      /* For printf() */
#include <stdlib.h>     /* For EXIT_SUCCESS and FAILURE */
#include <getopt.h>     /* For getopt_long() */

#include "arguments.h"

/** Handles all the commandline arguments.
 *
 * This is the main function of this module. It processes
 * an argv[] array of argc elements based on the options
 * specified at the struct option.
 *
 * This special structure is composed of four elements:
 * - Name (char* name)
 *   The name of the option. Note that, for example, the '--verbose' option
 *   is represented by the "verbose" string here.
 * - Has Arg (int has_arg)
 *   Indicates if this option takes an argument or not. Its an integer with
 *   three values: no_argument, required_argument and optional_argument.
 * - Flag (int* flag)
 *   TODO explain this shit
 * - Value (int val)
 *   TODO explain this shit
 *
 * If you want to add another argument, follow these steps:
 * # Add an option on the struct option.
 * # Add the short equivalent (if it exists) on the getopt_long() call.
 * # Add a case on the switch specifying the action of that option.
 *
 */
void args_handle (int argc, char* argv[])
{
	if (argc < 2)
	{
		print_usage();
		exit(EXIT_FAILURE);
	}

	static struct option options[] =
	{
		{"verbose",       no_argument, NULL, 'v'},
		{"help",          no_argument, NULL, 'h'},
		{"usage",         no_argument, NULL, 'u'},
		{"encrypt",       no_argument, NULL, 'e'},
		{"decrypt",       no_argument, NULL, 'd'},
		/* The last element must be all zeroes */
		{0, 0, 0, 0}
	};
	/* The index of the current option */
	int option_index;
	/* The character for comparison */
	int c = 0;

	/* We keep checking the arguments untill they run out (c == -1) */
	while (c != -1)
	{
		c = getopt_long (argc, argv, "vhued", options, &option_index);

		switch (c)
		{
		case 'v':
			verbose_mode = 1;
			break;

		case 'h':
			print_help ();
			exit(EXIT_SUCCESS);
			break;

		case 'u':
			print_usage ();
			exit(EXIT_SUCCESS);
			break;

		case 'e':
			encrypt_mode = 1;
			decrypt_mode = 0;
			break;

		case 'd':
			encrypt_mode = 0;
			decrypt_mode = 1;
			break;

		case '?':
			/* getopt_long() already printed an error message about
			 * unrecognized option, so you'll probably want to
			 * abort the execution now */
			 exit(EXIT_FAILURE);
			break;

		case -1:
			break;

		default:
			/* Do nothing */
			print_usage ();
			exit(EXIT_FAILURE);
			break;
		}
	}

	/* Just in case the user specified more arguments (not options)
	 * than needed, you decide what to do. Here, we just ignore them */
	while (optind < argc)
		optind++;

	/* Goodbye, hope you liked it! */
}


void print_help ()
{
	printf("vigener Help\n");
	printf("\n");
}


void print_usage ()
{
	printf("vigener Usage\n");
	printf("\tvigener [-v] [-ed] key message\n");
	printf("Options\n");
	printf("\t-d  Decrypts message with key\n");
	printf("\t-e  Encrypts message with key (default)\n");
	printf("\t-h  Print help\n");
	printf("\t-u  Print usage (this text)\n");
	printf("\t-v  Verbose mode: print cryptographic transformations\n");
	printf("Note that you should escape with \" multiple-word key/message\n");
	printf("\n");
}

