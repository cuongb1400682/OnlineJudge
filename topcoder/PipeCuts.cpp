class PipeCuts {
public:
    double f(int n){
        return 0.5*n*(n-1);
    }
    double probability(vector<int> weldLocations, int L){
        int count=0;
        sort(weldLocations.begin(),weldLocations.end());
        for(int i=0;i<(int)weldLocations.size()-1;i++)
            for(int j=i+1;j<(int)weldLocations.size();j++){
                int cut1=weldLocations[i];
                int cut2=weldLocations[j];
                if(cut1>L||cut2-cut1>L||100-cut2>L)
                    count++;
            }
        return (double)count/f(weldLocations.size());
    }
};
