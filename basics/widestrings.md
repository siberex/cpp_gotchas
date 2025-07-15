# Wide strings

TLDR: Do not use wide strings or wide characters.

Exceptions:
- [locale::toupper](https://en.cppreference.com/w/cpp/locale/toupper.html) / [tolower](https://en.cppreference.com/w/cpp/locale/tolower.html).
    Currently, there is no way to do it without wide strings in C++ stdlib (without importing [ICU](https://github.com/unicode-org/icu) or [Boost.Locale](https://github.com/boostorg/locale)).


## Narrow strings: `std::string`, `char`

`std::string` = sequence of `char`

Encoding: any. Always assume UTF-8.

Use `unsigned char` to avoid sign-casting errors. 

`char` is always one-byte length.


## Wide strings `std::wstring`, `wchar_t`

`std::wstring` = sequence of `wchar_t`

Encoding: UTF-16 or UTF-32.

See also: [deprecated wbuffer_convert](https://en.cppreference.com/w/cpp/locale/wbuffer_convert.html)

Legacy type. Could be used to support special cases:
- Win32 APIs
- Java JNI mappings. Java strings are UTF-16-encoded sequences of fixed-width 16-bit character entities (UCS-2), with [Surrogates](http://en.wikipedia.org/wiki/Universal_Character_Set_characters#Surrogates) outside U+FFFF range represented by character pairs.

Be aware: `wchar_t` is extremely system-dependent!

On Linux, `wchar_t` is 4-bytes wide, and represents text in the UTF-32 encoding (regardless of the current locale).

In MSVC [wchar_t](https://learn.microsoft.com/en-us/cpp/cpp/char-wchar-t-char16-t-char32-t) is 2-bytes wide.
