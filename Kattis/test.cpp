#include<bits/stdc++.h>
using namespace std;

int main() {
  printf("100000 200000\n");
  for(int i=1;i<=100000;i++){
    printf("1 1 100000\n");
  }
  for(int i=1;i<=100000;i++){
    printf("0 %d %d\n", i, i);
  }
}
