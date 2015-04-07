/// Display of the types in Rust
///
/// Rust does not have implicit casts. Rust does have explicit casts.
#[allow(overflowing_literals)]
#[allow(unused_variables)]
fn main() {
    let a_float: f64 = 1.0;
    let a_float2: f32 = 1.0;

    // Type inference!
    let a_i32 = 5;
    let a_i32_also = 5i32;
    let x = 5u32;
    let y = 5_u16;
    let z = 5_u8;

    let a_float = 65.4321_f32;
    let a_int = a_float as u8;
    let a_char = a_int as char;

    println!("Casting: {} -> {} -> {}", a_float, a_int, a_char);

    // When casting to unsigned T, std::T::MAX + 1 is added or subtracted
    // until the value fits into the new type.
    println!("1000 as a u16 is: {}", 1000 as u16);
    // 1000 - 256 - 256 = 232
    println!("1000 as a u8 is: {}", 1000 as u8);
    println!("1000 mod 256 is: {}", 1000 % 256);
    // -1 + 256 = 255
    println!("-1 as a u8 is: {}", (-1_i8) as u8);

    // When casting to signed T, the unsigned part of T is casted to unsigned
    // then the result is two's complemented.
    println!("128 as a i16 is: {}", 128 as i16);
    println!("128 as a i8 is: {}", 128 as i8);
    println!("1000 as a i8 is: {}", 128 as i8);
    println!("232 as a i8 is: {}", 232 as i8);

    // Unsuffixed literals with have sizes depending upon how they are used.
    // Compiler defaults to i32 and f64
    println!("size of an u8 in bytes: {}", std::mem::size_of_val(&3u8));

    // Alias NanoSecond to u64.
    type NanoSecond = u64;
}
