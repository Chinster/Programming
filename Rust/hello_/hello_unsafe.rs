fn main() {
    use std::mem;
    let mut x: u8 = 1;

    let ref1: &mut u8 = &mut x;
    let ref2: &mut u8 = unsafe { mem::transmute(&mut *ref1) };

    // Both references point to the same piece of data.
    // Violates Rust Ownership System
    *ref1 = 10;
    *ref2 = 20;

    // Raw pointers are not guaranteed to point to valid memory,
    // require manual resource management, and other loosened restrictions
    let x: *const i32;

    // Recommended method for *const to & conversion. The programmer must
    // guarentee that the pointer points to valid memory
    let i: u32 = 1;
    // explicit cast
    let p_imm: *const u32 = &i as *const u32;
    let mut m: u32 = 2;
    // implicit coercioin
    let p_mut: *mut u32 = &mut m;

    unsafe {
        let ref_imm: &u32 = &*p_imm;
        let ref_mut: &mut u32 = &mut *p_mut;
    }
}
