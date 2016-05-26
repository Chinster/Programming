pub struct Matrix<T> {
    height: usize,
    width: usize,
    data: Vec<T>
}

impl<T> Matrix<T> {
    pub fn new_from(vec: Vec<T>, h: usize, w: usize) -> Matrix<T> {
        Matrix {
            height: h,
            width: w,
            data: vec
        }
    }

    pub fn get_raw(self) -> Vec<T> {
        self.data
    }
}
