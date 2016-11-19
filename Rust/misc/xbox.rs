extern crate futures;

use std::process::{Child, Command, Stdio};
use std::io::Read;
use std::thread;
use futures::Future;
use futures::stream::{Stream, BoxStream};

fn printer(req: String) {
    println!("{}", req);
}

/// Converts a process' stdout into a stream
fn proc_stream(p: &Child) -> BoxStream<String, std::io::Error> {
    let (mut tx, rx) = futures::stream::channel();
    thread::spawn(move || {
        let output = p.stdout.expect("Could not grab stdout from process");
        match  tx.send(output.read()).wait() {
            Ok(val) => tx = val,
            Err(_) => {},
        }
    });

    return rx.boxed();
}

pub fn main() {
    let child = Command::new("xboxdrv")
                         .arg("--detach-kernel-driver")
                         .arg("--no-uinput")
                         .stdout(Stdio::piped())
                         .spawn()
                         .expect("xboxdrv failed to start");

    let iostream = proc_stream(&child);

    //type IoStream<T> = Box<Stream<Item=T, Error=std::io::Error>>;
    //let events: BoxStream = init_xboxdrv();

    //events.and_then(|req| printer(req));
}
