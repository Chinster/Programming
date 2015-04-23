use std::io::prelude::*;
use std::fs::File;
use std::path::Path;
use std::env;

/// Takes two paths, copies from the File at src to a File as dest
fn cp(src: &Path, dest: &Path) {
    let src: Result<_, _> = File::open(&src);
    if let Err(cause) = src {
        println!("cp: {}", cause);
        return;
    }

    let dest: Result<_, _> = File::create(&dest);
    if let Err(cause) = dest {
        println!("cp: {}", cause);
        return;
    }

    let mut src_bin = vec![];
    if let Err(cause) = src.unwrap().read_to_end(&mut src_bin) {
        println!("cp: {}", cause);
        return;
    }
    if let Err(cause) = dest.unwrap().write_all(&src_bin) {
        println!("cp: {}", cause);
        return;
    }
}

fn parse_files(sources: Vec<String>, dest: String) {
    if sources.len() == 1 {
        let dest_path = Path::new(&dest);
        let src_path = Path::new(&sources[0]);
        cp(src_path, dest_path);
    }
    else {
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
            let dir_dest = file_name.unwrap().to_string() + &dest;
            let dest_path = Path::new(&dir_dest);
            cp(src_path, dest_path);
        }
    }
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
