/// Input WAV data must be preprocessed before being used in the neural net.
/// Preprocessing involves naive upscaling to a higher bitrate through simple
/// linear interpolation.
extern crate hound;
extern crate rand;

mod audio;
mod matrix;
mod neuralnet;

use std::fs::File;
use neuralnet::NeuralNetwork;

const IN_SIZE: usize = 150;
const OUT_SIZE: usize = 150;
const HIDDEN_LAYERS: usize = 3;
const HIDDEN_NODES: usize = 200;

fn read_args() -> Option<Vec<Vec<f64>>> {
    let mut init_weights = None;

    let mut arg_iter = std::env::args().skip(1);
    while let Some(arg) = arg_iter.next() {
        match arg.as_ref() {
            "--preprocess" => audio::process_recurse(&arg_iter.next().unwrap()),
            "--initial_weights" => {
                match read_weights(&arg_iter.next().unwrap()) {
                    Ok(weights) => init_weights = Some(weights),
                    Err(e) => println!("{}", e),
                }
            },
            e => println!("Unknown flag: {}", e)
        }
    }

    init_weights
}

/// Reads a 2d array of weights in Rust Debug format.
fn read_weights(path: &str) -> Result<Vec<Vec<f64>>, std::io::Error> {
    /*
    let mut buf = String::new();
    File::open(path)
         .and_then(|handle| {
             handle.read_to_string(buf)
         })
    let file = try!(File::open(path));
    */
    Ok(Vec::new())
}

fn main() {
    let network = if let Some(init_weights) = read_args() {
        NeuralNetwork::new_from(init_weights)
    } else {
        NeuralNetwork::new(IN_SIZE, OUT_SIZE, HIDDEN_LAYERS, HIDDEN_NODES)
    };
    let mut rng = rand::thread_rng();
}
