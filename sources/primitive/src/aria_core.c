/*********************************************
Author  : Chris Allard, Corentin Aulagnier
Date    : 2019-02
Source  : https://github.com/Allard-Chris/Aria
Version : 0.1
###
Aria primitive functions
**********************************************/
#include "aria_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ariaCore(int            mode,
             ariaKey_t*     key,
             unsigned char* working_input_buffer,
             unsigned char* working_output_buffer,
             int            valid) {
  char     nb_round;
  state_t* state = NULL;

  /* fixed round number */
  if (key->size == 128)
    nb_round = 12;
  else if (key->size == 192)
    nb_round = 14;
  else /* 256-bits key size */
    nb_round = 16;

  DBG(fprintf(stdout, "Total number of round: %d\n", nb_round));

  /* create init state */
  state = (state_t*)malloc(sizeof(state_t));
  if (state == NULL) return -1;

  /* copy input buffer into state */
  memcpy(state, working_input_buffer, CHUNK_SIZE_OCTET);

  /* round key EK */

  /* loop for all rounds */
  /* start at 1 to be egal with Aria specification description in PDF file */
  for (int i = 1; i <= nb_round; i++) {
    DBG(fprintf(stdout, "Current round: %d\n", i));
    /* XORing the round input and the round_key ek */
    /* if (valid) test output from XOR*/

    if (i % 2 != 0) DBG(fprintf(stdout, "Odd round\n"));
    /* ..substition layer type 1 */
    else
      DBG(fprintf(stdout, "Even round\n"));
    /* ..substition layer type 2 */
    /* Test result if Test variable is defined */

    /* if (i < nb_round)*/
    /* ..diffusion_layer */
    /* ..Test result if Test variable is defined */
  }
  /* Last XORing the round input and the round_key ek */

  /* write result in working_output_buffer*/
  memcpy(working_output_buffer, state, CHUNK_SIZE_OCTET);

  free(state);
  return 0;
}