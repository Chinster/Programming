extern crate pcap;
extern crate ncurses;
use pcap::Device;
use std::thread;
use std::collections::LinkedList;

const REFRESH_RATE_MS: u32 = 500;

/// Modifies x and y to max x and max y
fn init_ncurses(x: &mut i32, y: &mut i32) {
    use ncurses::*;

    initscr();
    curs_set(CURSOR_VISIBILITY::CURSOR_INVISIBLE);
    noecho();

    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_RED);
    getmaxyx(stdscr, y, x);
}

// TODO: Handle SIGWINCH http://invisible-island.net/ncurses/ncurses-intro.html
// TODO: Color based on packet type?

fn main() {
    let mut max_x = 0;
    let mut max_y = 0;
    init_ncurses(&mut max_x, &mut max_y);
    let mut cap = Device::lookup().unwrap().open().unwrap();

    thread::spawn(|| {
        loop {
            ncurses::refresh();
            thread::sleep_ms(REFRESH_RATE_MS);
        }
    });

    let mut cur_y = 0;
    while let Some(packet) = cap.next() {
        let mut len = packet.len();
        if len > max_x as usize {
            len = max_x as usize;
        }

        // Clear row
        ncurses::mv(cur_y, 0);
        ncurses::color_set(1);
        for _ in 0..max_x {
            ncurses::printw(" ");
        }

        ncurses::mv(cur_y, 0);
        ncurses::color_set(2);
        for _ in 0..len {
            ncurses::printw("x");
        }

        cur_y += 1;
        if cur_y >= max_y {
            cur_y = 0;
        }
    }

    ncurses::endwin();
}
