#define MAX_V 20001

class DiceThrows{
public:
    double probA[2][MAX_V],probB[2][MAX_V];

    void calcProb(int numDice,
                  vector<int> sides,
                  double prev[MAX_V],
                  double prob[MAX_V]){
        for(int j=0;j<MAX_V;j++)
            prob[j]=0;
        for(int j=0;j<MAX_V;j++){
            if(prev[j]==0)continue;
            for(int k=0;k<6;k++){
                if(j+sides[k]>=MAX_V)continue;
                prob[j+sides[k]]+=prev[j]/6.0;
            }
        }
    }

    void getNonZero(double prob[MAX_V],int numDice,vector<int> &sum){
        for(int i=0;i<MAX_V;i++)
            if(prob[i]>0.0)
                sum.push_back(i);
    }
    
    double winProbability(int numDiceA, vector<int> sidesA,
                          int numDiceB, vector<int> sidesB){
        vector<int> sumA,sumB;

        for(int i=0;i<MAX_V;i++){
            probA[0][i]=0;
            probB[0][i]=0;
        }
        
        probA[0][0]=1;
        probB[0][0]=1;

        for(int i=1;i<=numDiceB;i++)
            calcProb(numDiceB,sidesB,probB[(i-1)&1],probB[i&1]);
        for(int i=1;i<=numDiceA;i++)
            calcProb(numDiceA,sidesA,probA[(i-1)&1],probA[i&1]);
        
        getNonZero(probA[numDiceA&1],numDiceA,sumA);
        getNonZero(probB[numDiceB&1],numDiceB,sumB);

        double ans=0.0;
        for(int i=0;i<sumA.size();i++)
            for(int j=0;j<sumB.size();j++)
                if(sumA[i]>sumB[j])
                    ans+=probA[numDiceA&1][sumA[i]]*probB[numDiceB&1][sumB[j]];
        return ans;
    }
};

