#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std;

char s1[20],s2[20];

int main(){
    while(scanf(" %s %s ",s1,s2)!=EOF){
        int n1=strlen(s1);
        int n2=strlen(s2);
        int a=0,b=0,c=0,d=0,q=0;
        for(int i=0;i<n1;i++){
            if(s1[i]=='+')
                a++;
            if(s1[i]=='-')
                b++;
        }
        for(int i=0;i<n2;i++){
            if(s2[i]=='+')
                c++;
            if(s2[i]=='-')
                d++;
        }
        q=n2-c-d;
        int ans=0;
        for(int st=0;st<(1<<q);st++){
            int plus=0,minus=0;
            for(int j=0;j<q;j++){
                if((st>>j)&1){
                    plus++;
                }else{
                    minus++;
                }
            }
            if(c+plus==a && d+minus==b)
                ans++;
        }
        printf("%.9f\n",(double)ans/(1<<q));
    }
    return 0;
}
