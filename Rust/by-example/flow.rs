fn main() {
    let n = 5;
    if n < 0 {
        println!("{} is negative", n);
    }
    else if n > 0 {
        println!("{} is negative", n);
    }
    else {
        println!("{} is zero", n);
    }

    // infinite loop
    let mut count = 0u32;
    'outer: loop {
        count += 1;

        if count == 3 {
            continue;
        }
        println!("{}",  count);

        if count == 6 {
            println!("We are at {}", count);
            // This loop breaks out of the whole loop
            'inner: loop {
                continue 'outer;
            }
        }
        if count == 8 {
            break;
        }
    }

    for _i in 1..101 {
        continue;
    }

    // Matches are like switches
    match count {
        1 => println!("One"),
        2 | 3 | 5 | 7 | 11 => println!("Small Prime"),
        13...19 =>  println!("A teen"),
        i @ _ => println!("{}", i),
    }
    // Destructuring a pair
    let pair = (0, -2);
    match pair {
        (0, _y) => (),
        (_x, 0) => (),
        (x, y) if x == y => println!("Square Pair"),
        _ => (),
    }

    // Destructuring references
    //let refer = &4;
    let  ref refer = 4;
    match refer {
        &val => println!("Destructured reference: {:?}", val),
    }
    match *refer {
        val => println!("Dereferenced match: {:?}", val),
    }

    let mut value = 4;
    match value {
        ref mut r => {
            *r + 1;
            println!("Ref from val: {:?}", r);
        },
    }

    // Destructuring Structs
    struct Foo { x: (u32, u32), y: u32 }
    let foo = Foo {x: (1, 2), y: 3 };
    // Capturing variables
    let Foo { x: (a, b), y } = foo;
    println!("a = {}, b = {}, y = {}", a, b, y);

    let num = Some(4);
    // `if let` - if `let` destructures `number` info `Some(i)` eval block
    if let Some(_i) = num {
        println!("Matched");
    }
    // while let
}
