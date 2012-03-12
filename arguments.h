/** @file arguments.h
 *
 *  Declaration of the arguments functions.
 */

#ifndef ARGUMENTS_H_DEFINED
#define ARGUMENTS_H_DEFINED

extern int verbose_mode;
extern int extra_verbose_mode;
extern int encrypt_mode;
extern int decrypt_mode;

void args_handle (int argc, char* argv[]);
void print_help ();
void print_usage ();

#endif

