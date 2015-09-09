/// An implementation of the Bailey-Borwein-Plouffe formula.
/// Computes arbitrary hex digits of pi.

/// Performs modular exponentiation
fn expm(mut b: i32, mut exp: i32, m: i32) -> i32 {
    //assert!((m - 1) * (m - 1) < b);
    let mut result = 1;
    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * b) % m;
        }
        exp >>= 1;
        b = (b * b) % m;
    }
    return result
}

fn series(m: i32, id: i32) -> f32 {
    let mut sum: f32 = 0.0;
    for i in 0..id {
        let ak = 8 * i + m;
        let p = id - i;
        let t = expm(16, p, ak);
        sum = sum + (t as f32) / (ak as f32);
        sum = sum - sum.floor();
    }

    for i in id..(id + 100) {
        let ak = 8 * i + m;
        let t = 16_f32.powf((id - i) as f32) / (ak as f32);
        if t < 1e-10 {
            break;
        }
        sum = sum + t;
        sum = sum - sum.floor();
    }

    return sum
}

fn get_byte(id: i32) -> u8 {
    let s1 = series(1, id);
    let s2 = series(4, id);
    let s3 = series(5, id);
    let s4 = series(6, id);
    let mut pid = (4.0 * s1) - (2.0 * s2) - s3 - s4;
    pid = pid - pid.floor() + 1.0;

    let mut y = pid.abs();
    y = 16.0 * (y - y.floor());
    let first = y as i32;
    y = 16.0 * (y - y.floor());
    let second = y as i32;

    return ((first << 4) | second) as u8;
}

fn main() {
    let byte = get_byte(0);
    println!("{}", byte);
}
