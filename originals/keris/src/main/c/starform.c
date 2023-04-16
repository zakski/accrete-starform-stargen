#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "structs.h"
#include "gensys.h"
#include "display.h"

flags args;

int main(int argc, char **argv)
{
  char *c;
  bool skip;
  int  nstars = 1;
  unsigned long random_seed = 0;

  char *program = argv[0];
  while (--argc > 0 && (*++argv)[0] == '-')
  {
    for (c = argv[0] + 1, skip = false; (*c != '\0') && (!(skip)); c++)
      switch (*c)
      {
      case 'm':         /* set moon output */
        args.make_moon = true;
        break;
        
      case 's':         /* set random seed */
        random_seed = strtoul(&(*++c), NULL, 0);
        skip = true;
        break;
        
      case 'v':         /* increment verbosity */
        args.verbose = true;
        break;
        
      case 'n':
        nstars = strtoul(&(*++c), NULL, 0);
        skip = true;
        break;
        
      case 'h':
      case '?':
      default:
        fprintf(stderr, "%s: Usage: %s [-l] [-s#] [-v] [-m] [-n#]\n",
                program, program);
        return 1;
      }
  }
  
  // generate N stars
  while (nstars-- > 0)
  {
    stellar_system *system = generate_stellar_system(random_seed);
    display_system(system);
    free_stellar_system(system);
  }
  return 0;
}
