#ifndef __UNICHAR_H
#define __UNICHAR_H

typedef uint32_t unichar_t;

extern const uint8_t *const uni_utf8_non1_bytes;

/* Returns number of characters in a NUL-terminated unicode string */
unsigned int uni_strlen(const unichar_t *str);
/* Translates UTF-8 input to UCS-4 output. Returns 0 if ok, -1 if input was
   invalid */
int uni_utf8_to_ucs4(const char *input, buffer_t *output);
/* Translates UCS-4 input to UTF-8 output. */
void uni_ucs4_to_utf8(const unichar_t *input, size_t len, buffer_t *output);
void uni_ucs4_to_utf8_c(unichar_t chr, buffer_t *output);

/* Returns 1 if *chr_r is set, 0 for incomplete trailing character,
   -1 for invalid input. */
int uni_utf8_get_char(const char *input, unichar_t *chr_r);
int uni_utf8_get_char_n(const void *input, size_t max_len, unichar_t *chr_r);
/* Returns UTF-8 string length with maximum input size. */
unsigned int uni_utf8_strlen_n(const void *input, size_t size);

/* Returns the number of bytes belonging to this partial UTF-8 character.
   Invalid input is returned with length 1. */
static inline unsigned int uni_utf8_char_bytes(char chr)
{
	/* 0x00 .. 0x7f are ASCII. 0x80 .. 0xC1 are invalid. */
	if ((uint8_t)chr < (192 + 2))
		return 1;
	return uni_utf8_non1_bytes[(uint8_t)chr - (192 + 2)];
}

#endif
