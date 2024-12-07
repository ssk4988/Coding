use std::{fs::File, io::{BufRead, BufReader}};

fn readLines() -> Vec<Vec<i32>> {
    let input = File::open("input/d2p1.in").unwrap();
    let reader = BufReader::new(input);
    let mut res = reader.lines()
        .map(|l| l.unwrap().split_whitespace()
        .map(|v| v.parse::<i32>().unwrap()).collect()).collect();
    res
}

fn safeness(v: &Vec<i32>) -> bool {
    let mut v2 = v.clone();
    v2.sort();
    let mut ordered = false;
    if v2 == *v {
        ordered = true;
    }
    v2.reverse();
    if v2 == *v {
        ordered = true;
    }
    if !ordered { return false; }
    (1..v.len()).all(|i| {
        (1..4).contains(&(v[i] - v[i-1]).abs())
    })
}

fn part1(a: &Vec<Vec<i32>>) {
    let mut ans = a.iter().filter(|v| safeness(v)).count();
    println!("{}", ans);
}

fn part2(a: &Vec<Vec<i32>>) {
    let mut ans = 0;
    for v in a {
        if safeness(v) {
            ans += 1;
            continue;
        }
        for i in 0..v.len() {
            let mut res = v.clone();
            res.remove(i);
            if safeness(&res) {
                ans += 1;
                break;
            }
        }
    }
    println!("{}", ans);
}

pub fn main() {
    let mut v = readLines();
    part1(&v);
    part2(&v);
}
