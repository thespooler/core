#ifndef MESSAGE_SIZE_H
#define MESSAGE_SIZE_H

struct message_size {
	uoff_t physical_size;
	uoff_t virtual_size;
	unsigned int lines;
};

/* Calculate size of message header. Leave the input point to first
   character in body. */
int message_get_header_size(struct istream *input, struct message_size *hdr,
			    bool *has_nuls_r);
/* Calculate size of message body. */
int message_get_body_size(struct istream *input, struct message_size *body,
			  bool *has_nuls_r);

/* Sum contents of src into dest. */
void message_size_add(struct message_size *dest,
		      const struct message_size *src);

/* Skip number of virtual bytes from buffer. last_cr_r is set to TRUE if the
   last character we skipped was '\r', meaning that the next character should
   be '\n', which shouldn't be treated as "\r\n". */
int message_skip_virtual(struct istream *input, uoff_t virtual_skip,
			 bool *last_cr_r);

#endif
