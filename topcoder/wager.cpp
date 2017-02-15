class QuizShow {
public:
    int wager(vector<int> scores, int wager1, int wager2){
        int wager[]={0,wager1,wager2};
        int final_scores[3],final_winning=0,final_wager=0;
        for(wager[0]=0;wager[0]<=scores[0];wager[0]++){
            int winning=0;
            for(int state=0;state<8;state++){
                for(int i=0;i<3;i++){
                    if((state>>i)&1)
                        final_scores[i]=scores[i]+wager[i];
                    else
                        final_scores[i]=scores[i]-wager[i];
                }
                if(final_scores[0]>final_scores[1]&&
                   final_scores[0]>final_scores[2])
                    winning++;
            }
            if(winning>final_winning){
                final_winning=winning;
                final_wager=wager[0];
            }
        }
        return final_wager;
    }
};
