extern crate wayland;
use wayland::client;

#[test]
fn it_works() {
    client::wl_display_connect("asdf");
}
