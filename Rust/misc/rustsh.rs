/// A high level implementation of a shell
use std::process::Command;
use std::io;
use std::io::prelude::*;

/// Prints the specified string to stdout and flushes the buffer.
fn print(out_str: &str) {
    print!("{}", out_str);
    io::stdout().flush().ok().expect("Could not flush stdout");
}

fn parse_input() -> Command {
    let mut comm_str = String::new();
    io::stdin().read_line(&mut comm_str)
               .ok()
               .expect("Could not read stdin");
    // Drop trailing new line
    comm_str.pop();
    let tokens: Vec<&str> = comm_str.split(' ').collect();

    let comm_name = tokens[0];

    let mut command = Command::new(comm_name);

    for arg in 1..tokens.len() {
        command.arg(tokens[arg]);
    }
    command
}

fn main() {
    let user = std::env::var("USER").unwrap_or("".to_string());
    let home = std::env::home_dir();
    let wd = std::env::current_dir().unwrap_or_else(
        |_| {
            let path = home.unwrap(); // Panic here
            if std::env::set_current_dir(&path).is_err() {
                println!("Can't change directories.");
            }
            path
        });
    let top_level = wd.to_str().unwrap().split("/").last().unwrap();

    loop {
        print(&format!("{} {}$ ", user, top_level));


        let mut command = parse_input();
        let comm_proc = command.output()
                               .unwrap_or_else(
                                   |e| {
                                       panic!("Process execution failed: {}", e)
                                   });
        print!("{}", String::from_utf8_lossy(&comm_proc.stdout));
        print!("{}", String::from_utf8_lossy(&comm_proc.stderr));
    }
}
