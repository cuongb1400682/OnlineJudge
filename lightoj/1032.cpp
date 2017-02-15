#include<stdio.h>

typedef long long ll;
/*
  f[n] - the total number of 1 adj bit of all binary string of length n
  (counting merely the significant bits)

  is calculated by the formula:
        n-2
  f[n]=sigma(f[i]) + {2^(n-2) + f[n-1]}
        i=2

  with the base cases are:
  f[0] = f[1] = 0
  f[2] = 1
        
  const ll f[]={0,0,1,3,8,20,48,112,256,576,1280,2816,6144,13312,28672,
  61440,131072,278528,589824,1245184,2621440,5505024,
  11534336,24117248,50331648,104857600,218103808,
  452984832,939524096,1946157056,4026531840,8321499136,
  17179869184};
*/

/*
  p[n] = f[1]+f[2]+...+f[n]         
 */
const ll p[]={0,0,1,4,12,32,80,192,448,1024,2304,5120,11264,24576,53248,
              114688,245760,524288,1114112,2359296,4980736,10485760,
              22020096,46137344,96468992,201326592,419430400,872415232,
              1811939328,3758096384,7784628224,16106127360};

int cnt(int n){
    int ans=0;
    while(n>0){
        ans++;
        n>>=1;
    }
    return ans;
}

int main(){
    int n_case;
    scanf("%d",&n_case);
    for(int no=1;no<=n_case;no++){
        int number;
        scanf("%d",&number);
        ll ans=0,tot=0;
        int c=0,i,curr=0,prev=0;
        for(i=cnt(number)-1;i>=0;i--){
            curr=(number&(1<<i))>0;
            if(curr){
                ans+=p[i];
                ans+=(1<<i)*tot;
                if(prev&&curr)
                    tot++;
            }
            prev=curr;
        }
        ans+=tot;
        printf("Case %d: %lld\n",no,ans);
    }
    return 0;
}
