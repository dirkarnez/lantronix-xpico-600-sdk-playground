
#pragma once

/*****************************************************************************/
/*                              Legal                                        */
/*****************************************************************************/

/*
** Copyright ©2015-2024, Lantronix, Inc. All Rights Reserved.
** By using this software, you are agreeing to the terms of the Software
** Development Kit (SDK) License Agreement included in the distribution package
** for this software (the “License Agreement”).
** Under the License Agreement, this software may be used solely to create
** custom applications for use on the Lantronix xPico Wi-Fi, xPico 200 Series,
** and xPort® Edge products.
** THIS SOFTWARE AND ANY ACCOMPANYING DOCUMENTATION IS PROVIDED "AS IS".
** LANTRONIX SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS
** FOR A PARTICULAR PURPOSE.
** LANTRONIX HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
** ENHANCEMENTS, OR MODIFICATIONS TO THIS SOFTWARE.
** IN NO EVENT SHALL LANTRONIX BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
** SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
** ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
** LANTRONIX HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*****************************************************************************/
/*                             Includes                                      */
/*****************************************************************************/

#include <stddef.h>

/*****************************************************************************/
/*                            Prototypes                                     */
/*****************************************************************************/

void *memchr(const void *s, int c, size_t n);

int memcmp(const void *str1, const void *str2, size_t length);

void *memcpy(void *destination, const void *source, size_t length);

void *memmem(
	const void *haystack_start, size_t haystack_len,
	const void *needle_start, size_t needle_len
);

void *memmove(void *destination, const void *source, size_t length);

void *memset(void *destination, int value, size_t length);

int strcasecmp(const char *str1, const char *str2);

char *strcat(char *destination, const char *source);

char *strchr(const char *str, int ch);

int strcmp(const char *str1, const char *str2);

char *strcpy(char *destination, const char *source);

size_t strcspn(const char *source, const char *reject);

char *strerror(int errnum);

size_t strlcat(char *destination, const char *source, size_t length);

size_t strlcpy(char *destination, const char *source, size_t length);

size_t strlen(const char *string);

int strncasecmp(const char *str1, const char *str2, size_t length);

char *strncat(char *dest, const char *src, size_t count);

int strncmp(const char *str1, const char *str2, size_t length);

char *strncpy(char *dest, const char *src, size_t n);

size_t strnlen(const char *string, size_t maxlen);

char *strpbrk(const char *s1, const char *s2);

size_t strspn(const char *source, const char *accept);

char *strstr(const char *haystack, const char *needle);

char *strcasestr(const char *haystack, const char *needle);

char *strtok(char *str, const char *delim);

char *strtok_r(char *str, const char *delim, char **last);

char *strrchr(const char *str, int c);

