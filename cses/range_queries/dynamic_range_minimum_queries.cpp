#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;

struct Segtree {
    using Node = u32;
    static Node merge(Node const& node1, Node const& node2) {
        return min(node1, node2);
    }

    using Action = u32;
    static void apply_action(Action const& action, Node& node) {
        node = action;
    }

    using Args = struct {};
    using Output = u32;
    static Output extract(Args const& args, Node const& node) {
        return node;
    }
    static Output combine(Args const& args, Output const& output1, Output const& output2) {
        return min(output1, output2);
    }
    static Output neutral(Args const& args) {
        return -1;
    }

    template <typename F>
    static void build(F const& f, Node* data, u32 i, u32 bot, u32 top) {
        u32 mid = (bot + top) / 2;
        u32 i1 = i + 1;
        u32 i2 = i + 2 * (mid - bot);

        if (bot + 1 == top) {
            data[i] = f(bot);
            return;
        }

        build(f, data, i1, bot, mid);
        build(f, data, i2, mid, top);

        data[i] = merge(data[i1], data[i2]);
    }

    static void update(Action const& action, Node* data, u32 pos, u32 i, u32 bot, u32 top) {
        u32 mid = (bot + top) / 2;
        u32 i1 = i + 1;
        u32 i2 = i + 2 * (mid - bot);

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

    static Output query(Args const& args, Node* data, u32 l, u32 r, u32 i, u32 bot, u32 top) {
        u32 mid = (bot + top) / 2;
        u32 i1 = i + 1;
        u32 i2 = i + 2 * (mid - bot);

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
    u32 len_;

    template <typename F>
    void init(F const& f, u32 len) {
        len_ = len;
        data_.reset(new Node[2*len_-1]);
        build(f, &data_[0], 0, 0, len_);
    }

    void update(Action const& action, u32 pos) {
        update(action, &data_[0], pos, 0, 0, len_);
    }

    Output query(Args const& args, u32 l, u32 r) {
        return query(args, &data_[0], l, r, 0, 0, len_);
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    u32 n, q;
    cin >> n >> q;

    vector<u32> x(n);
    for (auto& xi : x) cin >> xi;

    Segtree seg; seg.init(
        [&] (u32 i) -> Segtree::Node {
            return x[i];
        },
        n
    );

    while (q--) {
        u32 t;
        cin >> t;
        if (t == 1) {
            u32 k, u;
            cin >> k >> u;
            k--;
            seg.update(u, k);
        }
        else { // t == 2
            u32 a, b;
            cin >> a >> b;
            a--;
            cout << seg.query({}, a, b) << "\n";
        }
    }

    return 0;
}
