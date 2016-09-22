struct pt
{
    ll x, y;
    pt(){}
    pt(ll xx, ll yy): x(xx), y(yy) {}
    void read() { scanf("%lld%lld", &x, &y); }
};

inline pt operator + (pt p1, pt p2) { return pt(p1.x + p2.x, p1.y + p2.y); }
inline pt operator - (pt p1, pt p2) { return pt(p1.x - p2.x, p1.y - p2.y); }
inline pt operator * (pt p, ll c) { return pt(p.x * c, p.y * c); }
inline pt operator * (ll c, pt p) { return pt(p.x * c, p.y * c); }

inline dbl len(pt p) { return sqrt(p.x * p.x + p.y * p.y); }
inline dbl dist(pt p1, pt p2) { ll dx = p1.x - p2.x; ll dy = p1.y - p2.y; return sqrt(dx * dx + dy * dy); }
inline ll scal(pt p1, pt p2) { return p1.x * p2.x + p1.y * p2.y; }
inline ll vect(pt p1, pt p2) { return p1.x * p2.y - p1.y * p2.x; }
inline bool operator < (pt p1, pt p2) { return p1.x < p2.x || (p1.x <= p2.x && p1.y < p2.y); }
