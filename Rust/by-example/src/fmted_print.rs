/// Usage of various formatted prints
use std::fmt;

pub fn _run() {
    // `{}` is replaced with stringified arguments.
    println!("{} days", 31);

    // Positional arguments.
    println!("{0}, this is {1}. {1}, this is {0}", "Alice", "Bob");

    // Named arguments.
    println!("{subject} {verb} {predicate}",
             predicate="overr the lazy dog",
             subject="the quick brown fox",
             verb="jumps");

    // Special formatting after :
    println!("{} of  {:b} people know binary, the other half don't", 1, 2);

    println!("{:?} and {:?} are some debugging output.", "This", 3);

    // Cannot be printed by debug prints.
    struct UnPrintable(i32);
    // Allow for debug printing on this struct.
    #[derive(Debug)]
    struct DebugPrintable(i32);

    // An implementation of fmt::Display so `{}` can be used.
    // This needs to be done because the std lib does not want to dictate
    // a certain format for how some things should be printed.
    impl fmt::Display for UnPrintable {
        fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
            write!(f, "{}", self.0)
        }
    }
    println!("{:?} a newtype pattern. {} an implementation of fmt::Display",
             DebugPrintable(42),
             UnPrintable(42));
}
