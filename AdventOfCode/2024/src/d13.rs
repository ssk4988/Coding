use std::{cmp::min, fs::File, io::{BufRead, BufReader}};

use regex::Regex;

pub fn main() {
    let reader = BufReader::new(File::open("input/d13.in").unwrap());
    let mut buttons = Vec::new();
    let mut targets = Vec::new();
    let button_regex = Regex::new(r".*X\+(\d*), Y\+(\d*)").unwrap();
    let target_regex = Regex::new(r".*X=(\d*), Y=(\d*)").unwrap();
    reader.lines().enumerate().for_each(|(i, l)| {
        let l = l.unwrap();
        match i % 4 {
            0 | 1 => {
                button_regex.captures_iter(&l).map(|c| c.extract()).for_each(|(_, [x, y])| {
                    buttons.push((x.parse::<i64>().unwrap(), y.parse::<i64>().unwrap()));
                });
            }
            2 => {
                target_regex.captures_iter(&l).map(|c| c.extract()).for_each(|(_, [x, y])| {
                    targets.push((x.parse::<i64>().unwrap(), y.parse::<i64>().unwrap()));
                });
            }
            _ => {}
        }
    });
    let ans = targets.iter().enumerate().map(|(i, (tx, ty))| {
        let (bx1, by1) = buttons[i * 2];
        let (bx2, by2) = buttons[i * 2 + 1];
        if let Some(b1) = (0..101).find(|&b1| {
            let (tx, ty) = (tx - bx1 * b1, ty - by1 * b1);
            if min(tx, ty) < 0 { return false; }
            tx * by2 == ty * bx2
        }) { 3 * b1 + (tx - bx1 * b1) / bx2 }
        else {0}
    }).sum::<i64>();
    let ans2 = targets.iter().enumerate().map(|(i, (tx, ty))| {
        let (tx, ty) = (tx + 10000000000000, ty + 10000000000000);
        let (bx1, by1) = buttons[i * 2];
        let (bx2, by2) = buttons[i * 2 + 1];
        let b1 = tx * by2 - ty * bx2;
        let b2 = bx1 * ty - by1 * tx;
        let deter = bx1 * by2 - by1 * bx2;
        assert!(deter != 0);
        if b1 % deter != 0 || b2 % deter != 0 {
            return 0;
        }
        let b1 = b1 / deter;
        let b2 = b2 / deter;
        assert!(bx1 * b1 + bx2 * b2 == tx);
        assert!(by1 * b1 + by2 * b2 == ty);
        3 * b1 + b2
    }).sum::<i64>();
    println!("{} {}", ans, ans2);
}
