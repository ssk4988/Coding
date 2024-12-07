use std::{collections::HashMap, io::{self, prelude::*}};

pub fn main() {
    let inputFile = std::fs::File::open("input/d1p1.in").unwrap();
    let bufReader = io::BufReader::new(inputFile);
    // let mut input = Scanner::from(io::stdin().lock());
    let mut input = Scanner::from(bufReader);
    let mut writer = io::BufWriter::new(io::stdout().lock());

    let mut freq1 = HashMap::new();
    let mut freq2 = HashMap::new();
    while let Some(x) = input.token::<i32>() {
        *freq1.entry(x).or_insert(0) += 1;
        let y = input.token::<i32>().unwrap();
        *freq2.entry(y).or_insert(0) += 1;
    }

    let mut sum = 0;
    for (k, v) in freq1.iter() {
        sum += k * freq2.get(k).unwrap_or(&0);
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
