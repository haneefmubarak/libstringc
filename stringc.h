// libstringc
// the (missing) string library for c
//
// Copyright 2014 Haneef Mubarak
// All Rights Reserved

#pragma once

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int		str_subkey 		(const char *string,
					const char *key,
					char ***substrings);
