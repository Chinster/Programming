/// Safe interface to wayland-client functions.
extern crate libc;
use std::ffi::CString;

mod header;

#[repr(C)]
pub struct wl_proxy {
    object
    flags: u32,
}

pub struct wl_display {
}

pub fn wl_display_connect(name: &str) {
    let c_str = CString::new(name).unwrap();
    unsafe {
        let header::wl_display_connect(c_str.as_ptr());
    }
}
