class PointSystem{
public:
    double f[500][500];
    
    double oddsOfWinning(int pointsToWin, int pointsToWinBy, int skill){
        double worse=(double)skill/100.0;
        double better=1.0-worse;
        for(int i=0;i<500;i++)
            for(int j=0;j<500;j++)
                f[i][j]=0;
        int limit=500;
        double ans=0.0;
        f[0][0]=1.0;
        for(int x=0;x<=limit;x++){
            int w=x,b=0;
            while(w>=0&&b<=limit){
                if(((w>=pointsToWin)||(b>=pointsToWin)) &&
                   (fabs(w-b)>=pointsToWinBy)){
                    if(w-b>=pointsToWinBy){
                        ans+=f[w][b];
                    }
                    //printf("(%d,%d)\n",w,b);
                }else{
                    f[w+1][b]+=f[w][b]*worse;
                    f[w][b+1]+=f[w][b]*better;
                }
                w--;
                b++;
            }
        }
        return ans;
    }
};

