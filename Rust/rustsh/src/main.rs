extern crate nix;
use nix::sys;
use std::io::{Write, ErrorKind};

fn getline() -> Option<String> {
    let mut buf = String::new();
    match std::io::stdin().read_line(&mut buf) {
        Ok(_) if buf.is_empty() => None,
        Ok(_) => Some(buf),
        Err(e) => {
            writeln!(&mut std::io::stderr(), "{}", e).unwrap();
            None
        },
    }
}

fn eval(cmd: String) {
    let is_background = false;

    let args = cmd.split_whitespace.collect();
    let process = args[0];
}

fn main() {
    sys::syscall()
    /*
    loop {
        let cmd;
        match getline() {
            Some(line) => cmd = line,
            None => return,
        }
        eval(cmd);
    }
    */
}
