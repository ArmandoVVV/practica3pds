/*
 * notes.h
 *
 *  Created on: Nov 11, 2022
 *      Author: armando
 */

#ifndef NOTES_H_
#define NOTES_H_


void sound_note(uint32_t note);

uint16_t* get_note_A(void);
uint16_t* get_note_B(void);
uint16_t* get_note_C(void);
uint16_t* get_note_D(void);
uint16_t* get_note_E(void);
uint16_t* get_note_F(void);
uint16_t* get_note_G(void);

void set_current_note(uint16_t* note);
uint16_t* get_current_note(void);

void set_sound_index(uint32_t value);
uint32_t get_sound_index(void);

void set_end_flag(bool_t value);
bool_t get_end_flag(void);

uint16_t* get_next_note(void);

uint16_t* get_next_partiture_note(void);

#endif /* NOTES_H_ */
