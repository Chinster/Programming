use ::phi::{Phi, View, ViewAction};
use ::sdl2::pixels::Color;
use ::sdl2::rect::Rect as SdlRect;

// pixels / second
const PLAYER_SPEED: f64 = 180.0;

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Rectangle {
    pub x: f64,
    pub y: f64,
    pub w: f64,
    pub h: f64,
}

impl Rectangle {
    /// Generates an SDL-compatible Rect equivalent to `self`.
    /// Panics if it could not be created, for exa,ple if a
    /// coordinate of a corner overflows an `i32`.
    pub fn to_sdl(self) -> Option<SdlRect> {
        assert!(self.w >= 0.0 && self.h >= 0.0);

        SdlRect::new(self.x as i32,
                     self.y as i32,
                     self.w as u32,
                     self.h as u32).unwrap()
    }

    pub fn move_inside(self, parent: Rectangle) -> Option<Rectangle> {
        if self.w > parent.w || self.h > parent.h {
            return None
        }

        Some(Rectangle {
            w: self.w,
            h: self.h,
            x: if self.x < parent.x {
                parent.x
            }
            else if self.x + self.w >= parent.x + parent.w {
                parent.x + parent.w - self.w
            }
            else {
                self.x
            },
            y: if self.y < parent.y {
                parent.y
            }
            else if self.y + self.h >= parent.y + parent.h {
                parent.y + parent.h - self.h
            }
            else {
                self.y
            },
        })
    }
}


struct Ship {
    rect: Rectangle,
}

pub struct ShipView {
    player: Ship,
}

impl ShipView {
    pub fn new(phi: &mut Phi) -> ShipView {
        ShipView {
            player: Ship {
                rect: Rectangle {
                    x: 64.0,
                    y: 64.0,
                    w: 32.0,
                    h: 32.0,
                }
            }
        }
    }
}

impl View for ShipView {
    fn resume(&mut self, _context: &mut Phi) {}
    fn pause(&mut self, _context: &mut Phi) {}
    fn render(&mut self, phi: &mut Phi, elapsed: f64) -> ViewAction {
        let events = &phi.events;

        if events.now.quit || events.now.key_escape == Some(true) {
            return ViewAction::Quit;
        }

        let diagonal = (events.key_up ^ events.key_down)
            && (events.key_left ^ events.key_right);
        let moved = if diagonal {
            1.0 / 2.0f64.sqrt()
        }
        else {
            1.0
        } * PLAYER_SPEED * elapsed;

        let dx = match (events.key_left, events.key_right) {
            (true, true) | (false, false) => 0.0,
            (true, false) => -moved,
            (false, true) => moved,
        };

        let dy = match (events.key_up, events.key_down) {
            (true, true) | (false, false) => 0.0,
            (true, false) => -moved,
            (false, true) => moved,
        };

        self.player.rect.x += dx;
        self.player.rect.y += dy;

        // Limit rectangle to view
        let moveable_region = Rectangle {
            x: 0.0,
            y: 0.0,
            w: phi.output_size().0 as f64 * 0.70,
            h: phi.output_size().1 as f64,
        };
        self.player.rect = self.player.rect.move_inside(moveable_region).unwrap();

        // Clear screen
        phi.renderer.set_draw_color(Color::RGB(0, 0, 0));
        phi.renderer.clear();

        // Render scene
        phi.renderer.set_draw_color(Color::RGB(200, 200, 50));
        phi.renderer.fill_rect(self.player.rect.to_sdl().unwrap());

        ViewAction::None
    }
}
