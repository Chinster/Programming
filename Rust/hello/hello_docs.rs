/// High level one liner
///
/// Other details in paragraph format, comments are return in Markdown so are
/// language independent. Often a .md file. Special sections are below.
/// Code segments can be compiled and tested.
///
/// # Examples
///
/// Example 1:
///
/// ```
/// println!("Hello World!");
/// ```
///
/// Example 2:
/// ```c
/// printf("Hello, world\n"); //  Not Rust Code
/// ```
///
/// Example 3:
/// ```text
/// rustdoc --test path/to/my/crate/root.rs
/// cargo test
/// ```
///
/// # Panics
///
/// # Failures
///
/// # Safety
pub fn new(value: T) -> Rc<T> {
    // implementation
}

/// The `Option` type. See [thee module level documentation](../)  for more.
enum Option<T> {
    /// No value
    None,
    /// Some value `T`
    Some(T),

    // An error, doc comments apply to thing after them
    // Some(T), ///  Some value `T`
}
