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

fn tokenize(cmd: String) -> Option<Vec<String>> {
    let tokens = cmd.split_whitespace().collect();
    Some(tokens)
}

fn main() {
    loop {
        getline().and_then(tokenize);
        // if None then return
    }
}
