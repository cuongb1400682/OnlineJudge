/*
 * PROB: TopCoder - TCO13 Parallel Round 3B - AntlerSwapping
 * LANG: C++
 */

class AntlerSwapping {
public:
    int getmin(vector<int> antler1, vector<int> antler2, int capacity) {
        int n=antler2.size();
        bool can_circle[1<<n];
        int f[1<<n];
        int lim = 1<<n;

        memset(can_circle,false,sizeof can_circle);
        memset(f,0,sizeof f);

        for(int grp=0;grp<lim;grp++) {
            int ant[32]={0},n_ant=0;
            for(int j=0;j<n;j++)
                if(grp&(1<<j)) {
                    ant[n_ant++]=antler1[j];
                    ant[n_ant++]=antler2[j];
                }

            sort(ant,ant+n_ant);
            can_circle[grp]=true;
            for(int j=0;j<n_ant;j+=2)
                if(ant[j+1]-ant[j]>capacity) {
                    can_circle[grp]=false;
                    break;
                }
        }

        for(int grp=1;grp<lim;grp++) {
            for(int i=grp;i>0;i=(i-1)&grp) {
                if(!can_circle[i] || (i != grp && !can_circle[grp-i]))
                    continue;
                f[grp] = max(f[grp],1+f[grp-i]);
            }
        }

        if(f[lim-1]) return n-f[lim-1]; else return -1;
    }
};
