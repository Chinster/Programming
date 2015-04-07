use std::thread;
use std::sync::{Arc, Mutex};
use std::sync::mpsc;


fn main() {
    // returns a join guard which causes main thread to join this thread when
    // the join guard goes out of scope
    thread::scoped(|| {
        println!("Hello, world!");
    });

    // Does not return a join guard, which is why we join it.
    thread::spawn(|| {
        println!("Hello, world2!");
    }).join();

    // Create an atomic reference counted pointer
    let data = Arc::new(Mutex::new(vec![1u32, 2, 3]));

    // Create a channel for synchronization with spawned threads
    // Any data with trait Send can be sent down channel
    let (tx, rx) = mpsc::channel();

    for i in 0..10 {
        // Cloning an Arc increases its internal counter
        let (data, tx) = (data.clone(), tx.clone());
        thread::spawn(move || {
            // .lock() on a mutex returns a Result<T, E>
            // which could be an error. This code simply unwrap() the result.
            let mut data = data.lock().unwrap();
            *data[i] += 1;

            tx.send(());
        });
    }
    for _ in 0..10 {
        rx.recv();
    }

    let result = thread::spawn(move || {
        panic!("oh no!");
    }).join();
    assert!(result.is_err());
}
