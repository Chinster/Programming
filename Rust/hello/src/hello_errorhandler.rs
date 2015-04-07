/// This enum is provided by Rust
/// enum Result<T, E> {
///     Ok(T),
///     Err(E)
/// }
use std::fs::File;
use std::io;
use std::io::prelude::*;

fn main() {
    let mut buffer = String::new();
    // here unwrap() panics if readline returns None
    //io::stdin().read_line(&mut buffer).unwrap();

    let input = io::stdin().read_line(&mut buffer)
                           .ok()  // Converts Result to Option
                           .expect("Failed to read line");

    panic!("boom");
}

struct Info {
    name: String,
    age: i32,
    rating: i32,
}

// try! can only be used in a function that returns a Result<T, E>
fn write_info(info: &Info) -> io::Result<()> {
    let mut filel = try!(File::open("best_friend.txt"));

    try!(writeln!(&mut file, "name: {}", info.name));
    try!(writeln!(&mut file, "age: {}", info.age));
    try!(writeln!(&mut file, "rating: {}", info.rating));

    return Ok(());
}

