/* COMMONLIB.H
 *
 * Author: Isonguyo John <isongjohn014@gmail.com>
 * created on 14 May, 2024.
 *
 * Modified by: Isonguyo John
 * Last modified: 14 May, 2024.
 *
 * Header file for clib.c
 */


#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <dirent.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define NO_HIDDEN 1
#define MAX(x,y) ((x) > (y)?(x):(y))
#define ABS(x) ((x) < 0?-1*(x):(x))
#define EOL 10



typedef struct {
  mode_t mode;
  struct dirent entry;
  char path[PATH_MAX];
} __direntry;

typedef __direntry DIRENTRY;


/*[str_concat]- concatenate strings `str1`,`str2` without modifying the original strings.
 * The new string should be deallocated  with `free`.
 * Returns new string on success, and returns NULL 	nd sets a `errno` on failure.
 */
char *str_concat(const char *str1,const char *str2);


/* [readfile]- opens and read `count` bytes from the file at `file_path` into `buffer`.
 * Returns the number of bytes read on success, and return a negative  value and sets `errno` on failure.
 */
ssize_t readfile(const char *pathname,void *buffer, size_t count);


/* [writefile]- opens and write `count` bytes to the file at `file_aath` from `buffer`.
 * Returns number of bytes written on success, and returns a negative value and set `errno` on failure.
 */
ssize_t writefile(const char *pathname,void *buffer,size_t count);


/*[scandir_r]- Traverse a directory recursively storing
 * at most `count` DIRENTRY structure in `buf`.
 * Returns the number of DIRENTRY structure in `buf` on 
 * success, and returns a negative value and set errno
 * on failure.
 */
ssize_t  traversdirr(const char *path,DIRENTRY buf[],size_t count, int flag);


/*[gcd]- calculate and returns the greatest common divisor of `a` and `b`.
 */
int64_t gcd(int64_t a,int64_t b);


/*[str_toupper]- convert every lowercase character 
 * in `str` at position less than `len` or before 
 *  `NULL` character to uppercase.
 * Returns `str`.
 */
char *str_toupper(char *str, size_t len);


/*[str_tolower]- convert every uppercase character in 
 * `str`  at position less than `len` or before
 * a `NULL` character to lowercase.
 * Returns `str`
 */
char *str_tolower(char *str, size_t len);


/*[str_rev]- reverses a string
 * Returns `str`
 */
char *str_rev(char *str);


/*[str_slice]-
 *
 */
size_t str_slice(char *dst,const char *str,int start,int end);


/*[str_trim]- Remove blank characters from the beginning and end
 * of a string.
 * Return `str`
 */
char *str_trim(char *str);


/*[readline_p] - 
 *
 *
 */

char *readline_p(const char *path,char buffer[], size_t buffer_size, int lineno);


/*[readline_fd]- 
 *
 *
 */

char *readline_fd(int fd,char buffer[],size_t buffer_size, int lineno);

#endif
