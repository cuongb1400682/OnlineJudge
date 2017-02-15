class Collision{
public:
    double probability(vector<int> assignments, int ids){
        int sum=0;
        double prob1=1.0,prob2=1.0;
        for(int i=0;i<assignments.size();i++){
            for(int j=0;j<assignments[i];j++)
                prob2*=(double)(ids-sum-j)/(ids-j);
            sum+=assignments[i];            
        }
        if(sum>ids)return 0.0;
        for(int i=0;i<sum;i++)
            prob1*=(double)(ids-i)/ids;            
        if(prob2>prob1)
            return prob2-prob1;
        else
            return prob1-prob2;
    }
};
