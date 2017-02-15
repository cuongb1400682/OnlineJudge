struct ContestSchedule {
    double expectedWinnings(vector<string> cts) {
        int s[100]={0},t[100]={0},p[100]={0},f[100]={0};
        int n=0;
        for(string ss : cts) {
            sscanf(ss.c_str(),"%d %d %d",&s[n],&t[n],&p[n]);
            n++;
        }
        for(int i=0;i<n-1;i++)
            for(int j=i+1;j<n;j++)
                if(t[i]>t[j]) {
                    swap(s[i],s[j]);
                    swap(t[i],t[j]);
                    swap(p[i],p[j]);
                }
        int ans=0;
        for(int i=0;i<n;i++) {
            f[i]=p[i];
            f[i]=max(f[i],f[i-1]);
            for(int j=0;j<n;j++)
                if(t[j]<=s[i])
                    f[i]=max(f[i],f[j]+p[i]);
            ans=max(ans,f[i]);
        }
        return ans/100.0;
    }
};
