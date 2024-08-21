struct ChineseRemainderTheorem {
    map<u64, tuple<u64, u64>> primes;

    // returns false if the congruence system is inconsistent
    bool init(vector<tuple<u64, u64>> const& congruences_) {
        // avoid factoring the same m multiple times
        map<u64, vector<u64>> congruences;
        for (auto [a, m] : congruences_) {
            congruences[m].push_back(a);
        }

        for (auto& [m, as] : congruences) {
            for (auto [p, n] : factorize(m)) {
                for (auto a : as) {
                    // there is no overflow here because
                    // p^n is at most m
                    a %= pow_mod(p, n, 0);

                    auto it = primes.find(p);
                    if (it == primes.end()) {
                        primes.emplace(p, make_tuple(n, a));
                        continue;
                    }

                    auto [last_n, last_a] = it->second;
                    if (last_n < n) {
                        it->second = make_tuple(n, a);
                        swap(last_n, n);
                        swap(last_a, a);
                    }

                    if (a != last_a % pow_mod(p, n, 0)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    // returns true if the system of congruences guarantees
    // that the solution is unique (mod m)
    //
    // for example, if the (normalized) system is
    //
    // x === a1 (mod 2^3)
    // x === a2 (mod 3^2)
    //
    // then the solution is unique (mod 2^3 * 3^2), and also (mod 2^2 * 3^1),
    // but not (mod 2^4) or (mod 5^1)
    bool is_solution_mod_unique(u64 m) {
        for (auto [p, n] : factorize(m)) {
            auto it = primes.find(p);
            if (it == primes.end()) {
                return false;
            }

            auto [largest_n, _] = it->second;
            if (largest_n < n) {
                return false;
            }
        }

        return true;
    }

    // returns [a, p, n] such that
    // x === a[i] (mod p[i]^n[i])
    // and p[i] is prime for all i
    tuple<vector<u64>, vector<u64>, vector<u64>> get_congruences() {
        vector<u64> a;
        vector<u64> p;
        vector<u64> n;

        for (auto it : primes) {
            auto pi = it.first;
            auto [ni, ai] = it.second;

            a.push_back(ai);
            p.push_back(pi);
            n.push_back(ni);
        }

        return make_tuple(a, p, n);
    }
};

// https://redirect.cs.umbc.edu/~lomonaco/s08/441/handouts/GarnerAlg.pdf
struct Garner {
    u32 k;
    vector<u64> m;
    vector<u64> r;

    // p[i] must all be primes, and n[i] is the respective prime power
    void init(vector<u64> const& p, vector<u64> const& n) {
        k = p.size();
        assert(n.size() == k);

        m.resize(k);
        r.resize(k);

        for (u32 i = 0; i < k; ++i) {
            // if you have overflow here, all bets are off
            // p[i] and n[i] should be chosen so that p[i]^n[i]
            // fits in a native integer
            m[i] = pow_mod(p[i], n[i], 0);

            u64 prod = 1;
            for (u32 j = 0; j < i; ++j) {
                prod = (prod * m[j]) % m[i];
            }

            #warning "p[i] must be prime!"
            u64 phi = pow_mod(p[i], n[i]-1, 0) * (p[i]-1);

            r[i] = pow_mod(prod, phi-1, m[i]);
        }
    }

    // returns the digits of the solution in the mixed radix representation:
    // a = x[0] + x[1]*m[0] + x[2]*m[0]*m[1] + ... + x[k-1]*m[0]*m[1]*...*m[k-2]
    // you can use this later with `get_mod` to calculate the answer (mod M)
    vector<u64> solve(vector<u64> const& a) {
        assert(a.size() == k);

        vector<u64> x(k);
        for (u32 i = 0; i < k; ++i) {
            u64 temp = 0;
            for (u32 j = i; j > 0; --j) {
                temp = (temp * m[j-1]) % m[i];
                temp = (temp + x[j-1]) % m[i];
            }
            x[i] = (a[i] + m[i] - temp) % m[i];
            x[i] = (x[i] * r[i]) % m[i];
        }
        return x;
    }

    // gives the solution (mod M) to the CRT system, based on the
    // digits of the mixed radix representation
    //
    // note that if the answer (mod M) is not unique, you must guarantee
    // that it fits in m = m1*m2*...*mk (in other words, m must be big
    // enough so that overflow does not happen)
    //
    // if M == 0, uses the native u64 overflow (mod 2^64)
    u64 get_mod(vector<u64> const& x, u64 M) {
        assert(x.size() == k);

        u64 ans = 0;
        for (u32 i = k; i > 0; --i) {
            ans *= m[i-1];
            if (M != 0) ans %= M;
            ans += x[i-1];
            if (M != 0) ans %= M;
        }
        return ans;
    }
};
