use std::{collections::HashMap, fs::File, io::{BufRead, BufReader}};

fn go(moves: u32, x: u64, dp: &mut HashMap<(u32, u64), u64>) -> u64 {
    if let Some(&result) = dp.get(&(moves, x)) {
        return result;
    }
    let result = if moves == 0 {
        1
    }
    else if x == 0 {
        go(moves-1, 1, dp)
    } else {
        let s = x.to_string();
        if s.len() % 2 == 0 {
            let x1 = s[0..(s.len() / 2)].parse::<u64>().unwrap();
            let x2 = s[s.len()/2..].parse::<u64>().unwrap();
            go(moves-1, x1, dp) + go(moves-1, x2, dp)
        }
        else {
            go(moves-1, x * 2024, dp)
        }
    };
    dp.insert((moves, x), result);
    result
}

pub fn main() {
    let input = File::open("input/d11.in").unwrap();
    let reader = BufReader::new(input);
    let a = reader.lines().map(|l| l.unwrap().split_whitespace().map(|t| t.parse::<u64>().unwrap()).collect::<Vec<_>>()).next().unwrap();
    let mut dp = HashMap::new();
    let ans = a.iter().map(|x| go(25, *x, &mut dp)).sum::<u64>();
    println!("{}", ans);
    let ans = a.iter().map(|x| go(75, *x, &mut dp)).sum::<u64>();
    println!("{}", ans);
}
