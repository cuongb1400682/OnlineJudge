package solutions;

class ChessKnight {
    final int[] dX = new int[]{-2, -1, 1, 2, 2, 1, -1, -2};
    final int[] dY = new int[]{1, 2, 2, 1, -1, -2, -2, -1};

    public double probability(int x, int y, int n) {
        double[][][] f = new double[n + 2][8][8];
        double ans = 0.0;
        x--;
        y--;
        f[0][x][y] = 1;
        for (int i = 0; i <= n - 1; i++) {
            for (x = 0; x < 8; x++) {
                for (y = 0; y < 8; y++) {
                    if (f[i][x][y] == 0) {
                        continue;
                    }
                    for (int j = 0; j < dX.length; j++) {
                        if (isValid(x + dX[j], y + dY[j])) {
                            f[i + 1][x + dX[j]][y + dY[j]] += f[i][x][y] * 0.125;
                        }
                    }
                }
            }
        }
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                ans += f[n][x][y];
            }
        }
        return ans;
    }

    private boolean isValid(int x1, int y1) {
        return x1 >= 0 && x1 <= 7 && y1 >= 0 && y1 <= 7;
    }
    
}
