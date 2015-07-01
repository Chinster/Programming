/// An implementation of the Bailey-Borwein-Plouffe formula.
/// Computes arbitrary hex digits of pi.

/// Performs modular exponentiation
const PREC: i64 = 14;

fn expm(mut b: i64, mut exp: i64, modu: i64) -> i64 {
    //assert!((modu - 1) * (modu - 1) < b);
    let mut result = 1;
    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * b) % modu;
        }
        exp >>= 1;
        b = (b * b) % modu;
    }
    return result
}

fn series(j: i64, n: i64) -> i64 {
    let m: i64 = 16_i64.pow(PREC as u32);

    let mut sum1 = 0;
    let mut iter = 0;
    while iter <= n {
        let r = 8 * iter + j;
        sum1 = sum1 + expm(16, n - iter, r) << (4 * PREC);
        iter += 1;
    }

    let mut sum2 = 0;
    loop {
        let exp = 16_i64.pow((n - iter) as u32) * m;
        let new_sum = sum2 + exp;

        if new_sum == sum2 {
            break;
        }
        else {
            sum2 = new_sum;
        }
        iter += 1;
    }

    return sum1 + sum2
}

fn bbp(n: i64) -> i64 {
    let m = 16_i64.pow(PREC as u32);
    let id = n - 1;
    let s1 = series(1, id);
    let s2 = series(4, id);
    let s3 = series(5, id);
    let s4 = series(6, id);
    ((4 * s1) - (2 * s2) - s3 - s4) & (m - 1)
}

fn main() {
    let num = bbp(0);
    println!("{}", num);
}
