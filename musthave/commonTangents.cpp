

vector<Line> commonTangents(pt A, dbl rA, pt B, dbl rB) {
    vector<Line> res;
    pt C = B - A;
    dbl z = C.len2();
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2)  {
            dbl r = rB * j - rA * i;
            dbl d = z - r * r;
            if (ls(d, 0)) continue;
            d = sqrt(max(0.0l, d));
            pt magic = pt(r, d) / z;
            pt v(magic % C, magic * C); 
            dbl CC = (rA * i - v % A) / v.len2();
            pt O = v * -CC;
            res.pb(Line(O, O + v.rotate()));
        }
    }
    return res;
}

// HOW TO USE ::
// --      *D*---------------*F*    
// --     *...*-           -*...*  
// --    *.....* -       - *.....*  
// --   *.......*  -   -  *.......* 
// --   *...A...*   --    *...B...* 
// --   *.......*  -   -  *.......* 
// --    *.....* -       - *.....*  
// --     *...*-           -*...*   
// --      *C*---------------*E*    
// --  res = {CE, CF, DE, DF}

