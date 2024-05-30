#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif
#include "utils.h"

#define QUOTEDB "/run/qotd.db"
#define MAXQUOTELEN 512
#define EOL 10

unsigned short win_col;
size_t  quotes_count;

static void get_rand_quote(char qbuf[]);
static void init(size_t *qc);


int main(void)
{
  setvbuf(stdout,NULL,_IONBF,0);
  setvbuf(stderr,NULL,_IONBF,0);
  setvbuf(stdin,NULL,_IONBF,0);
  char quote_buffer[MAXQUOTELEN] = {0};
  struct winsize wsz;

  if(ioctl(STDOUT_FILENO,TIOCGWINSZ,(char *)&wsz) < 0)
    win_col = 20;
  else
    win_col = wsz.ws_col;

  char marker[win_col+14];
  strcpy(marker,"\n\x1b[1;32m");
  srand((unsigned) time(NULL));
  init(&quotes_count);

  get_rand_quote(quote_buffer);

  str_toupper(quote_buffer, strlen(quote_buffer));

  for(unsigned short i =0; i < win_col; ++i)
    strcat(marker,"*");

  strcat(marker,"\x1b[0m\n\0");

  printf("%s",marker);
  printf("%s", "\x1b[1;32m[QUOTE OF THE DAY]\x1b[0m");
  printf("%s",marker);
  write(STDOUT_FILENO,quote_buffer,strlen(quote_buffer));
  printf("%s",marker);

  return 0;
}


static void init(size_t *qc)
{
  int ch;
  FILE *fp;
  int i = 0;

  if((fp = fopen(QUOTEDB,"rb")) == NULL)
  {
    perror("qotd");
    exit(EXIT_FAILURE);
  }

  while((ch = getc(fp)) != EOF)
  {
    if(ch == EOL)
      ++i;
  }

  rewind(fp);
  fclose(fp);
  *qc  = i;

}


static void get_rand_quote(char qbuf[])
{
  int target_line = rand() % quotes_count;

  if(readline_p(QUOTEDB,qbuf,MAXQUOTELEN,target_line) == NULL)
  {
    perror("qotd");
    exit(EXIT_FAILURE);
  }
 
}
