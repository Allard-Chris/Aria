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
  fprintf(stderr, "How to use aria:\n");
  fprintf(stderr,
          "Usage: ./aria [mode] --key <key_file_name> --in <input_file_name> "
          "--out <output_file_name>\n");
  fprintf(stderr, "Mode: --encrypt or --decrypt\n");
  fprintf(
      stderr,
      "--key: file with hexa key inside in only one line without spaces and "
      "Feed Line\n");
  fprintf(stderr, "--in : file with plain-text\n");
  fprintf(stderr, "--out: output file\n");
  fprintf(
      stderr,
      "[optional]: --valid: use with valid/plaintext.txt input to test aria "
      "algorithm\n");
}

/* function to extract, from a file, a key */
/* return filled ariaKey struct */
ariaKey_t* extractKeyFromFile(const char* filename) {
  char       current_char;
  ariaKey_t* key = NULL;
  int        size = 0, i = 0, peer = 0;

  /* Getting size of current key */
  FILE* keyfile = fopen(filename, "r");
  if (keyfile == NULL) goto error;
  while ((current_char = fgetc(keyfile)) != EOF) {
    size += 4;
  }

  /* init ariaKey struct to store key */
  if ((size != 128) && (size != 192) && (size != 256)) goto error;
  if ((key = (ariaKey_t*)malloc(sizeof(ariaKey_t))) == NULL) {
    fprintf(stderr, "Can't get enough memory\n");
    goto error;
  }

  key->size = size;
  DBG(fprintf(stdout, "Key size: %d\n", size));

  /* read current key */
  fseek(keyfile, 0, SEEK_SET);
  while ((current_char = fgetc(keyfile)) != EOF) {
    current_char = atoh(current_char);
    if (current_char == -1) goto error;

    /* first 4 bits of u8 */
    if (peer == 0) {
      peer++;
      key->key[i] = (u8)current_char;
    }

    /* last 4 bits of u8 */
    else {
      key->key[i] = (u8)(key->key[i] << 4) + current_char;
      i++;
      peer = 0;
    }
  }
  fclose(keyfile);
  return key;

/* in case of error */
error:
  fprintf(stderr, "Error in parsing keyfile\n");
  free(key);
  return NULL;
}

/* main function starting Aria cipher */
int main(int argc, const char** argv) {
  const char*    infile = NULL;
  const char*    outfile = NULL;
  const char*    keyfile = NULL;
  unsigned char* working_input_buffer = NULL;
  unsigned char* working_output_buffer = NULL;
  int            working_length;
  int            mode = -1;
  ariaKey_t*     key;
  argc--;
  argv++;

  /* parsing arguments */
  while (argc >= 1) {
    /* checking mode */
    if (strcmp(*argv, "--decrypt") == 0) {
      mode = DECRYPT;
    } else if (strcmp(*argv, "--encrypt") == 0) {
      mode = ENCRYPT;
    }

    /* checking key file */
    else if (strcmp(*argv, "--key") == 0) {
      if (--argc < 1) goto error;
      keyfile = *(++argv);
    }

    /* checking input file */
    else if (strcmp(*argv, "--in") == 0) {
      if (--argc < 1) goto error;
      infile = *(++argv);
    }

    /* checking output file */
    else if (strcmp(*argv, "--out") == 0) {
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

  /* check mode */
  if (mode == -1) goto error;

  /* open input file */
  FILE* in = fopen(infile, "rb");
  if (in == NULL) goto error;

  /* open output file */
  FILE* out = fopen(outfile, "wb");
  if (out == NULL) goto error;

  /* create input/output buffer for chunks */
  working_input_buffer = malloc(CHUNK_SIZE_OCTET);
  working_output_buffer = malloc(CHUNK_SIZE_OCTET);

  /* for every 128-bit chunk of input file */
  /* check malloc result here, in one if, to avoid memory leaks */
  if ((working_input_buffer != NULL) && (working_output_buffer != NULL)) {
    do {
      /* fill buffer */
      working_length =
          fread(working_input_buffer, sizeof(u8), CHUNK_SIZE_OCTET, in);

      /* if still have data in inputfile */
      if (working_length) {
        if (working_length < CHUNK_SIZE_OCTET)
          fillBuffer(working_input_buffer, working_length);

        DBG(fprintf(stdout,
                    "New chunk extracted from input file, size of buffer: %d\n",
                    working_length));
        DBG(printBuffer(working_input_buffer, CHUNK_SIZE_OCTET));

        /* call aria algorithm */
        if (ariaCore(mode, key, working_input_buffer, working_output_buffer) ==
            -1)
          goto error;

        /* write into output file with contents inside working_output_buffer */
        fwrite(working_output_buffer, sizeof(u8), CHUNK_SIZE_OCTET, out);
      }
    } while (working_length);
  }

  /* close */
  fclose(in);
  fclose(out);

  free(working_input_buffer);
  free(working_output_buffer);
  free(key);
  return 0;

error:
  fprintf(stderr, "Runtime error!\n");
  help();
  return 1;
}