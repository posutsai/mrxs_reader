#include <stdio.h>
#include <stdint.h>
#include <glib.h>
#include <string.h>
#include "util.h"

GKeyFile  *slide_open(char *filepath) {
	struct Error err = init_domain("Reading And Parsing File");
	FILE *fptr = fopen(filepath, "rb");
	if (fptr == NULL) {
		ERROR_SET_MSG(err, "File opening error");
		goto FAIL;
	}
	char *buf = NULL;
	int64_t size = get_filesize(fptr);
	fseeko(fptr, 0, SEEK_SET);
	buf = (char *)g_malloc(size + 1);
	if (!fread(buf, 1, size + 1, fptr)) {
		ERROR_SET_MSG(err, "Error happens when reading file.")
		goto FAIL;
	}
	int offset = 0;
	if (size >= 3 && memcmp(buf, "\xef\xbb\xbf", 3) == 0)
			offset = 3;
	GKeyFile *key_file = g_key_file_new();
	if (!g_key_file_load_from_data(key_file, buf + offset, size - offset, G_KEY_FILE_NONE, &err)) {
			g_key_file_free(key_file);
			goto FAIL;
	}

	g_free(buf);
	fclose(fptr);
	return key_file;
FAIL:
	/* ERROR_PROCESSING(err, "PARSE SLIDE ERROR"); */
	g_free(buf);
	fclose(fptr);
	return NULL;
}

int main(int argc, char *argv[]) {
	return 0;
}
