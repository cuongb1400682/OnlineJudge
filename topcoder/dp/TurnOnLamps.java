class TurnOnLamps {
    boolean[][] adj, important, state;
    int n;

    int dfs(int p, int u, int t, ArrayList<Integer> a) {
        a.add(u);
        if (u == t)
            return 0;
        for (int v = 0; v < n; v++) {
            if (important[u][v] && state[u][v])
                continue;
            if (v != p && adj[u][v]) {
                int ans = dfs(u, v, t, a) + (important[u][v] ? 1 : 0);
                if (a.get(a.size() - 1) == t)
                    return ans;
            }
        }
        a.remove(a.size() - 1);
        return 0;
    }

    ArrayList<Integer> getBestWay() {
        ArrayList<Integer> ans = new ArrayList<>();
        ArrayList<Integer> tmp = new ArrayList<>();
        int cnt_ans = 0;
        for (int u = 0; u < n; u++)
            for (int v = u + 1; v < n; v++) {
                tmp.clear();
                int cnt_tmp = dfs(u, u, v, tmp);
                if (!tmp.isEmpty() && tmp.get(tmp.size() - 1) == v) {
                    if (cnt_tmp > cnt_ans) {
                        ans = (ArrayList<Integer>) tmp.clone();
                        cnt_ans = cnt_tmp;
                    }
                }

            }
        ans.trimToSize();
        return ans;
    }

    public int minimize(int[] roads, String initState, String isImportant) {
        int ans = 0;
        n = roads.length + 1;
        adj = new boolean[n][n];
        state = new boolean[n][n];
        important = new boolean[n][n];
        for (int i = 0; i < roads.length; i++) {
            adj[roads[i]][i + 1] = true;
            adj[i + 1][roads[i]] = true;
            state[roads[i]][i + 1] = initState.charAt(i) == '1';
            state[i + 1][roads[i]] = initState.charAt(i) == '1';
            important[roads[i]][i + 1] = isImportant.charAt(i) == '1';
            important[i + 1][roads[i]] = isImportant.charAt(i) == '1';
        }
        for (;; ans++) {
            ArrayList<Integer> bestWay = getBestWay();
            if (bestWay.isEmpty())
                break;
            for (int i = 0; i < bestWay.size() - 1; i++) {
                int u = bestWay.get(i);
                int v = bestWay.get(i + 1);
                state[u][v] = !state[u][v];
                state[v][u] = !state[v][u];
            }
        }
        return ans;
    }
}
