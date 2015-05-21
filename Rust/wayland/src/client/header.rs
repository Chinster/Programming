#![allow(non_camel_case_types)]
#![allow(dead_code)]
/// Import of wayland-client.h in Rust
extern crate libc;
use self::libc::{c_void, c_int, c_char};
use util;

#[repr(C)]
pub struct wl_proxy;
#[repr(C)]
pub struct wl_display;
#[repr(C)]
pub struct wl_event_queue;

#[link(name="wayland-client")]
extern {
    pub fn wl_event_queue_destroy(queue: *mut wl_event_queue);
    pub fn wl_proxy_marshal(p: *mut wl_proxy, opcode: u32, ...);
    pub fn wl_proxy_marshal_array(p: *mut wl_proxy, opcode: u32, ...);
    pub fn wl_proxy_create(factory: *mut wl_proxy,
                       interface: *const util::wl_interface) -> *mut wl_proxy;
    pub fn wl_proxy_marshal_constructor(proxy: *mut wl_proxy,
                                        opcode: u32,
                                        interface: *const util::wl_interface,
                                        ...) -> *mut wl_proxy;
    pub fn wl_proxy_destroy(proxy: *mut wl_proxy);
    pub fn wl_proxy_add_listener(proxy: *mut wl_proxy,
                                 implementation: *mut fn (),
                                 data: *mut c_void) -> c_int;
    pub fn wl_proxy_get_listener(proxy: *mut wl_proxy) -> *const c_void;

    /*
    fn wl_proxy_add_dispatcher(proxy: *mut wl_proxy,
                               dispatcher_fun: wl_dispatcher_func_t,
                               dispatcher_data: *const c_void,
                               data: *mut c_void) -> c_int;
*/
    pub fn wl_proxy_set_user_data(proxy: *mut wl_proxy,
                                  user_data: *mut c_void);
    pub fn wl_proxy_get_user_data(proxy: *mut wl_proxy) -> *mut c_void;
    pub fn wl_proxy_get_id(proxy: *mut wl_proxy) -> u32;
    pub fn wl_proxy_get_class(proxy: *mut wl_proxy) -> *const c_char;
    pub fn wl_proxy_set_queue(proxy: *mut wl_proxy,
                              queue: *mut wl_event_queue);

    pub fn wl_display_connect(name: *const c_char) -> *mut wl_display;
    pub fn wl_display_connect_to_fd(fd: c_int) -> *mut wl_display;
    pub fn wl_display_disconnect(display: *mut wl_display);
    pub fn wl_display_get_fd(display: *mut wl_display) -> c_int;
    pub fn wl_display_dispatch(display: *mut wl_display) -> c_int;
    pub fn wl_display_dispatch_queue(display: *mut wl_display,
                                     queue: *mut wl_event_queue) -> c_int;
    pub fn wl_display_dispatch_queue_pending(display: *mut wl_display,
                          queue: *mut wl_event_queue) -> c_int;
    pub fn wl_display_dispatch_pending(display: *mut wl_display) -> c_int;
    pub fn wl_display_get_error(display: *mut wl_display) -> c_int;
    pub fn wl_display_get_protocol_error(display: *mut wl_display,
                                         interface: *const *mut util::wl_interface,
                                         id: *mut u32) -> u32;
    pub fn wl_display_flush(display: *mut wl_display) -> c_int;
    pub fn wl_display_roundtrip_queue(display: *mut wl_display,
                                   queue: *mut wl_event_queue) -> c_int;
    pub fn wl_display_roundtrip(display: *mut wl_display) -> c_int;
    pub fn wl_display_create_queue(display: *mut wl_display) -> *mut wl_event_queue;
    pub fn wl_display_prepare_read_queue(display: *mut wl_display,
                      queue: *mut wl_event_queue) -> c_int;
    pub fn wl_display_prepare_read(display: *mut wl_display) -> c_int;
    pub fn wl_display_cancel_read(display: *mut wl_display);
    pub fn wl_display_read_events(display: *mut wl_display) -> c_int;

    //pub fn wl_log_set_handler_client(wl_log_func_t handler);
}
