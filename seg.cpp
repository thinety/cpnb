#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

struct segtree {
    using Node = u64;
    static Node merge(Node const& node1, Node const& node2) {
        return node1 + node2;
    }

    using Action = u64;
    static void apply_action(Action const& action, Node& node) {
        node += action;
    }

    using Args = struct {};
    using Output = u64;
    static Output extract(Args const& args, Node const& node) {
        return node;
    }
    static Output combine(Args const& args, Output const& output1, Output const& output2) {
        return output1 + output2;
    }
    static Output neutral(Args const& args) {
        return 0;
    }

    template <typename F>
    static void build(F const& f, Node* data, size_t i, size_t bot, size_t top) {
        size_t mid = (bot + top + 1) / 2;

        size_t i1 = i + 1;
        size_t i2 = i + 2 * (mid - bot);

        if (bot + 1 == top) {
            data[i] = f(bot);
            return;
        }

        build(f, data, i1, bot, mid);
        build(f, data, i2, mid, top);

        data[i] = merge(data[i1], data[i2]);
    }

    static void update(Action const& action, Node* data, size_t pos, size_t i, size_t bot, size_t top) {
        size_t mid = (bot + top + 1) / 2;

        size_t i1 = i + 1;
        size_t i2 = i + 2 * (mid - bot);

        if (bot + 1 == top) {
            apply_action(action, data[i]);
            return;
        }

        if (pos < mid) {
            update(action, data, pos, i1, bot, mid);
        }
        else {
            update(action, data, pos, i2, mid, top);
        }

        data[i] = merge(data[i1], data[i2]);
    }

    static Output query(Args const& args, Node* data, size_t l, size_t r, size_t i, size_t bot, size_t top) {
        size_t mid = (bot + top + 1) / 2;

        size_t i1 = i + 1;
        size_t i2 = i + 2 * (mid - bot);

        if (r <= bot || top <= l) {
            return neutral(args);
        }

        if (l <= bot && top <= r) {
            return extract(args, data[i]);
        }

        return combine(
            args,
            query(args, data, l, r, i1, bot, mid),
            query(args, data, l, r, i2, mid, top)
        );
    }

    unique_ptr<Node[]> data_;
    size_t len_;

    template<typename F>
    segtree(F const& f, size_t len)
    {
        len_ = len;
        data_.reset(new Node[2*len_-1]);
        build(f, &data_[0], 0, 0, len_);
    }

    void update(Action const& action, size_t pos) {
        update(action, &data_[0], pos, 0, 0, len_);
    }

    Output query(Args const& args, size_t l, size_t r) {
        return query(args, &data_[0], l, r, 0, 0, len_);
    }
};

int main() {
    u32 N, Q;
    cin >> N >> Q;

    vector<u32> A(N);
    for (auto& Ai : A) cin >> Ai;

    segtree seg(
        [&] (auto i) {
            return A[i];
        },
        N
    );

    for (u32 q = 0; q < Q; ++q) {
        u32 T; cin >> T;
        if (T == 0) {
            u32 P, X; cin >> P >> X;
            seg.update(X, P);
        }
        else { // T == 1
            u32 L, R; cin >> L >> R;
            cout << seg.query({}, L, R) << "\n";
        }
    }
}
