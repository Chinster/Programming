use ::phi::{Phi, View, ViewAction};
use ::phi::data::Rectangle;
use ::phi::gfx::{CopySprite, Sprite};
use ::std::path::Path;
use ::sdl2::pixels::Color;
use ::sdl2::render::{Renderer, Texture, TextureQuery};
use ::sdl2_image::LoadTexture;
use ::views::shared::BgSet;

// pixels / second
const PLAYER_SPEED: f64 = 180.0;

const SHIP_W: f64 = 43.0;
const SHIP_H: f64 = 39.0;

const DEBUG: bool = false;

#[derive(Clone, Copy)]
enum ShipFrame {
    UpNorm   = 0,
    UpFast   = 1,
    UpSlow   = 2,
    MidNorm  = 3,
    MidFast  = 4,
    MidSlow  = 5,
    DownNorm = 6,
    DownFast = 7,
    DownSlow = 8,
}

struct Ship {
    rect: Rectangle,
    sprites: Vec<Sprite>,
    current: ShipFrame,
}

pub struct ShipView {
    player: Ship,
    bg: BgSet,
}

impl ShipView {
    pub fn new(phi: &mut Phi, bg: BgSet) -> ShipView {
        let bg = BgSet::new(&mut phi.renderer);
        ShipView::with_backgrounds(phi, bg)
    }
    pub fn with_backgrounds(phi: &mut Phi, bg: BgSet) -> ShipView {
        let spritesheet = Sprite::load(&mut phi.renderer,
                                       "assets/spaceship.png").unwrap();

        // Hard coded capacity - we know the number of sprites.
        let mut sprites = Vec::with_capacity(9);

        for y in 0..3 {
            for x in 0..3 {
                sprites.push(spritesheet.region(Rectangle {
                    w: SHIP_W,
                    h: SHIP_H,
                    x: SHIP_W * x as f64,
                    y: SHIP_H * y as f64,
                }).unwrap());
            }
        }

        ShipView {
            player: Ship {
                rect: Rectangle {
                    x: 64.0,
                    y: 64.0,
                    w: SHIP_W,
                    h: SHIP_H,
                },
                sprites: sprites,
                current: ShipFrame::MidNorm,
            },
            bg: bg,
        }
    }
}

impl View for ShipView {
    fn render(&mut self, phi: &mut Phi, elapsed: f64) -> ViewAction {
        if phi.events.now.quit || phi.events.now.key_escape == Some(true) {
            return ViewAction::Quit;
        }

        let diagonal =
            (phi.events.key_up ^ phi.events.key_down) &&
            (phi.events.key_left ^ phi.events.key_right);

        let moved = match diagonal {
            true => 1.0 / 2.0f64.sqrt(),
            false => 1.0
        } * PLAYER_SPEED * elapsed;

        let dx = match (phi.events.key_left, phi.events.key_right) {
            (true, true) | (false, false) => 0.0,
            (true, false) => -moved,
            (false, true) => moved,
        };

        let dy = match (phi.events.key_up, phi.events.key_down) {
            (true, true) | (false, false) => 0.0,
            (true, false) => -moved,
            (false, true) => moved,
        };

        self.player.rect.x += dx;
        self.player.rect.y += dy;

        // Limit rectangle to height and 70% of width
        let moveable_region = Rectangle {
            x: 0.0,
            y: 0.0,
            w: phi.output_size().0 as f64 * 0.70,
            h: phi.output_size().1 as f64,
        };

        // If player cannot fit the screen, abort immediately
        self.player.rect = self.player.rect.move_inside(moveable_region).unwrap();
        self.player.current =
            if dx == 0.0 && dy < 0.0       { ShipFrame::UpNorm }
            else if dx > 0.0 && dy < 0.0   { ShipFrame::UpFast }
            else if dx < 0.0 && dy < 0.0   { ShipFrame::UpSlow }
            else if dx == 0.0 && dy == 0.0 { ShipFrame::MidNorm }
            else if dx > 0.0 && dy == 0.0  { ShipFrame::MidFast }
            else if dx < 0.0 && dy == 0.0  { ShipFrame::MidSlow }
            else if dx == 0.0 && dy > 0.0  { ShipFrame::DownNorm }
            else if dx > 0.0 && dy > 0.0   { ShipFrame::DownFast }
            else if dx < 0.0 && dy > 0.0   { ShipFrame::DownSlow }
            else { unreachable!() };

        // Clear screen
        phi.renderer.set_draw_color(Color::RGB(0, 0, 0));
        phi.renderer.clear();

        // Render Background
        self.bg.back.render(&mut phi.renderer, elapsed);
        self.bg.middle.render(&mut phi.renderer, elapsed);

        // Render bounding box for debugging
        if DEBUG {
            phi.renderer.set_draw_color(Color::RGB(200, 200, 50));
            phi.renderer.fill_rect(self.player.rect.to_sdl().unwrap());
        }

        // Render scene
        phi.renderer.copy_sprite(
            &self.player.sprites[self.player.current as usize],
            self.player.rect);

        // Render foreground
        self.bg.front.render(&mut phi.renderer, elapsed);

        ViewAction::None
    }
}
