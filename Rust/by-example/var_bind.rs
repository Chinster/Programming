/// Usage of bindings
fn main() {
    // prepending with underscore disables compiler warnings about unused
    // variables.  Seems to work with functions as well.
    let _unit = ();

    let mut mutable = 1;
    print!("{} + 1 = ", mutable);
    mutable += 1;
    println!("{}", mutable);

    let shadow = 1;
    {
        let shadow = 3;
        println!("shadow {}, is in code block.", shadow);
    }
    println!("shadow {}, is outside code block.", shadow);

    //  y is uninitialized and cannot be used until it is.
    let _y: i32;
}
