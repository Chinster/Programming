use ::phi::{Phi, View, ViewAction};
use ::phi::data::Rectangle;
use ::phi::gfx::{CopySprite, Sprite};
use ::sdl2::pixels::Color;
use ::views::shared::BgSet;

const ACTION_FONT: &'static str = "assets/belligerent.ttf";

pub struct MainMenuView {
    actions: Vec<Action>,
    selected: i8,
    bg: BgSet
}

impl MainMenuView {
    pub fn new(phi: &mut Phi) -> MainMenuView {
        let bg = BgSet::new(&mut phi.renderer);
        MainMenuView::with_backgrounds(phi, bg)
    }
    pub fn with_backgrounds(phi: &mut Phi, bg: BgSet) -> MainMenuView {
        MainMenuView {
            actions: vec![
                Action::new(phi, "New Game", Box::new(|phi, bg| {
                    ViewAction::ChangeView(Box::new(
                            ::views::game::ShipView::new(phi, bg)))
                })),
                Action::new(phi, "Quit", Box::new(|_, _| {
                    ViewAction::Quit
                })),
            ],
            selected: 0,
            bg: bg
        }
    }
}


impl View for MainMenuView {
    fn render(&mut self, phi: &mut Phi, elapsed: f64) -> ViewAction {
        if phi.events.now.quit || phi.events.now.key_escape == Some(true) {
            return ViewAction::Quit;
        }

        // Execute selected option on space
        if phi.events.now.key_space == Some(true) ||
           phi.events.now.key_return == Some(true)
        {
            let bg = self.bg.clone();
            return (self.actions[self.selected as usize].func)(phi, bg);
        }

        // Change selected action using keyboard
        if phi.events.now.key_up == Some(true) {
            self.selected -= 1;
            if self.selected < 0 {
                self.selected = self.actions.len() as i8 - 1;
            }
        }

        // Change selected action using keyboard
        if phi.events.now.key_down == Some(true) {
            self.selected += 1;
            if self.selected >= self.actions.len() as i8 {
                self.selected = 0;
            }
        }

        // Clear the screen
        phi.renderer.set_draw_color(Color::RGB(0, 0, 0));
        phi.renderer.clear();

        // Render backgrounds
        self.bg.back.render(&mut phi.renderer, elapsed);
        self.bg.middle.render(&mut phi.renderer, elapsed);
        self.bg.front.render(&mut phi.renderer, elapsed);

        // Used for text centering
        let (win_w, win_h) = phi.output_size();
        let label_h = 50.0;
        let border_width = 3.0;
        let box_w = 360.0;
        let box_h = self.actions.len() as f64 * label_h;
        let margin_h = 10.0;

        // Render box to hold text
        phi.renderer.set_draw_color(Color::RGB(70, 15, 70));
        phi.renderer.fill_rect(Rectangle {
            w: box_w + border_width * 2.0,
            h: box_h + border_width * 2.0 + margin_h * 2.0,
            x: (win_w - box_w) / 2.0 - border_width,
            y: (win_h - box_h) / 2.0 - margin_h - border_width,
        }.to_sdl().unwrap());

        // Render text
        for (i, action) in self.actions.iter().enumerate() {
            let ((w, h), button_sprite) = if self.selected as usize == i {
                (action.hover_sprite.size(), &action.hover_sprite)
            } else {
                (action.idle_sprite.size(), &action.idle_sprite)
            };

            phi.renderer.copy_sprite(button_sprite, Rectangle {
                x: (win_w - w) / 2.0,
                y: (win_h - box_h + label_h - h) / 2.0 + label_h * i  as f64,
                w: w,
                h: h,
            });
        }

        ViewAction::None
    }
}

struct Action {
    func: Box<Fn(&mut Phi, BgSet) -> ViewAction>,
    idle_sprite: Sprite,
    hover_sprite: Sprite,
}

impl Action {
    fn new(phi: &mut Phi,
           label: &'static str,
           func: Box<Fn(&mut Phi, BgSet) -> ViewAction>) -> Action
    {
        Action {
            func: func,
            idle_sprite: phi.ttf_str_sprite(label, ACTION_FONT,
                                            32, Color::RGB(220, 220, 220))
                            .unwrap(),
            hover_sprite: phi.ttf_str_sprite(label, ACTION_FONT,
                                             42, Color::RGB(255, 255, 255))
                             .unwrap(),
        }
    }
}
