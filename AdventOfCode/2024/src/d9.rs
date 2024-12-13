use std::{fs::File, io::{BufRead, BufReader}};

fn part1(mut ans: i64, mut free: Vec<(i32, i32)>, mut used: Vec<(i32, i32)>) {
    let mut idx = 0;
    for i in (0..used.len()).rev() {
        while used[i].1 > 0 && idx < free.len() {
            if free[idx].1 == 0 {
                idx += 1;
                continue;
            }
            if free[idx].0 as i32 > (used[i].0 as i32) + used[i].1 - 1 {
                break;
            }
            ans += i as i64 * free[idx].0 as i64;
            ans -= i as i64 * (used[i].0 + used[i].1 - 1) as i64;
            free[idx].0 += 1;
            free[idx].1 -= 1;
            used[i].1 -= 1;
        }
    }
    println!("{}", ans);
}

fn part2(mut ans: i64, mut free: Vec<(i32, i32)>, mut used: Vec<(i32, i32)>) {
    for i in (0..used.len()).rev() {
        let mut it = free.iter().enumerate().filter(|(_, &(idx, v))| v >= used[i].1);
        if let Some((vi, &(idx, v))) = it.next() {
            if idx > used[i].0 { continue; }
            ans += (idx - used[i].0) as i64 * used[i].1 as i64 * i as i64;
            free[vi].0 += used[i].1;
            free[vi].1 -= used[i].1;
            if free[vi].1 == 0 { free.remove(vi); }
        }
    }
    println!("{}", ans);
}

pub fn main() {
    let input = File::open("input/d9.in").unwrap();
    let reader = BufReader::new(input);
    let a = reader.lines().map(|l| l.unwrap()).collect::<Vec<_>>()[0].chars().collect::<Vec<_>>();
    let mut free = Vec::new();
    let mut used = Vec::new();
    let mut idx: usize = 0;
    let mut ans: i64 = 0;
    a.iter().enumerate().for_each(|(i, c)| {
        let v = (*c as i32) - '0' as i32;
        if v == 0 { return; }
        if i % 2 == 0 {
            used.push((idx as i32, v));
            ans += (idx as i32 * v + v * (v-1) / 2) as i64 * i as i64 /2;
        } else {
            free.push((idx as i32, v));
        }
        idx += v as usize;
    });
    part1(ans, free.clone(), used.clone());
    part2(ans, free, used);
}
