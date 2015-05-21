/// Sequential generator for hexadecimal digits of pi.
struct PiDigits {
    index: i64,
    fract: f64,
}

impl PiDigits {
    fn new() -> PiDigits {
        PiDigits { index: 0, fract: 0.0}
    }
    fn all(&self) -> f64 {
        16.0 * self.fract
    }
}

impl Iterator for PiDigits {
    type Item = u64;
    fn next(&mut self) -> Option<Self::Item> {
        self.index += 1;
        let n = self.index;
        let numer = ((120 * n - 89) * n + 16) as f64;
        let denom = ((((512 * n - 1024) * n + 712) * n - 206) * n + 21) as f64;

        let newfract = 16.0 * self.fract + (numer / denom);
        self.fract = newfract;
        return Some((16_f64 * newfract) as u64)
    }
}

fn main() {
    let mut x = PiDigits::new();
    for i in 0..20 {
        match x.next() {
            Some(n) => println!("{:x}", n),
            None => panic!("How?"),
        }
    }
}
