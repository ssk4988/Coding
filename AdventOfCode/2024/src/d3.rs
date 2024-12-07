use std::{fs::File, io::{BufRead, BufReader}};
use regex::Regex;

fn read_lines() -> String {
    let input = File::open("input/d3p1.in").unwrap();
    let reader = BufReader::new(input);
    reader.lines().map(|l| l.unwrap()).collect::<Vec<String>>().join("\n")
}

fn part1(s: &String) {
    let re = Regex::new(r"mul\((\d{1,3}),(\d{1,3})\)").unwrap();
    let ans = re.captures_iter(s).map(|cap| {
        let a = cap[1].parse::<i32>().unwrap();
        let b = cap[2].parse::<i32>().unwrap();
        a*b
    }).sum::<i32>();
    println!("{}", ans);
}

fn part2(s: &String) {
    let re = Regex::new(r"mul\((\d{1,3}),(\d{1,3})\)").unwrap();
    let re2 = Regex::new(r"do\(\)").unwrap();
    let re3 = Regex::new(r"don't\(\)").unwrap();
    let do_indices = re2.find_iter(s).map(|m| m.start()).collect::<Vec<usize>>();
    let dont_indices = re3.find_iter(s).map(|m| m.start()).collect::<Vec<usize>>();
    let do_set = do_indices.iter().collect::<std::collections::BTreeSet<_>>();
    let dont_set = dont_indices.iter().collect::<std::collections::BTreeSet<_>>();
    let ans = re.captures_iter(s).map(|cap| {
        let start_index = cap.get(0).unwrap().start();
        let do_last = do_set.range(..start_index).next_back();
        let dont_last = dont_set.range(..start_index).next_back();
        if dont_last.is_some() && (do_last.is_none() || do_last.unwrap() < dont_last.unwrap()) {
            return 0;
        }
        let a = cap[1].parse::<i32>().unwrap();
        let b = cap[2].parse::<i32>().unwrap();
        a * b
    }).sum::<i32>();
    println!("{}", ans);
}

pub fn main() {
    let v = read_lines();
    part1(&v);
    part2(&v);
}
