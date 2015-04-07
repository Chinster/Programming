/// Returns the last element of a Vector
fn last(l: Vec<i32>) -> i32 {
    if l.len() <= 0 {
        panic!("Negative Number!");
    }
    return l[l.len() - 1];
}

fn main() {
    let arg = vec![1, 3, 3, 5];
    println!("{}", last(arg));
}
