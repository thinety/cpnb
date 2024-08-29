#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

template <u64 M>
struct modint {
    u64 x;
    modint() {}
    modint(u64 x_) : x(x_ % M) {}

    friend modint operator+(modint a, modint b) {
        return (a.x + b.x) % M;
    }
    friend modint operator-(modint a, modint b) {
        return (a.x + M - b.x) % M;
    }
    friend modint operator*(modint a, modint b) {
        return (a.x * b.x) % M;
    }
};

using mint = modint<998244353>;

struct LazySegtree {
    using Node = struct {
        mint sum;
        u32 len;
    };
    static Node merge(Node const& node1, Node const& node2) {
        Node node;
        node.sum = node1.sum + node2.sum;
        node.len = node1.len + node2.len;
        return node;
    }

    using Action = struct {
        mint b, c;
    };
    static void apply_action(Action const& action, Node& node) {
        node.sum = action.b * node.sum + action.c * node.len;
    }
    static void merge_action(Action const& parent_action, Action& action) {
        tie(action.b, action.c) = make_tuple(
            parent_action.b * action.b,
            parent_action.b * action.c + parent_action.c
        );
    }
    static Action default_action() {
        Action action;
        action.b = 1;
        action.c = 0;
        return action;
    }

    using Args = struct {};
    using Output = mint;
    static Output extract(Args const& args, Node const& node) {
        return node.sum;
    }
    static Output combine(Args const& args, Output const& output1, Output const& output2) {
        return output1 + output2;
    }
    static Output neutral(Args const& args) {
        return 0;
    }

    template <typename F>
    static void build(F const& f, Node* data, Action* lazy, size_t i, size_t bot, size_t top) {
        size_t mid = (bot + top + 1) / 2;

        size_t i1 = i + 1;
        size_t i2 = i + 2 * (mid - bot);

        lazy[i] = default_action();

        if (bot + 1 == top) {
            data[i] = f(bot);
            return;
        }

        build(f, data, lazy, i1, bot, mid);
        build(f, data, lazy, i2, mid, top);

        data[i] = merge(data[i1], data[i2]);
    }

    static void update(Action const& action, Node* data, Action* lazy, size_t l, size_t r, size_t i, size_t bot, size_t top) {
        size_t mid = (bot + top + 1) / 2;

        size_t i1 = i + 1;
        size_t i2 = i + 2 * (mid - bot);

        if (l <= bot && top <= r) {
            merge_action(action, lazy[i]);
        }

        apply_action(lazy[i], data[i]);

        if (bot + 1 != top) {
            merge_action(lazy[i], lazy[i1]);
            merge_action(lazy[i], lazy[i2]);
        }

        lazy[i] = default_action();

        if ((l <= bot && top <= r) || r <= bot || top <= l) {
            return;
        }

        update(action, data, lazy, l, r, i1, bot, mid);
        update(action, data, lazy, l, r, i2, mid, top);

        data[i] = merge(data[i1], data[i2]);
    }

    static Output query(Args const& args, Node* data, Action* lazy, size_t l, size_t r, size_t i, size_t bot, size_t top) {
        size_t mid = (bot + top + 1) / 2;

        size_t i1 = i + 1;
        size_t i2 = i + 2 * (mid - bot);

        if (r <= bot || top <= l) {
            return neutral(args);
        }

        apply_action(lazy[i], data[i]);

        if (bot + 1 != top) {
            merge_action(lazy[i], lazy[i1]);
            merge_action(lazy[i], lazy[i2]);
        }

        lazy[i] = default_action();

        if (l <= bot && top <= r) {
            return extract(args, data[i]);
        }

        return combine(
            args,
            query(args, data, lazy, l, r, i1, bot, mid),
            query(args, data, lazy, l, r, i2, mid, top)
        );
    }

    unique_ptr<Node[]> data_;
    unique_ptr<Action[]> lazy_;
    size_t len_;

    template <typename F>
    void init(F const& f, size_t len) {
        len_ = len;
        data_.reset(new Node[2*len_-1]);
        lazy_.reset(new Action[2*len_-1]);
        build(f, &data_[0], &lazy_[0], 0, 0, len_);
    }

    void update(Action const& action, size_t l, size_t r) {
        update(action, &data_[0], &lazy_[0], l, r, 0, 0, len_);
    }

    Output query(Args const& args, size_t l, size_t r) {
        return query(args, &data_[0], &lazy_[0], l, r, 0, 0, len_);
    }
};

int main() {
    u32 N, Q;
    cin >> N >> Q;

    vector<u32> A(N);
    for (auto& Ai : A) cin >> Ai;

    LazySegtree seg; seg.init(
        [&] (auto i) -> LazySegtree::Node {
            return {
                .sum = A[i],
                .len = 1,
            };
        },
        N
    );

    for (u32 q = 0; q < Q; ++q) {
        u32 T; cin >> T;
        if (T == 0) {
            u32 L, R; u64 B, C;
            cin >> L >> R >> B >> C;
            seg.update({ .b=B, .c=C }, L, R);
        }
        else { // T == 1
            u32 L, R; cin >> L >> R;
            cout << seg.query({}, L, R).x << "\n";
        }
    }
}
