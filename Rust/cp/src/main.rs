#![feature(path_ext)]
extern crate getopts;

use getopts::Options;
use getopts::Matches;
use std::io::prelude::*;
use std::fs::File;
use std::path::Path;
use std::env;

/// Takes two paths to files, copies bytes from src to dest
fn cp<P: AsRef<Path>>(src: P,
                      dest: P,
                      matches: &Matches) -> Option<std::io::Error> {
    let src = src.as_ref();
    let dest = dest.as_ref();

    if src.is_dir() {
        if matches.opt_present("r") {
            // Acceptable error creating dir. Errors will pop up later.
            std::fs::create_dir(dest);
            let read_dir = std::fs::read_dir(&src).unwrap();
            for entry in read_dir {
                let entry_path = entry.unwrap().path();
                let file_name = entry_path.file_name().unwrap().to_str().unwrap();

                let mut dest_buf = dest.to_path_buf();
                dest_buf.push(file_name);
                cp(&entry_path, &dest_buf, matches);
            }
        }
        else {
            println!("cp: Omitting directory {}", src.display());
        }
        return None;
    }

    File::open(&src)
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
         })
         .err()
}

fn print_usage(opts: Options) {
    let menu = format!("Usage: cp SOURCE... DEST");
    print!("{}", opts.usage(&menu));
}

/// Determines if destination is dir.
fn cp_branch(sources: Vec<&Path>, dest: &Path, matches: &Matches) {
    // File to file case.
    if !dest.is_dir() {
        if sources.len() > 1 {
            println!("cp: {} is not a directory.", dest.display());
            return;
        }

        let src_path = Path::new(&sources[0]);
        if let Some(x) = cp(src_path, dest, &matches) {
            // Print error
            println!("cp: {} for file {}", x, src_path.display());
        }

        return;
    }

    // Files to directory case
    for src in sources.iter() {
        let src_path = Path::new(&src);
        let file_name;
        match src_path.file_name() {
            Some(file) => file_name = file.to_str().unwrap(),
            None => {
                println!("cp: Omitting file {}", src.display());
                continue;
            },
        }
        let mut dest_buf = dest.to_path_buf();
        dest_buf.push(file_name);
        let dest_path = dest_buf.as_path();
        cp(src_path, dest_path, &matches);
    }
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
    // Generate Vec<&Path>
    let mut src_paths = Vec::new();
    for i in 0..files.len() {
        src_paths.push(Path::new(&files[i]));
    }
    cp_branch(src_paths, Path::new(&dest), &matches);
}
