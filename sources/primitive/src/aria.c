/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria main functions
**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aria_core.h"
#include "aria_debug.h"
#include "aria_type.h"
#include "aria_utils.h"

void help() {
  fprintf(stderr, "How to use aria:\n\n");
  fprintf(stderr,
          "Usage: ./aria [mode] --key <key_file_name> --in <input_file_name> "
          "--out <output_file_name>\n\n");
  fprintf(stderr, "mode: \"e\" or \"encrypt\" for encryption mode\n");
  fprintf(stderr, "      \"d\" or \"decrypt\" for decryption mode\n\n");
  fprintf(stderr,
          "-k, --key: file with hexa key inside in only one line without "
          "spaces and "
          "Feed Line\n");
  fprintf(stderr, "-i, --in : file with plain-text\n");
  fprintf(stderr, "-o, --out: output file\n");
  fprintf(stderr, "\n-h, --help : give some help\n");
}

/* function to extract, from a file, a key */
/* expect key in hexa format */
/* return filled ariaKey struct */
ariaKey_t* extractKeyFromFile(const char* filename) {
  char       current_char = 0;
  ariaKey_t* master_key = NULL;
  int        size = 0;
  int        i = 0;
  int        carry = 0;

  /* Getting size of current key */
  FILE* keyfile = fopen(filename, "r");
  if (keyfile == NULL) goto error;
  while ((current_char = fgetc(keyfile)) != EOF) {
    size += 4;
  }

  /* init ariaKey struct to store key */
  if ((size != 128) && (size != 192) && (size != 256)) goto error;
  if ((master_key = (ariaKey_t*)malloc(sizeof(ariaKey_t))) == NULL) {
    fprintf(stderr, "Can't get enough memory\n");
    goto error;
  }

  /* set size */
  master_key->size = size;
  DBG(fprintf(stdout, "Key size: %d\n", size));

  /* read current key */
  fseek(keyfile, 0, SEEK_SET); /* reset to the beginning of the file*/
  while ((current_char = fgetc(keyfile)) != EOF) {
    current_char = atoh(current_char);
    if (current_char == -1) goto error;

    /* first 4 bits of u8 */
    if (carry == 0) {
      carry++;
      master_key->key[i] = (u8)current_char;
    }

    /* last 4 bits of u8 */
    else {
      master_key->key[i] = (u8)(master_key->key[i] << 4) + current_char;
      i++;
      carry = 0;
    }
  }
  fclose(keyfile);
  fillBuffer(master_key->key, master_key->size, MAX_SIZE_OCTETS); /* Adding zero
      on remaining spaces*/
  return master_key;

/* in case of error */
error:
  fprintf(stderr, "Error in parsing keyfile\n");
  free(master_key);
  return NULL;
}

/* main function starting Aria cipher */
int main(int argc, const char** argv) {
  const char* infile = NULL;
  const char* outfile = NULL;
  const char* keyfile = NULL;
  u8*         input_buffer = NULL;
  u8*         output_buffer = NULL;
  int         nb_readed = 0;
  int         mode = -1;
  ariaKey_t*  master_key = NULL;

  /* parsing arguments */
  argc--;
  argv++;
  while (argc >= 1) {
    /* need help */
    if ((strcmp(*argv, "--help") == 0) || (strcmp(*argv, "-h") == 0)) {
      goto help;
    }

    /* checking mode */
    else if ((strcmp(*argv, "decrypt") == 0) || (strcmp(*argv, "d") == 0)) {
      mode = DECRYPT;
    } else if ((strcmp(*argv, "encrypt") == 0) || (strcmp(*argv, "e") == 0)) {
      mode = ENCRYPT;
    }

    /* checking key file */
    else if ((strcmp(*argv, "--key") == 0) || (strcmp(*argv, "-k") == 0)) {
      if (--argc < 1) goto error;
      keyfile = *(++argv);
    }

    /* checking input file */
    else if ((strcmp(*argv, "--in") == 0) || (strcmp(*argv, "-i") == 0)) {
      if (--argc < 1) goto error;
      infile = *(++argv);
    }

    /* checking output file */
    else if ((strcmp(*argv, "--out") == 0) || (strcmp(*argv, "-o") == 0)) {
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
  } /* end parsing arguments */

  /* check mode */
  if (mode == -1) goto error;

  /* extract key inside keyfile */
  if (keyfile != NULL) {
    master_key = extractKeyFromFile(keyfile);
    if (master_key == NULL) goto error;
  } else
    goto error;

  /* open input file */
  FILE* in = fopen(infile, "rb");
  if (in == NULL) goto error;

  /* open output file */
  FILE* out = fopen(outfile, "wb");
  if (out == NULL) goto error;

  /* create input/output buffer for 128bit chunks */
  input_buffer = malloc(CHUNK_16_OCTETS);
  output_buffer = malloc(CHUNK_16_OCTETS);

  /* for every 128bit chunk of input file */
  /* check malloc result here, in one if, to avoid memory leaks */
  if ((input_buffer != NULL) && (output_buffer != NULL)) {
    do {
      /* fill buffer */
      nb_readed = fread(input_buffer, sizeof(u8), CHUNK_16_OCTETS, in);

      /* if still have data in inputfile */
      if (nb_readed) {
        if (nb_readed < CHUNK_16_OCTETS)
          fillBuffer(input_buffer, nb_readed, CHUNK_16_OCTETS);

        DBG(fprintf(stdout, "New chunk, size of buffer: %d\n", nb_readed));
        DBG(printBuffer(input_buffer, CHUNK_16_OCTETS));

        /* call aria algorithm */
        ariaCore(mode, master_key, input_buffer, output_buffer);

        /* write into output file with contents inside working_output_buffer */
        fwrite(output_buffer, sizeof(u8), CHUNK_16_OCTETS, out);
      }
    } while (nb_readed); /* until we read all data from inputfile */
  }

  /* close */
  fclose(in);
  fclose(out);

  free(input_buffer);
  free(output_buffer);
  free(master_key);
  return 0;

error:
  fprintf(stderr, "Runtime error!\n");

help:
  help();
  return 1;
}
