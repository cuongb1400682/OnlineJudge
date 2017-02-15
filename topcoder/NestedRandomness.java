package solutions;

class NestedRandomness {
    public double probability(int N, int nestings, int target) {
        double[][] f = new double[N + 1][];
        for (int i = 0; i < f.length; i++)
            f[i] = new double[N + 1];
        for (int i = 0; i < N; i++)
            f[N][i] = 1.0 / N;
        for (int i = N; i >= N - nestings + 1; i--) {
            for (int j = 0; j < i; j++) {                
                for (int k = 0; k < j; k++) {
                    f[i - 1][k] += f[i][j] * 1.0 / j;
                }
            }
        }
        return f[N - nestings + 1][target];
    }
}
