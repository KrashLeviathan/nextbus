# Lecture Notes - March 11

## Assignment

Line of sight -- just go out from the character position and set
the cells to CAN_SEE.

## Memory management in C++

Have to use 'new' and 'delete' keywords when using C++ classes
for dynamic allocation.


character *c;

c = malloc(sizeof(*c));   // WRONG

c = new character();      // Correct

delete c;



#ifndef PC_H
# define PC_H

# include <stdint.h>

# include "dims.h"

# ifdef __cplusplus
extern "C"
# endif

typedef struct dungeon dungeon_t;

typedef struct {
} pc_t;                   // Do this for everything

uint32_t pc_is_alive(dungeon *d);
void config_pc(dungeon_t *d);
uint32_t pc_next_pos(dungeon_t *d, pair_t dir);
void place_pc(dungeon_t *d);
void delete_pc(character_t *the_pc);

# ifdef __cplusplus
}

# include "character.h"

class pc : public character {
};

# endif
#endif






### Character class

Wrap all the properties with getters and setters so you can access
them with C code

character_get_y(const character_t *c);
character_set_y(const character_t *c);
etc.


Implementation:

int character_next_turn(character_t *c) {
  character *the_character = (character *) c;   // Must cast it in
                                                // every function implem.

  the_character->next_turn += (1000 / the_character->speed);
}


... or ... return ((character *) c)->symbol;
etc.



Makefile

- rename pc.c and npc.c to pc.cpp and npc.cpp





## Finishing up the String class in C++

