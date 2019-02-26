/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria main functions
**********************************************/
#include "aria_const.h"
#include "aria_core.h"
#include "aria_type.h"
#include "aria_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void help() {
  fprintf(stderr, "How to use aria :\n");
  fprintf(stderr,
          "Usage: ./aria [mode] -key <key_file_name> -in <input_file_name> "
          "-out <output_file_name>\n");
  fprintf(stderr, "Mode: -encrypt or -decrypt\n");
  fprintf(stderr,
          "-key: file with key inside in only one line without spaces\n");
  fprintf(stderr, "-in : file with plain-text\n");
  fprintf(stderr, "-out: output file\n");
}

ariaKey_t* extractKeyFromFile(const char* filename) {
  char       current_char;
  ariaKey_t* key = NULL;

  FILE* keyfile = fopen(filename, "r");
  if (keyfile == NULL) return key;
  key = (ariaKey_t*)malloc(sizeof(ariaKey_t));
  while ((current_char = fgetc(keyfile)) != EOF) {
    if (atoh(current_char) == -1) return key;
  }
  fclose(keyfile);
  return key;
}

int main(int argc, const char** argv) {
  const char* infile = NULL;
  const char* outfile = NULL;
  const char* keyfile = NULL;
  int         mode = -1;
  ariaKey_t*  key;
  argc--;
  argv++;

  /* parsing arguments */
  while (argc >= 1) {
    /* checking mode */
    if (strcmp(*argv, "-decrypt") == 0) {
      mode = DECRYPT;
    } else if (strcmp(*argv, "-encrypt") == 0) {
      mode = ENCRYPT;
    }

    /* checking key file */
    else if (strcmp(*argv, "-key") == 0) {
      if (--argc < 1) goto error;
      keyfile = *(++argv);
    }

    /* checking input file */
    else if (strcmp(*argv, "-in") == 0) {
      if (--argc < 1) goto error;
      infile = *(++argv);
    }

    /* checking output file */
    else if (strcmp(*argv, "-out") == 0) {
      if (--argc < 1) goto error;
      outfile = *(++argv);
    }

    /* bad arguments */
    else {
      fprintf(stderr, "Unknown option %s\n", *argv);
      goto error;
    }
    argc--;
    argv++;
  }

  /* extract key inside keyfile */
  if (keyfile != NULL) {
    key = extractKeyFromFile(keyfile);
    if (key == NULL) goto error;
  } else
    goto error;

  free(key);
  return 0;

error:
  help();
  return 1;
}
