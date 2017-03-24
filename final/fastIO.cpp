#include <cstdio>
#include <algorithm>

/** Interface */

inline int readInt();
inline int readUInt();
inline bool isEof();

/** Read */

static const int buf_size = 100000;
static char buf[buf_size];
static int buf_len = 0, pos = 0;

inline bool isEof() {
    if (pos == buf_len) {
        pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
        if (pos == buf_len) return 1;
    }
    return 0;
}

inline int getChar() { return isEof() ? -1 : buf[pos++]; }

inline int readChar() {
    int c = getChar();
    while (c != -1 && c <= 32) c = getChar();
    return c;
}

inline int readUInt() {
    int c = readChar(), x = 0;
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = getChar();
    return x;
}

inline int readInt() {
    int s = 1, c = readChar();
    int x = 0;
    if (c == '-') s = -1, c = getChar();
    while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}


// 10M int [0..1e9)
// cin 3.02
// scanf 1.2
// cin sync_with_stdio(false) 0.71
// fastRead getchar 0.53
// fastRead fread 0.15
 
