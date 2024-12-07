use std::io::{self, prelude::*};

pub fn main() {
    let inputFile = std::fs::File::open("input/d1p1.in").unwrap();
    let bufReader = io::BufReader::new(inputFile);
    // let mut input = Scanner::from(io::stdin().lock());
    let mut input = Scanner::from(bufReader);
    let mut writer = io::BufWriter::new(io::stdout().lock());

    let mut a = Vec::new();
    let mut b = Vec::new();
    while let Some(x) = input.token::<i32>() {
        a.push(x);
        let y = input.token::<i32>().unwrap();
        b.push(y);
    }
    a.sort();
    b.sort();

    let mut sum = 0;
    for (x, y) in a.iter().zip(b.iter()) {
        sum += (x - y).abs();
    }
    writeln!(writer, "{}", sum);
}

pub struct Scanner<B> {
    reader: B,
    buffer: Vec<String>,
}

impl<R: BufRead> Scanner<R> {
    pub fn token<T: std::str::FromStr>(&mut self) -> Option<T> {
        loop {
            if let Some(token) = self.buffer.pop() {
                return Some(token.parse().ok().expect("Failed parse"));
            }
            let mut input = String::new();
            if self.reader.read_line(&mut input).expect("Failed read") == 0 {
                return None; // End of file
            }
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

impl<R: BufRead> From<R> for Scanner<R> {
    fn from(reader: R) -> Self {
        Self {
            reader,
            buffer: Vec::new(),
        }
    }
}
