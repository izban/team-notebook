// !!! warning !!! not flexible epsilons in "<"
struct pt
{
    dbl x, y;
    pt(){}
    pt(dbl xx, dbl yy): x(xx), y(yy) {}
    void read() { double xx, yy; scanf("%lf%lf", &xx, &yy); x = xx, y = yy; }
};

inline pt operator + (pt p1, pt p2) { return pt(p1.x + p2.x, p1.y + p2.y); }
inline pt operator - (pt p1, pt p2) { return pt(p1.x - p2.x, p1.y - p2.y); }
inline pt operator * (pt p, dbl c) { return pt(p.x * c, p.y * c); }
inline pt operator * (dbl c, pt p) { return pt(p.x * c, p.y * c); }

inline dbl len(pt p) { return sqrt(p.x * p.x + p.y * p.y); }
inline dbl dist(pt p1, pt p2) { dbl dx = p1.x - p2.x; dbl dy = p1.y - p2.y; return sqrt(dx * dx + dy * dy); }
inline dbl scal(pt p1, pt p2) { return p1.x * p2.x + p1.y * p2.y; }
inline dbl vect(pt p1, pt p2) { return p1.x * p2.y - p1.y * p2.x; }
inline bool operator < (pt p1, pt p2) { return p1.x < p2.x - eps || (p1.x < p2.x + eps && p1.y < p2.y - eps); }
