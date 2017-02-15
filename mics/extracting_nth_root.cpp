bigint_t estimate_beta(const vector<bigint_t>& pas, const bigint_t& delta, int __beta) {
    int n;
    bigint_t beta_n, beta_1, retval, terms, delta_n;
    if (__beta == 0)
        return string("0");
    n = static_cast<int>(pas.size());
    beta_1 = to_bignum_t(__beta);
    beta_n = pow_big(beta_1, n);
    delta_n = delta;
    retval = beta_n;

    // start estimating from the second terms
    for (vector<bigint_t>::const_iterator it = pas.begin() + 1; it != pas.end(); it++) {
        beta_n = div_big(beta_n, beta_1, terms); // terms is now temporary var
        terms = mul_big(*it, delta_n);
        terms = mul_big(terms, beta_n);
        retval = add_big(retval, terms);
        delta_n = mul_big(delta_n, delta);
    }

    return retval;
}

bigint_t guess_beta(const vector<bigint_t>& pas, int& beta,
                    const bigint_t& delta, const bigint_t& present) {
    bigint_t retval = "0", exp_val;
    for (int i = 0; i <= 9; ++i) {
        exp_val = estimate_beta(pas, delta, i);
        if (compare(exp_val, present) <= 0) {
            retval = exp_val;
            beta = i;
        } else {
            break;
        }
    }
    return retval;
}

bigint_t nth_root_big_slow(bigint_t a, int n) {
    vector<bigint_t> pascal;

    if (compare(to_bignum_t(n), a) >= 0)
        return string("1");

    if (compare(a, "1") == 0 || compare(a, "0") == 0)
        return a;

    // pascal trigangle for n-th root
    pascal.push_back("1");
    pascal.push_back("2");
    pascal.push_back("1");
    for (int i = 2; i < n; ++i) {
        bigint_t forw = "1", now;
        for (vector<bigint_t>::iterator it = pascal.begin() + 1; it != pascal.end(); ++it) {
            now = *it;
            *it = add_big(*it, forw);
            forw = now;
        }
        pascal.push_back("1");
    }
    pascal.pop_back();

    // 10^i
    bigint_t zeroes = "";
    for (vector<bigint_t>::iterator it = pascal.begin(); it != pascal.end(); ++it) {
        it->append(zeroes);
        zeroes.push_back('0');
    }

    // add non-significant leading zeroes, so that a.size() is multiple of n
    while (a.size() % n != 0)
        a.insert(a.begin(), '0');

    // extracting n-th root of a
    bigint_t present = "";
    bigint_t exp_val = "";
    bigint_t delta = "0";
    int beta;
    while (a.size() > 0) {
        present += a.substr(0, n);
        exp_val = guess_beta(pascal, beta, delta, present);
        delta += (to_bignum_t(beta));
        present = sub_big(present, exp_val);
        a.erase(0, n);
    }

    trim_zeroes(delta);
    return delta;
}
