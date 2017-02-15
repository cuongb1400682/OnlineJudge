#include <stdio.h>

int n, d, h;

int main() {
  while (~scanf("%d %d %d", &n, &d, &h)) {

    if ((n == 2 && (h != 1 || d != 1)) || (n >= 3 && (h < 1 || d < 2))) {
      printf("-1\n");
      continue;
    }
    
    if (d >= h && h >= (d / 2 + (d & 1))) {
      int u;
      
      for (u = 2; u <= h + 1; u++)
        printf("%d %d\n", u - 1, u);
      
      for (; u <= d + 1; u++)
        if (u == h + 2)
          printf("1 %d\n", u);
        else
          printf("%d %d\n", u - 1, u);

      for (; u <= n; u++)
        printf("%d %d\n", u, 1 + (h != 1));
    } else {
      printf("-1\n");
    }
    printf("\n");
  }
  return 0;
}


