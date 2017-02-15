#include<stdio.h>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;

int n,m;

int main(){
    while(scanf("%d%d",&n,&m)!=EOF){
        double ans=n;
        for(int i=1;i<=n-1;i++){
            ans-=pow((double)i/n,m);
        }
        printf("%.9lf\n",ans);
    }
    return 0;
}
