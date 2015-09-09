#![feature(path_ext)]
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
