inline int readInt()
{
    int x = 0;
    char c = getchar();
    int sgn = 1;
    while(c != '-' && !('0' <= c && c <= '9')) c = getchar();
    if (c == '-')
    {
        sgn = -1;
        c = getchar();
    }
    while('0' <= c && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * sgn;
}

inline void writeInt(int x)
{
    if (x < 0) putchar('-'), x = -x;
    if (x >= 10) writeInt(x / 10);
    putchar(x % 10 + '0');
}
