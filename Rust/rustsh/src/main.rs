extern crate nix;
use nix::sys::signal;

extern fn handle_sigint(_: i32) {
    println!("Interrupted!");
    panic!();
}

fn main() {
    let sig_action = signal::SigAction::new(handle_sigint,
                                            signal::SockFlag::empty(),
                                            signal::SigSet::empty());
    unsafe {
        signal::sigaction(signal::SIGINT, &sig_action);
    }

    loop {

    }
}
