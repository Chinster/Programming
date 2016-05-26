/// NOTE: Initial weights should be from -1/sqrt(d) to 1/sqrt(d) where d is the number of inputs to
/// a given neuron. Assume sets are normalized, mean 0, variance 1
/// NOTE: Number of hidden nodes (num inputs + outputs) * 2/3
use ::rand;
use ::rand::Rng;
use ::matrix::Matrix;

pub struct NeuralNetwork {
    weights: Vec<Vec<f64>>,
}

impl NeuralNetwork {
    /// Create a neural net with random weights.
    pub fn new(in_size: usize, out_size: usize,
               hidden_layers: usize, hidden_size: usize) -> NeuralNetwork {
        let mut rng = rand::thread_rng();
        let mut generator = rng.gen_iter::<f64>();

        let input_weight = generator.take(in_size * hidden_size).collect::<Vec<f64>>();
        /*
        let output_weight = generator.take(in_size * hidden_size).collect::<Vec<f64>>();
        let hidden_weights = generator.take(hidden_size * hidden_size * (hidden_layers - 1)).collect::<Vec<f64>>();
        */
        let x = Matrix::new_from(input_weight, in_size, hidden_size);
        let y = x.get_raw();
        NeuralNetwork {
            weights: Vec::new()
        }
    }

    pub fn new_from(weights: Vec<Vec<f64>>) -> NeuralNetwork {
        NeuralNetwork {
            weights: weights
        }
    }

    /// Moves an input vector through the neuralnet, returning the output
    pub fn propagate(&self, init: Vec<f64>) -> Vec<f64> {
        init.clone()
    }

    /// Performs back propagation and returns the resulting neural net
    pub fn train(&self, input: Vec<f64>, expected: Vec<f64>) -> NeuralNetwork {
        NeuralNetwork {
            weights: Vec::new()
        }
    }

    /// Sigmoid function
    fn sigmoid(x: f64) -> f64 {
        1.0 / (1.0 + (-x).exp())
    }

    /// Derivative of the sigmoid function
    fn sigmoid_prime(x: f64) -> f64 {
        (-x).exp() / ((1.0 + (-x).exp()).powi(2))
    }
}
