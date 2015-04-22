/// Creates a list 1..n, not tail-recursive!!
fn nat_list(n: i32) -> Vec<i32> {
    /*
    let mut x = Vec::new();
    for i in 0..n {
        x.push(i);
    }
    return x;
    */
    if n == 0 {
        return Vec::new();
    }
    else if n > 0 {
        let mut x = nat_list(n - 1);
        x.push(n);
        return x;
    }
    else {
        panic!("At the Disco!");
    }
}

fn main() {
    let mut vec = nat_list(5);
    loop {
        let top = match vec.pop() {
            None => break,
            Some(n) => n,
        };
        println!("{}", top);
    }
}
