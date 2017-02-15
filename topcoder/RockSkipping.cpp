class RockSkipping{
public:
    double f[105][105];
    string pads;
    
    double solve(int nJmp,int y,string idn=""){
        if(pads[y]=='X'){
            return 0.0;
        }
        if(nJmp==0){
            return 1.0;
        }
        if(f[nJmp][y]!=-1)
            return f[nJmp][y];
        double ans=0.0;
        for(int i=1;i<=nJmp;i++){
            ans+=solve(nJmp-1,(y+i)%pads.size(),idn+".")/nJmp;
        }
        return f[nJmp][y]=ans;
    }
    
    double probability(string pads, int maxDist){
        this->pads=pads;
        for(int i=0;i<105;i++)
            for(int j=0;j<105;j++)
                f[i][j]=-1;
        return solve(maxDist,0)*100.0;
    }
};
