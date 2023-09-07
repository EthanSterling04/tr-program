#include "translate.h"

#include <stddef.h>
#include <stdlib.h>

// Helper function for interpreting escapes. Given the character that
// follows a backslash, returns the character that the combination
// should be replaced with. Recognizes the seven standard C escapes, and
// maps every other character to itself.
char interpret_escape(char c)
{
    switch (c) {
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case 'n': return '\n';
    case 'r': return '\r';
    case 't': return '\t';
    case 'v': return '\v';
    default:  return c;
    }
}

size_t charseq_length(const char* src)
{
    size_t result = 0;
    size_t i = 0;
    while (src[i] != '\0') {
        if (src[i+1] == '-' && src[i+2] != '\0') {
            if (src[i] > src[i+2]) {
                result += 0;
            }
            else {
                result += src[i+2] - src[i] + 1;
            }
            i += 3;
        }
        else if (src[i] == '\\' && src[i+1] != '\0') {
            result++;
            i += 2;
        }
        else {
            result += 1;
            i++;
        }
    }

    return result;
}

char* expand_charseq(const char* src)
{
    char* const dst = malloc(charseq_length(src) + 1);
    if (!dst) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;

    while (src[i] != '\0') {
        if (src[i+1] == '-' && src[i+2] != '\0') {
            int start = src[i];
            int end = src[i+2];
            while (start <= end) {
                dst[j] = start;
                j++;
                start++;
            }
            i += 3;
        }
        else if (src[i] == '\\' && src[i+1] != '\0') {
            dst[j] = interpret_escape(src[i+1]);
            j++;
            i += 2;
        }
        else {
            dst[j] = src[i];
            j++;
            i++;
        }
    }

    dst[j] = '\0';

    return dst;
}

char translate_char(char c, const char* from, const char* to)
{
    for (size_t i = 0; from[i] != '\0'; i++) {
        if (from[i] == c) {
            c = to[i];
            break;
        }
    }

    return c;
}

void translate(char* s, const char* from, const char* to)
{
    for (size_t i = 0; s[i] != '\0'; i++) {
        s[i] = translate_char(s[i], from, to);
    }
}

