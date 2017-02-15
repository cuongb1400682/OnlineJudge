class YetAnotherORProblem2 {
    int[][] f;
    int R, N;
    final int MOD = (int)(1e9+9);

    public int rec(int T, int nEqual) {
        if (f[T][nEqual] != -1) return f[T][nEqual];
        if (T == 0) return f[0][nEqual] = 1;
        long ans = 0;
        int p = T - 1;
        if (nEqual == 0) {
            ans = rec(T - 1, 0);
            ans += (long) N * rec(T - 1, 0) % MOD;
            ans %= MOD;
        } else if (nEqual == 1) {
            if ((R & (1 << p)) > 0) {
                ans = rec(T - 1, 0);
                ans += (long) rec(T - 1, 1);
                ans %= MOD;
                ans += (long) (N - 1) * rec(T - 1, 0) % MOD;
                ans %= MOD;
            } else {
                ans = rec(T - 1, 1); // all are 0
                ans += (long) rec(T - 1, 1) * (N - 1) % MOD;
                ans %= MOD;
            }
        } else /* nEqual == N */ {
            if ((R & (1 << p)) > 0) {
                ans = rec(T - 1, 0);
                ans += (long) rec(T - 1, 1) * N % MOD;
                ans %= MOD;
            } else {
                ans = rec(T - 1, nEqual);
            }
        }
        return f[T][nEqual] = (int) ans;
    }

    public int countSequences(int N, int R) {
        int nBit = 0;
        for (int i = R; i > 0; i >>>= 1)
            nBit++;
        f = new int[nBit + 5][N + 5];
        for (int i = 0; i < f.length; i++)
            Arrays.fill(f[i], -1);
        this.R = R;
        this.N = N;
        return rec(nBit, N);
    }
}
