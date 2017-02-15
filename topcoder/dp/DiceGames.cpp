typedef long long ll;
struct DiceGames {
    ll countFormations(vector<int> a) {
        a.push_back(1);
        sort(a.begin(),a.end());
        ll f[100][100]={0};
        int n=a.size()-1;
        for(int i=1;i<=a[n];i++)
            f[n][i]=1;
        for(int i=n-1;i>=0;i--) {
            f[i][1]=0;
            for(int j=1;j<=a[i+1];j++)
                f[i][1]+=f[i+1][j];
            for(int j=2;j<=a[i];j++)
                f[i][j]=f[i][j-1]-f[i+1][j-1];
        }
        return f[0][1];
    }
};
