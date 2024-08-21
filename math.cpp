u64 gcd(u64 a, u64 b) {
    i64 old_r = a, r = b;

    while (r != 0) {
        i64 q = old_r / r;
        tie(old_r, r) = make_tuple(r, old_r - q * r);
    }

    return old_r;
}

u64 lcm(u64 a, u64 b) {
    return a * (b / gcd(a, b));
}

// solution of a*x + b*y = gcd(a,b)
// returns gcd(a,b) > 0
i64 extended_gcd(i64 a, i64 b, i64& x, i64& y) {
    i64 old_r = a, r = b;
    i64 old_s = 1, s = 0;
    i64 old_t = 0, t = 1;

    while (r != 0) {
        i64 q = old_r / r;
        tie(old_r, r) = make_tuple(r, old_r - q * r);
        tie(old_s, s) = make_tuple(s, old_s - q * s);
        tie(old_t, t) = make_tuple(t, old_t - q * t);
    }

    if (old_r < 0) {
        old_r = -old_r;
        old_s = -old_s;
        old_t = -old_t;
    }

    x = old_s;
    y = old_t;
    return old_r;
}

vector<tuple<u64, u64>> factorize(u64 n) {
    vector<tuple<u64, u64>> factors;
    for (u64 i = 2; i*i <= n; ++i) {
        if (n % i != 0) continue;
        u64 k = 0;
        while (n % i == 0) {
            n /= i;
            k += 1;
        }
        factors.emplace_back(i, k);
    }
    if (n > 1) { // prime
        factors.emplace_back(n, 1);
    }
    return factors;
}

// returns a^n (mod M)
// if M == 0, uses the native u64 overflow (mod 2^64)
u64 pow_mod(u64 a, u64 n, u64 M) {
    u64 ans = 1;
    while (n > 0) {
        if ((n & 1) != 0) {
            ans *= a;
            if (M != 0) ans %= M;
        }
        a *= a;
        if (M != 0) a %= M;
        n /= 2;
    }
    return ans;
}

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

    modint pow(u64 n) {
        return pow_mod(x, n, M);
    }

    modint inv() {
        #warning "M must be prime!"
        u64 phi = M-1;
        return pow_mod(x, phi-1, M);
    }
};
