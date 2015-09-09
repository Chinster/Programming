/// Signal handling by interfacing with C sigaction
extern crate libc;
use self::libc::{c_int};

struct siginfo_t;
type sigset_t = libc::uint64_t;
#[repr(C)]
struct SigAction {
    sa_handler: fn(isize),
    sa_sigaction: fn(c_int, *mut siginfo_t, *mut libc::c_void),
    sa_mask: sigset_t,
    sa_flags: c_int,
    sa_restorer: fn(),
}

impl Default for SigAction {
    fn default() -> SigAction {
        SigAction {
            sa_handler: stub_handler,
            sa_sigaction: stub_sigaction,
            sa_mask: 0,
            sa_flags: 0,
            sa_restorer: stub_restorer,
        }
    }
}

extern {
    fn sigemptyset(set: *const sigset_t) -> c_int;
    fn sigaction(signum: c_int, act: *const SigAction, oldact: *const SigAction) -> c_int;

}

fn my_handler(sig: isize) {
    println!("handled!");
}
fn stub_restorer() {
}
fn stub_handler(_: isize) {
}
fn stub_sigaction(_: c_int, _: *mut siginfo_t, _: *mut libc::c_void) {
}

fn main() {
    let new_action = SigAction {
        sa_handler: my_handler,
        sa_flags: 0x0030, // SA_NODEFER
        ..Default::default()
    };
    let mask_ptr = &new_action.sa_mask as *const sigset_t;
    let action_ptr = &new_action as *const SigAction;
    unsafe {
        if sigemptyset(mask_ptr) == -1 {
            println!("sigemptyset fail");
            return;
        }
        // SIGINT
        if sigaction(2, action_ptr, std::ptr::null()) == -1 {
            println!("sigaction fail");
            return;
        }
    }
    loop {

    }
}
