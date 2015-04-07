fn main() {
    let x = 5u32;
    let y = {
        let x_sq = x * x;
        let x_cube = x_sq * x;

        // This expression will be assigned to y
        x_cube + x_sq + x
    };

    let z = {
        let x_sq = x * x;
        let x_cube = x_sq * x;

        // This statement returns (), which z is now.
        x_cube + x_sq + x;
    };

    println!("x is {:?}", x);
    println!("y is {:?}", y);
    println!("z is {:?}", z);
}
