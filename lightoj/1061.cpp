#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
using namespace std;

typedef pair<int,int> ii;

#define INF 0x3f3f3f3f

vector<ii> states[92];
char queen[9][9];
int n_state,n,dp[1<<16],cost[8][8];

void eightqueen(char matrix[9][9],int r,int row,int up,int down){
    if(r>=8){
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++)
                if(matrix[i][j]=='q')
                    states[n_state].push_back(ii(i,j));
        }
        n_state++;
        return;
    }
    for(int c=0;c<8;c++){
        int cup=r+c;
        int cdown=7+r-c;
        if(((row>>c)&1)||((up>>cup)&1)||((down>>cdown)&1))
            continue;
        matrix[r][c]='q';
        eightqueen(matrix,r+1,row|(1<<c),up|(1<<cup),down|(1<<cdown));
        matrix[r][c]='.';
    }        
}

int solve(int st){
    if(dp[st]!=-1)return dp[st];
    int ans=INF;

    int _st1=st&(0xFF);
    int _st2=(st>>8)&(0xFF);

    for(int st1=_st1;st1>0;){
        int i=31-__builtin_clz(st1);
        for(int st2=_st2;st2>0;){
            int j=31-__builtin_clz(st2);
            ans=min(ans,solve(st-(1<<i)-(1<<(j+8)))+cost[i][j]);
            st2-=(1<<j);
        }
        break; // no need to consider further.
    }

    return dp[st]=ans;
}

int main(){
    int n_test;
    memset(queen,'.',sizeof(queen));
    n_state=0;
    eightqueen(queen,0,0,0,0);
    scanf("%d",&n_test);
    for(int no=1;no<=n_test;no++){
        vector<ii> vec;
        for(int i=0;i<8;i++){
            scanf("%s",queen[i]);
            for(int j=0;j<8;j++)
                if(queen[i][j]=='q'){
                    vec.push_back(ii(i,j));
                }
        }
        int ans=INF,istate;
        for(int si=0;si<92;si++){
            istate=(1<<16)-1;
            memset(cost,0,sizeof(cost));
            for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                    int x1=states[si][i].first;
                    int y1=states[si][i].second;
                    int x2=vec[j].first;
                    int y2=vec[j].second;
                    int up1=x1+y1;
                    int down1=7+x1-y1;
                    int up2=x2+y2;
                    int down2=7+x2-y2;                    
                    if((x1==x2)&&(y1==y2)){
                        istate&=~((1<<i)|(1<<(8+j)));
                        cost[i][j]=0;
                    }else if((x1==x2)||(y1==y2)||(up1==up2)||(down1==down2)){
                        cost[i][j]=1;
                    }else{
                        cost[i][j]=2;
                    }
                }
            }
            memset(dp,-1,sizeof(dp));
            dp[0]=0;
            ans=min(ans,solve(istate));
        }
        printf("Case %d: %d\n",no,ans);
    }
    return 0;
}
