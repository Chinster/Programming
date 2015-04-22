//use std::io::prelude::*;
use std::fs::File;
use std::env;

fn cp(src: String, dest: String) {
    let mut src = File::open(src);
    let mut dest = File::create(dest);
}

fn main() {
    let mut args: Vec<String> = env::args().collect();
    // Remove 1st argument, this program name.
    // Hopefully std::vec::Vec::remove is a tad efficient when given param 0
    args.remove(0);
    let argc = args.len();

    if argc < 2 {
        println!("Usage: cp SOURCE DEST
          or: cp SOURCE... DIR");
        return;
    }
    if argc == 2 {
        cp(args[0].clone(), args[1].clone());
    }
    else {
        // TODO
        cp(args[0].clone(), args[1].clone());
    }
    /*
    let mut f = File::create("foo.txt").ok().unwrap();
    let bytes: [u8; 1] = [0x64];
    f.write_all(&bytes);*/
}
