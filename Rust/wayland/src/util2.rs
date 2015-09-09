#![allow(dead_code)]
extern crate libc;
use self::libc::{size_t, int32_t, uint32_t, c_char, c_int, c_void, c_double};


#[repr(C)]
struct wl_message {
    name: *const c_char,
    signature: *const c_char,
    types: *const *mut wl_interface,
}

#[repr(C)]
pub struct wl_interface {
    name: *const c_char,
    version: c_int,
    method_count: c_int,
    methods: *const wl_message,
    event_count: c_int,
    events: *const wl_message,
}

#[repr(C)]
struct wl_list {
    prev: *mut wl_list,
    next: *mut wl_list,
}

#[repr(C)]
struct wl_array {
    size: size_t,
    alloc: size_t,
    data: *mut c_void,
}

// Largest data point is 32 bits
#[repr(C)]
struct wl_argument_union {
    u: uint32_t
}

type wl_fixed_t = int32_t;
type wl_dispatcher_func_t = fn(*const c_void, *const c_void, uint32_t,
                               *const wl_message,
                               *mut wl_argument_union) -> c_int;
//type wl_log_func_t = fn(*const c_void, ...);

#[link(name="wayland-util")]
extern {

    fn wl_list_init(list: *mut wl_list);
    fn wl_list_insert(list: *mut wl_list, elm: *mut wl_list);
    fn wl_list_remove(elm: *mut wl_list);
    fn wl_list_length(list: *const wl_list) -> c_int;
    fn wl_list_empty(list: *const wl_list) -> c_int;
    fn wl_list_insert_list(list: *mut wl_list, other: *mut wl_list);
    fn wl_array_init(array: *mut wl_array);
    fn wl_array_release(array: *mut wl_array);
    fn wl_array_add(array: *mut wl_array, size: size_t) -> *mut c_void;
    fn wl_array_copy(array: *mut wl_array, source: *mut wl_array) -> c_int;

    // static inline functions below
    fn wl_fixed_to_double(f: wl_fixed_t) -> c_double;
    fn wl_fixed_from_double(d: c_double) -> wl_fixed_t;
    fn wl_fixed_to_int(f: wl_fixed_t) -> c_int;
    fn wl_fixed_from_int(i: c_int) -> wl_fixed_t;
}
