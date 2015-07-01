#![feature(path_ext)]
extern crate getopts;

use getopts::Options;
use std::io::prelude::*;
use std::fs::File;
use std::path::Path;
use std::env;

/// Takes two paths to files, copies from src to dest.
fn cp(src: &Path, dest: &Path) {
    let res = File::open(&src)
                   .and_then(|mut file| {
                       let mut src_bin = vec![];
                       file.read_to_end(&mut src_bin)
                           .map(|_| src_bin)
                   })
                   .and_then(|src_bin| {
                       File::create(&dest)
                            .and_then(|mut file| {
                                file.write_all(&src_bin)
                            })
                   });
    if res.is_err() {
        println!("cp: {}", res.err().unwrap().to_string());
    }
}

fn print_usage(opts: Options) {
    let menu = format!("Usage: cp SOURCE... DEST");
    print!("{}", opts.usage(&menu));
}

fn parse_files(sources: Vec<String>, dest: String) {
    if Path::new(&dest).is_dir() {
        for src in sources.iter() {
            let src_path = Path::new(&src);
            let file_name;
            match src_path.file_name() {
                Some(file) => file_name = file.to_str(),
                None => {
                    println!("cp: Omitting file {}", src);
                    continue;
                },
            }
            let dir_dest = dest.clone() + "/" + file_name.unwrap();
            let dest_path = Path::new(&dir_dest);
            cp(src_path, dest_path);
        }
        return;
    }

    if sources.len() > 1 {
        println!("cp: {} is not a directory.", dest);
        return;
    }
    let dest_path = Path::new(&dest);
    let src_path = Path::new(&sources[0]);
    cp(src_path, dest_path);
    return;
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let mut opts = Options::new();
    opts.optflag("h", "help", "print this help menu");
    opts.optflag("r", "recursive", "copy recursively");

    let matches = match opts.parse(&args[1..]) {
        Ok(m) => { m }
        Err(f) => { panic!(f.to_string()) }
    };

    if matches.opt_present("h") {
        print_usage(opts);
        return;
    }
    if matches.opt_present("r") {
        println!("RECURSIVE!!!");
    }

    let mut files = if !matches.free.is_empty() {
        matches.free.clone()
    } else {
        print_usage(opts);
        return;
    };

    if files.len() < 2 {
        println!("cp: Missing destination.");
        return;
    }

    let dest = files.pop().unwrap();
    parse_files(files, dest);
}
