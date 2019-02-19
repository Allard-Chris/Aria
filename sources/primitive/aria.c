/*
 * ARIA crypto primitive implementation
 */

#include <aria.h>

// Init function, prepare each struct with parameters
state_t* Aria_init(char *plain_text, unsigned char *init_key){
  state_t *init_state = malloc(sizeof(state_t));
  key_t *init_key_struct = malloc(sizeof(key_t));
  expansion_key_t *init_expansion_struct =  malloc(sizeof(expansion_key_t));

  // Expansion key init
  init_expansion_struct->w0 = 0;
  init_expansion_struct->w1 = 0;
  init_expansion_struct->w2 = 0;
  init_expansion_struct->w3 = 0;

  // Key init
  init_key_struct->key = init_key;
  init_key_struct->key_size = 0;
  init_key_struct->nb_round = 0;
  init_key_struct->expansion_struct = init_expansion_struct;

  // State init
  init_state->message = plain_text;
  init_state->current_round = 0;
  init_state->key_struct = init_key_struct;

  return init_state;
}

// Main function for Aria encryption
char* Aria_encrypt (char *plain_text, unsigned char *key){
  state_t *current_state = Aria_init(plain_text, key);

  if(current_state == NULL){
    printf("ERROR : Aria_init in Aria_encrypt");
    return NULL;
  }

  int return_value = Aria_round(current_state);

  if(return_value == 1){
    printf("ERROR : Aria_round in Aria_encrypt");
    return NULL;
  }

  return_value = Aria_key_expansion(current_state);

  if(return_value == 1){
    printf("ERROR : Aria_key_expansion in Aria_encrypt");
    return NULL;
  }

  return current_state->message;
}

// Main function for Aria decryption
char* Aria_decryption (char *cipher_text, unsigned char *key){
  state_t *current_state = Aria_init(cipher_text, key);

  if(current_state == NULL){
    printf("ERROR : Aria_init in Aria_encrypt");
    return NULL;
  }

  int return_value = Aria_round(current_state);

  if(return_value == 1){
    printf("ERROR : Aria_round in Aria_encrypt");
    return NULL;
  }

  return_value = Aria_key_expansion(current_state);

  if(return_value == 1){
    printf("ERROR : Aria_key_expansion in Aria_encrypt");
    return NULL;
  }

  return current_state->message;
}

// Function for global rounds operations
int Aria_round(state_t *init_state){
  key_t* key = init_state->key_struct;
  int return_value = 0;

  while(&(init_state->current_round) != &(key->nb_round)){
    return_value = Aria_round_key_addition(init_state);

    if(return_value == 1){
      printf("ERROR : Aria_round_key_addition in Aria_round");
      return 1;
    }

    return_value = Aria_substitution_layer(init_state);

    if(return_value == 1){
      printf("ERROR : Aria_substitution_layer in Aria_round");
      return 1;
    }

    return_value = Aria_diffusion_layer(init_state);

    if(return_value == 1){
      printf("ERROR : Aria_diffusion_layer in Aria_round");
      return 1;
    }

    init_state->current_round = init_state->current_round + 1;
  }

  return 0;
}

// Function for Step 1 inside rounds operations
int Aria_round_key_addition(state_t *current_state){
  //TODO
  return 0;
}

// Function for Step 2 inside rounds operations
int Aria_substitution_layer(state_t *current_state){
  current_state->current_round;

  //u8 sbox = Sbox_Tab[current_state->current_round];
// Faire le xor


  //TODO
  return 0;
}

// Function for Step 3 inside rounds operations
int Aria_diffusion_layer(state_t *current_state){
  //TODO
  return 0;
}

// Function for last steps after rounds opertaion
int Aria_key_expansion(state_t *current_state){
  //TODO
  return 0;
}