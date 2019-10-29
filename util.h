#include <stdio.h>

#define ERROR_PROCESSING(err, comment) 														\
	do {																					\
		if (err.gerr) {																		\
			fprintf(stderr, "%s (%s) : %s\n", comment, g_quark_to_string(err.quark),		\
							err.gerr->message);												\
			g_error_free(err.gerr);															\
		}																					\
	} while(0)

#define ERROR_SET_MSG(err, msg)  g_set_error_literal(&(err.gerr), err.quark, 0, msg)
struct Error {
	GError *gerr;
	GQuark quark;
};

struct Error init_domain(const char *domain) {
	struct Error err = {
		.gerr = NULL,
		.quark = g_quark_from_static_string(domain)
	};
	return err;
}

int64_t get_filesize(FILE *fptr) {
	fseeko(fptr, 0, SEEK_END);
	return ftello(fptr);
}

