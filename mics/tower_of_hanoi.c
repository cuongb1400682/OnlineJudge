void toh_classic(int dish,int dest,int mid) {
    if(dish<=0) return;
    toh_classic(dish-1,mid,dest);
    int tt=6-(dest+mid);
    printf("dish[%d] %d->%d $%d\n",dish,tt,dest,cost[tt][dest]);
    toh_classic(dish-1,dest,tt);
}
