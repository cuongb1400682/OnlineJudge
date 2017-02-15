struct CtuRobots {
    double maxDist(int B, vector<int> cost, vector<int> cap) {
        int n=cost.size();
        for(int i=0;i<n-1;i++)
            for(int j=i+1;j<n;j++)
                if(cap[i]>cap[j]) {
                    swap(cost[i],cost[j]);
                    swap(cap[i],cap[j]);
                }

        static double f[501][10001];
        ms(f[0],0);
        for(int i=1;i<=n;i++) {
            for(int j=0;j<=B;j++) {
                f[i][j]=f[i-1][j];
                if(j>=cost[i-1])
                    f[i][j]=max(f[i][j],f[i-1][j-cost[i-1]]/3.0+cap[i-1]);
            }
        }
        return f[n][B]/2.0;
    }
};
