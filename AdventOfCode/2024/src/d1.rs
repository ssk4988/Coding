use std::{collections::HashMap, fs::File, io::{BufRead, BufReader}};

fn readLines() -> (Vec<i32>, Vec<i32>) {
    let input = File::open("input/d1p1.in").unwrap();
    let reader = BufReader::new(input);
    let (mut v1, mut v2) = (Vec::new(), Vec::new());
    for line in reader.lines() {
        let nums: Vec<i32> = line.unwrap().split_whitespace()
            .map(|v| v.parse::<i32>().unwrap()).collect();
        v1.push(nums[0]);
        v2.push(nums[1]);
    }
    (v1, v2)
}

fn part1(v1: &Vec<i32>, v2: &Vec<i32>) -> u32 {
    v1.iter().zip(v2.iter()).map(|(a, b)| a.abs_diff(*b)).sum::<u32>()
}

fn part2(v1: &Vec<i32>, v2: &Vec<i32>) -> i32 {
    let mut freq = HashMap::new();
    v2.iter().for_each(|i| *freq.entry(i).or_insert(0) += 1);
    v1.iter().map(|i| i * freq.get(i).unwrap_or(&0)).sum()
}

pub fn main () {
    let (mut v1, mut v2) = readLines();
    v1.sort();
    v2.sort();
    println!("{}", part1(&v1, &v2));
    println!("{}", part2(&v1, &v2));
}
