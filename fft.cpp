u32 reverse(u32 x, u32 k) {
    u32 y = 0;
    for (u32 i = 0; i < k; ++i) {
        y <<= 1;
        y |= x & 1;
        x >>= 1;
    }
    return y;
}

template <typename T>
void fft(vector<T>& a, vector<u32> const& rev, vector<T> const& w) {
    u32 n = a.size();

    for (u32 i = 0; i < n; ++i) {
        if (i < rev[i]) {
            swap(a[i], a[rev[i]]);
        }
    }

    for (u32 k = 1; k < n; k *= 2) {
        for (u32 i = 0; i < n; i += 2*k) {
            for (u32 j = 0; j < k; j += 1) {
                tie(a[i+j], a[i+j+k]) = make_tuple(
                    a[i+j] + w[n/(2*k)*j] * a[i+j+k],
                    a[i+j] + w[n/(2*k)*(j+k)] * a[i+j+k]
                );
            }
        }
    }
}


struct DiscreteFourierTransform {
    u32 n;
    vector<u32> permutation;
    vector<C> omega;
    vector<C> omega_conj;

    u32 init(u32 size) {
        n = 1;
        u32 k = 0;
        while (n < size) {
            n *= 2;
            k += 1;
        }

        permutation.resize(n);
        for (u32 i = 0; i < n; ++i) {
            permutation[i] = reverse(i, k);
        }

        omega.resize(n);
        omega_conj.resize(n);
        for (u32 i = 0; i < n; ++i) {
            F a = cos(2*PI*i/n);
            F b = sin(2*PI*i/n);
            omega[i] = {a, b};
            omega_conj[i] = {a, -b};
        }

        return n;
    }

    vector<C> dft(vector<C> x) {
        assert(x.size() == n);
        fft(x, permutation, omega_conj);
        return x;
    }

    vector<C> idft(vector<C> x) {
        assert(x.size() == n);
        fft(x, permutation, omega);
        for (auto& xi : x) xi /= n;
        return x;
    }
};


u64 primitive_root(u64 p) {
    #warning "p must be prime!"
    u64 phi = p-1;

    for (u64 ans = 2; ans < p; ++ans) {
        bool ok = true;
        for (auto [pi, _] : factorize(phi)) {
            if (pow_mod(ans, phi/pi, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return ans;
    }

    // something really bad happened if you get here
    // is p a prime?
    assert(0 == 1);
}

// P must be prime
//
// Usually, we pick primes of the form P = k * 2^n + 1.
// These are called Proth primes (http://www.prothsearch.com/Proth-k-1200-I.txt).
//
// Some of them for convenience:
//  k   n       k   n       k   n       k   n
//  3   30      51  25      235 24      305 23
//  13  28      63  25      243 24      335 23
//  15  27      81  25      45  23      347 23
//  17  27      125 25      71  23      357 23
//  29  27      45  24      77  23      371 23
//  7   26      73  24      105 23      395 23
//  27  26      127 24      107 23      407 23
//  37  26      151 24      119 23      431 23
//  43  26      157 24      155 23      437 23
//  5   25      171 24      177 23      447 23
//  33  25      193 24      249 23      507 23
template <u64 P>
struct NumberTheoreticTransform {
    u32 n;
    vector<u32> permutation;
    vector<modint<P>> omega;
    vector<modint<P>> omega_inv;

    u32 init(u32 size) {
        n = 1;
        u32 k = 0;
        while (n < size) {
            n *= 2;
            k += 1;
        }

        permutation.resize(n);
        for (u32 i = 0; i < n; ++i) {
            permutation[i] = reverse(i, k);
        }

        u64 g = primitive_root(P);
        assert((P-1) % n == 0);
        auto w = modint<P>(g).pow((P-1)/n);

        omega.resize(n);
        omega[0] = 1;
        for (u32 i = 1; i < n; ++i) {
            omega[i] = w * omega[i-1];
        }

        omega_inv.resize(n);
        omega_inv[0] = 1;
        for (u32 i = 1; i < n; ++i) {
            omega_inv[i] = omega[n-i];
        }

        return n;
    }

    vector<modint<P>> ntt(vector<modint<P>> x) {
        assert(x.size() == n);
        fft(x, permutation, omega);
        return x;
    }

    vector<modint<P>> intt(vector<modint<P>> x) {
        assert(x.size() == n);
        fft(x, permutation, omega_inv);
        auto n_inv = modint<P>(n).inv();
        for (auto& xi : x) xi = xi * n_inv;
        return x;
    }
};
