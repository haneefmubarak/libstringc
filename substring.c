#include "stringc.h"

int str_subkey (const char *string, const char *key, char ***substrings) {
	int	matches = 0,
		arraysize = 16,
		x = 0,
		y = 0,
		lastx = 1,
		exit = 0;

	void *oldptr;	// in case we need to free after a realloc

	*substrings = malloc (arraysize);

	if (!(*substrings)) {
		return -1;
	}

	do {
		x = strcspn ((string + x), key);
		y = x - y;

		if (((*substrings)[matches] = strndup ((string + x), y))) {
			// if we fail, clear the entire array
			for (x = 0; x < matches; x++) {
				free ((*substrings)[x]);
			}

			free (*substrings);
			return -1;
		}

		if (lastx != x) {
			matches++;		// next match

			if (matches < arraysize) {
				oldptr = *substrings;
				arraysize += 16;
				*substrings = realloc (*substrings, arraysize);

				if (!(*substrings)) {
					// if we fail, free the entire thing
					*substrings = oldptr;

					matches--;
					for (x = 0; x < matches; x++) {
						free ((*substrings)[x]);
					}

					free (*substrings);
					return -1;
				}
			}

			x += 2;			// skip matched char
			lastx = y = x;		// use to find displacement
		} else {
			exit = 1;
		}
	} while (!exit);

	return matches;
}
