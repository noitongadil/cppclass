#include "hw06.h"
#include <iostream>

// Pre-conditions: none
// Post-conditions: none
// Returns: number of bytes in the string pointed to by str,
//          excluding the terminating null byte ('\0')
size_t cppclass::strlen(const char *str) {
        size_t size = 0;
        while (*str != '\0')  {
                size += sizeof(*str);
                str++;
        }
        return size;
}

// Pre-conditions: none
// Post-conditions: none
// Returns: Searches for the first occurrence of the character c
//          (an unsigned char) in the string pointed to, by the
//          argument str.
//
//          If character doesn't exist, returns nullptr
//
//          Example: str = "asdf", c = 'a',
//                   returns pointer to 0th element of string
//          Example: str = "asdf", c = 'f',
//                   returns pointer to 3rd element of string
//          Example: str = "asdf", c = 'g',
//                   returns nullptr
const char *cppclass::strchr(const char *str, char c) {
        while (*str != '\0') {
                if (*str == c) {
                        return str;
                }
                str++;
        }
        return nullptr;
}

// Pre-conditions: The strings may not overlap, and the destination
//                 string dest must be large enough to receive the
//                 copy.
// Post-conditions: The strcpy() function copies the string pointed
//                  to by src, including the terminating null byte
//                  ('\0'), to the buffer pointed to by dest.
// Returns: return a pointer to the destination string dest
char *cppclass::strcpy(char *dest, const char *src) {
        char *dest_start = dest;
        while (*src != '\0') {
                *dest = *src;
                dest++, src++;
        }
        *dest = *src;
        return dest_start;
}

// Pre-conditions: none
// Post-conditions: none
// Returns: The  strstr() function finds the first occurrence of
//          the substring needle in the string haystack.  The
//          terminating null bytes ('\0') are not compared.
//
//          These functions return a pointer to the beginning of
//          the located substring, or nullptr if the substring is
//          not found.
char *cppclass::strstr(const char *haystack, const char *needle) {
        if (*needle == '\0') {
                return const_cast<char *>(haystack); // was haystack
        }
        const char *ptr = nullptr;
        const char *init_needle = needle;
        while (*haystack != '\0' && *needle != '\0') {
                if (*needle == *haystack) {
                        if (ptr == nullptr) {
                                ptr = haystack;
                        }
                        needle++, haystack++;
                } else if (ptr == nullptr) {
                        haystack++;
                } else {
                        ptr = nullptr;
                        needle = init_needle;
                }
        }
        if (*needle != '\0' && *haystack == '\0') {
                return nullptr;
        }
        return const_cast<char *>(ptr); // was ptr
}

// Pre-conditions: none
// Post-conditions: none
// Returns: The strspn() function calculates the length (in bytes)
//          of the initial segment of str which consists entirely
//          of bytes in accept.
//
//          Example: str="aardvark", accept="aeiouy" -> 2
//          Example: str="baboon", accept="aeiouy" -> 0
//          Example: str="yak", accept="aeiouy" -> 2
size_t cppclass::strspn(const char *str, const char *accept) {
        const char *og_accept = accept;
        size_t size = 0;
        int count = 0;
        while (*str != '\0') {
                while (*accept != '\0') {
                        if (*str == *accept) {
                                size++;
                                break;
                        }
                        accept++;
                }
                accept = og_accept;
                str++, count++;
                if (size != count) {
                        break;
                }
        }
        return size;
}

// Pre-conditions: none
// Post-conditions: none
// Returns: The strcmp() function compares the two strings
//          str1 and str2. It returns an integer less than,
//          equal to, or greater than zero if str1 is found,
//          respectively, to be less than, to  match,  or
//          be greater than str2.
int cppclass::strcmp(const char *str1, const char *str2) {
        int diff = 0;
        while (*str1 != '\0' || *str2 != '\0') {
                diff = *str1 - *str2;
                if (diff != 0) {
                        return diff;
                }
                str2++, str1++;
        }
        return diff;
}

// Pre-conditions: none
// Post-conditions: str is replaced in-place
// Returns: replaces all characters in passed-in string such
//          that any lower-case characters are translated
//          into upper-case characters.
void cppclass::upper(char *str) {
        while (*str != '\0') {
                if (*str >= 'a' && *str <= 'z') {
                        *str = *str - 'a' + 'A';
                }
                str++;
        }
}

// Pre-conditions: none
// Post-conditions: str is replaced in-place
// Returns: replaces all characters in passed-in string such
//          that any upper-case characters are translated
//          into lower-case characters.
void cppclass::lower(char *str) {
        while (*str != '\0') {
                if (*str >= 'A' && *str <= 'Z') {
                        *str = *str - 'A' + 'a';
                }
                str++;
        }
}
