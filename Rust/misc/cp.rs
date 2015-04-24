#![feature(path_ext)]
use std::io::prelude::*;
use std::fs::File;
use std::path::Path;
use std::env;

/// Takes two paths, copies from the File at src to a File as dest
fn cp(src: &Path, dest: &Path) {
    let mut src_f: File;
    match File::open(&src) {
        Ok(handle) => src_f = handle,
        Err(cause) => {
            println!("cp: {}", cause);
            return;
        }
    }

    let mut dest_f: File;
    match File::create(&dest) {
        Ok(handle) => dest_f = handle,
        Err(cause) => {
            println!("cp: {}", cause);
            return;
        }
    }

    let mut src_bin = vec![];
    if let Err(cause) = src_f.read_to_end(&mut src_bin) {
        println!("cp: {}", cause);
        return;
    }
    if let Err(cause) = dest_f.write_all(&src_bin) {
        println!("cp: {}", cause);
        return;
    }
}

fn parse_files(sources: Vec<String>, dest: String) {
    let dest_is_dir = Path::new(&dest).is_dir();
    if !dest_is_dir {
        if sources.len() > 1 {
            println!("cp: {} is not a directory.", dest);
            return;
        }
        let dest_path = Path::new(&dest);
        let src_path = Path::new(&sources[0]);
        cp(src_path, dest_path);
        return;
    }

    // Copy into directory.
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

fn main() {
    let mut args: Vec<String> = env::args().collect();
    let argc = args.len();
    if argc < 2 {
        println!("Usage: cp SOURCE DEST
          or: cp SOURCE... DIR");
        return;
    }
    if argc < 3 {
        println!("cp: Missing destination.");
        return;
    }

    let dest = args.pop().unwrap();
    args.swap_remove(0); // Order of args do not matter.
    parse_files(args, dest);
}
