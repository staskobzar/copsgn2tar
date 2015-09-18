/**
 * Converts Cisco files *.cop.sgn to tar archives.
 *
 * @author Stas Kobzar <stas@modulis.ca> 
 * 
 */
#include "copsgn2tar.h"

#define NDEBUG 0
#define VERSION "1.0"

#define MAX_FILE_NAME (1 << 8)

int main(int argc,const char **argv)
{
  if(argc == 1){
    print_usage(argv[0]);
    return EINVAL;
  }
  char file_in_name[MAX_FILE_NAME] = {};
  char file_out_name[MAX_FILE_NAME] = {};
  FILE *file_in = NULL;
  FILE *file_out = NULL;
  int ch = NULL, do_write = NULL;

  strncpy(file_in_name, argv[1], MAX_FILE_NAME);
  file_in = fopen(file_in_name, "r");
  check(file_in, "Failed to open file to read: %s", file_in_name);

  sprintf(file_out_name, "%s.tar", file_in_name);
  file_out = fopen(file_out_name, "w");
  check(file_out, "Failed to open file to write: %s", file_out_name);

  while((ch = fgetc(file_in)) != EOF){
    // when pattern found, write to out file
    if(do_write){
      fputc(ch, file_out);
      continue;
    }
    // search pattern
    if(ch == 0x1f && fgetc(file_in) == 0x8b && fgetc(file_in) == 0x08){
      debug("Found pattern x1F8B08 at %ld", ftell(file_in));
      debug("Enable flag to start writing to file %s", file_out_name);
      // first rewind back to write
      fseek(file_in, ftell(file_in) - 3, SEEK_SET);
      do_write = 1;
    }
  }

  debug("Done: %s => %s\n", file_in_name, file_out_name);

  if(file_in) fclose(file_in);
  if(file_out) fclose(file_out);
  return 0;

error:
  if(file_in) fclose(file_in);
  if(file_out) fclose(file_out);
  return -1;
}

/**
 * Print usage
 */
void print_usage(const char *name) {
  printf("Converts Cisco cop.sgn file to tar archive.\n");
  printf("Version %s\n", VERSION);
  printf("Usage: %s <COP_FILE>\n", name);
}
