struct CakeDivision {
    double calc(double L,double W,double p) {
        if(L<W) swap(L,W);
        if(p==1) return L/W;
        double ans=1e20;
        for(int i=1;i<p;i++) {
            ans=min(ans, max(calc(L*i/p,W,i), calc(L*(p-i)/p,W,p-i)));
            ans=min(ans, max(calc(L,W*i/p,i), calc(L,W*(p-i)/p,p-i)));
        }
        return ans;
    }

    double ratio(int length, int width, int pieces) {
        return CakeDivision::calc(length,width,pieces);
    }
};
