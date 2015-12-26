use std::cmp::Ordering;

fn bubble_sort<T>(arr: &mut [T]) where T: Ord {
    let ptr = arr.as_mut_ptr();
    for i in 0..arr.len() {
        for j in 1..(arr.len() - i) {
            unsafe {
                let right = ptr.offset(j as isize);
                let left = ptr.offset(j as isize - 1);
                if (*right).cmp(&*left) == Ordering::Less {
                    std::ptr::swap(right, left);
                }
            }
        }
    }
}

fn main() {
    let mut x = [3, 4, 2, 1, 5, 6, 8, 2];
    println!("{:?}", x);
    bubble_sort(&mut x);
    println!("{:?}", x);
}
