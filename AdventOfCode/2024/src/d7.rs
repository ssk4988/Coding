use std::{collections::HashSet, fs::File, io::{BufRead, BufReader}, mem::swap};

fn part1(targs: &Vec<(u64, Vec<u64>)>) {
    let mut ans = 0;
    targs.iter().for_each(|(target, operands)| {
        let mut seen = HashSet::new();
        seen.insert(1);
        for v in operands {
            let mut seen2 = HashSet::new();
            for u in seen.iter() {
                seen2.insert(u * v);
                seen2.insert(u + v);
            }
            swap(&mut seen, &mut seen2);
        }
        if seen.contains(target) {
            ans += target;
        }
    });
    println!("{}", ans);
}

fn part2(targs: &Vec<(u64, Vec<u64>)>) {
    let mut ans = 0;
    targs.iter().for_each(|(target, operands)| {
        let mut seen = HashSet::new();
        seen.insert(1);
        for v in operands {
            let mut seen2 = HashSet::new();
            let len = v.to_string().len();
            for u in seen.iter() {
                seen2.insert(u * v);
                seen2.insert(u + v);
                seen2.insert(u * 10_u64.pow(len as u32) + v);
            }
            swap(&mut seen, &mut seen2);
        }
        if seen.contains(target) {
            ans += target;
        }
    });
    println!("{}", ans);
}

pub fn main() {
    let input = File::open("input/d7.in").unwrap();
    let reader = BufReader::new(input);
    let targs = reader.lines().map(|line| {
        let line = line.unwrap();
        let tokens = line.split_whitespace().collect::<Vec<&str>>(); 
        let target = tokens[0][0..(tokens[0].len()-1)].parse::<u64>().unwrap();
        let operands = tokens[1..tokens.len()].iter().map(|v| v.parse::<u64>().unwrap()).collect::<Vec<u64>>();
        (target, operands)
    }).collect::<Vec<_>>();
    part1(&targs);
    part2(&targs);
}
