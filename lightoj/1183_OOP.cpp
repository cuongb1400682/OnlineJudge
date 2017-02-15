#include <bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

template <class Node>
class SegTree {
public:
    typedef typename Node::val_type val_type;

    template<class Iter>
    SegTree(Iter b, Iter e) {
        N = distance(b, e);
        vector<val_type> a(b, e);
        st.assign(4*N, Node());
        init(a.data(), 1, 0, N - 1);
    }

    SegTree(int N = 0) : N(N) {
        st.assign(4*N, Node());
    }

    SegTree(const val_type *a, int N) : N(N) {
        st.assign(4*N, Node());
        init(a, 1, 0, N - 1);
    }

    val_type query(int L, int R) { return query(1, 0, N - 1, L, R).val; }
    void update(int L, int R, val_type val) { update(1, 0, N - 1, L, R, val); }
    int size() const { return this->N; }


    ///////////////////
    void debug(int p, int L, int R, string indent = "") {
        if (L == R)
            cout << indent << "[" << R << "]";
        else
            cout << indent << "[" << L << ", " << R << "]";

        cout << " -> ";
        st[p].debug();

        if (L != R) {
            debug(left(p), L, (L + R) / 2, indent + "  .");
            debug(right(p), (L + R) / 2 + 1, R, indent + "  .");
        }
    }
    void debug() { debug(1, 0, N - 1); }
    ///////////////////

private:
    vector<Node> st;
    int N;

    int left(int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }

    void init(const val_type *a, int p, int L, int R) {
        if (L == R) {
            st[p].lazy = Node::HUNGRY;
            st[p].val = a[L];
            return;
        }

        init(a, left(p), L, (L + R) / 2);
        init(a, right(p), (L + R) / 2 + 1, R);

        st[p].select(st[left(p)], st[right(p)]);
    }

    Node query(int p, int L, int R, int u, int v) {
        if (v < L || R < u)
            return Node(Node::HUNGRY);

        if (u <= L && R <= v)
            return st[p];

        if (st[p].lazy != Node::HUNGRY) {
            val_type old_lazy = st[p].lazy;
            st[p].lazy = Node::HUNGRY;

            st[left(p)].lazy = old_lazy;
            st[left(p)].use(old_lazy);

            st[right(p)].lazy = old_lazy;
            st[right(p)].use(old_lazy);
        }

        return Node().select(
            query(left(p), L, (L + R) / 2, u, v),
            query(right(p), (L + R) / 2 + 1, R, u, v)
        );
    }

    void update(int p, int L, int R, int u, int v, val_type val) {
        if (v < L || R < u)
            return;

        if (u <= L && R <= v) {
            st[p].lazy = val;
            st[p].use(val);
            return;
        }

        if (st[p].lazy != Node::HUNGRY) {
            val_type old_lazy = st[p].lazy;
            st[p].lazy = Node::HUNGRY;

            st[left(p)].lazy = old_lazy;
            st[left(p)].use(old_lazy);

            st[right(p)].lazy = old_lazy;
            st[right(p)].use(old_lazy);
        }

        update(left(p), L, (L + R) / 2, u, v, val);
        update(right(p), (L + R) / 2 + 1, R, u, v, val);

        st[p].select(st[left(p)], st[right(p)]);
    }
};

struct IntNode {
    typedef int val_type;
    static const int HUNGRY;
    int val, lazy, sum;

    void debug() {
        if (lazy == HUNGRY)
            printf("(%d, *, %d)\n", val, sum);
        else
            printf("(%d, %d, %d)\n", val, lazy, sum);
    }

    IntNode(int val = int(), int lazy = HUNGRY) :
        val(val), lazy(lazy), sum(1) {}

    IntNode& select(const IntNode& a, const IntNode& b) {
        sum = 1;
        if (a.val == HUNGRY)
            val = b.val;
        else if (b.val == HUNGRY)
            val = a.val;
        else {
            val = a.val + b.val;
            sum = a.sum + b.sum;
        }
        return *this;
    }

    void use(int lazyVal) {
        val = sum * lazyVal;
    }
};

const int IntNode::HUNGRY = INF;

SegTree<IntNode> s;
int T;
vector<int> arr;

int main(void) {
    freopen("input.txt", "rt", stdin);
    scanf("%d", &T);
    for (int caseNo = 1, qType, i, j, value, n, q; caseNo <= T; caseNo++) {
        scanf("%d %d", &n, &q);
        arr.assign(n, 0);
        s = SegTree<IntNode>(arr.begin(), arr.end());
        printf("Case %d:\n", caseNo);
        while (q--) {
            scanf("%d %d %d", &qType, &i, &j);
            if (qType == 1) {
                scanf("%d", &value);
                s.update(i, j, value);
            } else {
                int len = j - i + 1;
                int qVal = s.query(i, j);
                int g = __gcd(len, qVal);
                qVal /= g; len /= g;
                if (len > 1)
                    printf("%d/%d\n", qVal, len);
                else
                    printf("%d\n", qVal);
            }
        }
    }
    return 0;
}
