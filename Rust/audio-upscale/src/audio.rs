use ::hound::{WavReader, WavSpec, WavWriter};

/// Performs preprocessing while recursing into subdirectories.
pub fn process_recurse(path: &str) {
}

/// Performs linear interpolation on a WAV file, replacing it.
pub fn process(path: &str) {
    let (spec, data) = read_wav(path);
    let new_data = linear_interp(data);
    write_file(path, spec, new_data);
}

/// Reads a WAV file and returns its data and specification
fn read_wav(path: &str) -> (WavSpec, Vec<i32>) {
    let reader = WavReader::open(path).unwrap();

    let spec = reader.spec();
    let data = reader.into_samples::<i16>()
                     .map(|sample| sample.unwrap() as i32)
                     .collect();
    (spec, data)
}

/// Performs simple averages to interpolate a datum between two points. As a
/// result the size of the resulting data is actually 2n - 1 where n is the
/// original length. This function is executed on WAV data, whose data points
/// are interleaved for left and right audio.
fn linear_interp(in_data: Vec<i32>) -> Vec<i32> {
    let mut data = Vec::new();

    // WAV data is interweaved.
    let mut prev_sample = (in_data[0], in_data[1]);

    data.push(prev_sample.0);
    data.push(prev_sample.1);
    let mut in_iter = in_data.iter();
    loop {
        let left = match in_iter.next() {
            Some(sample) => *sample,
            None => break,
        };
        let right = match in_iter.next() {
            Some(sample) => *sample,
            None => break,
        };
        let left_avg = (prev_sample.0 + left) / 2;
        let right_avg = (prev_sample.1 + right) / 2;
        data.push(left_avg);
        data.push(right_avg);
        data.push(left);
        data.push(right);
        prev_sample = (left, right);
    }

    data
}
/// Writes the given data to a file
fn write_file(name: &str, spec: WavSpec, out_data: Vec<i32>) {
    let mut writer = WavWriter::create(name, spec).unwrap();

    for data in out_data {
        writer.write_sample(data as i16);
    }

    writer.finalize().unwrap();
}
