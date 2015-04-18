///Takes two numbers from stdin and prints their sum to stdout
fn main() {
    let mut stdin = std::io::stdin();
    let mut sum = 0;
    let mut line = String::new();
    match stdin.read_line(&mut line) {
        Ok(_) => match line.trim().parse::<u32>() {
                Ok(num) => sum += num,
                Err(_) => println!("Error due to: {}", reason),
            },
        Err(_) => println!("Could not read line."),
    }

    line = String::new();
    match stdin.read_line(&mut line) {
        Ok(_) => match line.trim().parse::<u32>() {
                Ok(num) => sum += num,
                Err(reason) => println!("Error due to: {}", reason),
            },
        Err(reason) => println!("Error: {}", reason),
    }
    println!("{}", sum);
}
