/* http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Map/skip-list-impl.html */

#include <bits/stdc++.h>
using namespace std;

#define REP(i,a,b) for(int i=int(a),n##i=int(b);i<=n##i;i++)
#define TR(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();it++)
#define ms(f,a) memset(f,a,sizeof(f))
#define DBG(S) cerr << "[" #S " = " << (S) << "]" << endl;
#define INF 0x3f3f3f3f
#define fi first
#define se second
#define pb push_back
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;

struct entry_t {
    int key,val;
    list<entry_t>::iterator left,right,down,up;
    entry_t(int key = 0, int val = 0) {
        this->key = key;
        this->val = val;
        left = right = down = up = (list<entry_t>::iterator) 0;
    }
};

typedef list<entry_t>::iterator p_entry_t;

const p_entry_t INULL = (p_entry_t) 0;

struct skip_list {
    list<entry_t> l;
    int height;
    p_entry_t head,tail;

    skip_list() { head = tail = INULL; }
    p_entry_t new_entry(int key, int val) {
        return l.insert(l.begin(), entry_t(key, val));
    }
};

enum {
    LEFT_RIGHT,
    UP_DOWN
};

void connect(p_entry_t a, p_entry_t b, int d = LEFT_RIGHT) {
    if(d == LEFT_RIGHT) {
        if(a != INULL) a->right = b;
        if(b != INULL) b->left = a;
    } else {
        if(a != INULL) a->down = b;
        if(b != INULL) b->up = a;
    }
}

void create(skip_list &lst) {
    lst.l.clear();
    lst.height = 1;
    lst.head = lst.new_entry(-INF, -INF);
    lst.tail = lst.new_entry(+INF, +INF);
    connect(lst.head, lst.tail);
}

p_entry_t find(const skip_list &lst, int key) {
    assert(lst.head != INULL);
    for(p_entry_t p = lst.head; ;) {
        while(p->right->val <= key)
            p = p->right;
        if(p->down != INULL)
           p = p->down;
        else
            return p;
    }
    return INULL;
}

void insert(skip_list &lst, int key, int val) {
    assert(lst.head != INULL);
    p_entry_t p,r,u;
    p=find(lst,key);
    if(p->key==key) {
        for(;p!=INULL && val!=p->val;p=p->up)
            p->val=val;
        return;
    }

    int h_tower=1;
    r=lst.new_entry(key,val);
    connect(r,p->right);
    connect(p,r);
    u=r;

    srand(clock());
    while(rand()&1) {
        if(h_tower>=lst.height) {
            connect(lst.new_entry(-INF,-INF),lst.head,UP_DOWN);
            connect(lst.new_entry(+INF,+INF),lst.tail,UP_DOWN);
            lst.head=lst.head->up;
            lst.tail=lst.tail->up;
            connect(lst.head,lst.tail);
            lst.height++;
        }
        for(;p->up==INULL;p=p->left)
            ;
        p=p->up;
        r=lst.new_entry(key,val);
        connect(r,p->right);
        connect(p,r);
        connect(r,u,UP_DOWN);
        u=r;
        h_tower++;
    }
}

void erase(skip_list &lst,int key) {
    assert(lst.head != INULL);
    p_entry_t p=find(lst,key),t;
    if(p->key==key) {
        for(;p != INULL; p=t) {
            t=p->up;
            connect(p->left,p->right);
            connect(p->up,p->down,UP_DOWN);
            lst.l.erase(p);
        }
    }
}

void print_list(const skip_list &lst,int width=5) {
    p_entry_t p=lst.head;
    while(p->down !=INULL)
        p=p->down;
    char chr_fmt[128],val_fmt[128];

    sprintf(chr_fmt,"%%%dc",width);
    sprintf(val_fmt,"%%%dd",width);

    for(;p!=INULL;p=p->right) {
        for(p_entry_t q=p;q!=INULL;q=q->up) {
            if(q->val==-INF)
                printf(chr_fmt,'-');
            else if(q->val==+INF)
                printf(chr_fmt,'+');
            else
                printf(val_fmt,q->val);
        }
        putchar('\n');
    }
}

skip_list s;

int main(void) {
    return 0;
}





