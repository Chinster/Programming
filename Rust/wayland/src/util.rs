#![allow(non_camel_case_types)]
#![allow(dead_code)]
#[repr(C)]
pub struct wl_message;
#[repr(C)]
pub struct wl_interface;
#[repr(C)]
pub struct wl_list;
#[repr(C)]
pub struct wl_array;

/// A union representing all of the basic data types that can be passed
/// along the wayland wire format.
///
/// This is used by dispatchers and runtime-friendly versions of the event
/// and reques marshaling functions.
#[repr(C)]
pub struct wl_argument;

#[repr(C)]
pub type wl_log_func_t = fn () -> i8;
